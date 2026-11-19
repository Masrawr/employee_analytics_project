// PARTS E/F/G — OWNER: MEMBER 3
#include "Benchmark.h"

#include "EmployeeIO.h"
#include "RecursiveAlgorithms.h"

#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <type_traits>

namespace {
using Clock = std::chrono::steady_clock;

bool salaryLess(const Employee& a, const Employee& b) {
    if (a.getSalary() != b.getSalary()) {
        return a.getSalary() < b.getSalary();
    }
    return a.getEmployeeId() < b.getEmployeeId();
}

template <typename Container>
double sortedChecksum(const Container& employees) {
    double checksum = 0.0;
    std::size_t position = 0;
    for (const Employee& employee : employees) {
        checksum += static_cast<double>(++position) * employee.getEmployeeId();
    }
    return checksum;
}

template <typename Container>
double runIterative(const Container& employees, const BenchmarkConfig& config) {
    if (config.operation == "search_id") {
        if constexpr (std::is_same_v<Container, EmployeeSet>) {
            return employees.find(config.searchId) != employees.end();
        } else {
            return std::any_of(employees.begin(), employees.end(), [&](const Employee& employee) {
                return employee.getEmployeeId() == config.searchId;
            });
        }
    }

    double result = 0.0;
    if (config.operation == "aggregate") {
        for (const Employee& employee : employees) {
            result += employee.getSalary();
        }
    } else if (config.operation == "filter_department") {
        for (const Employee& employee : employees) {
            result += employee.getDepartment() == config.department;
        }
    } else if (config.operation == "filter_performance") {
        for (const Employee& employee : employees) {
            result += employee.getPerformanceScore() > config.threshold;
        }
    } else {
        throw std::invalid_argument("Unsupported operation: " + config.operation);
    }
    return result;
}

template <typename Load, typename Recursive>
BenchmarkResult measure(const BenchmarkConfig& config, Load load, Recursive recursive) {
    using Container = decltype(load());
    BenchmarkResult result{config.container, config.strategy, config.operation};
    double elapsedMs = 0.0;
    const auto recordTime = [&](Clock::time_point start) {
        elapsedMs += std::chrono::duration<double, std::milli>(Clock::now() - start).count();
    };

    if (config.operation == "load") {
        for (int repetition = 0; repetition < config.repetitions; ++repetition) {
            const auto start = Clock::now();
            const auto employees = load();
            recordTime(start);
            result.employeeCount = employees.size();
            result.checksum += static_cast<double>(employees.size());
        }
    } else {
        const auto employees = load();
        result.employeeCount = employees.size();
        for (int repetition = 0; repetition < config.repetitions; ++repetition) {
            if (config.operation == "sort_salary") {
                if constexpr (std::is_same_v<Container, EmployeeSet>) {
                    // The ID-ordered set requires a separate salary-ordered representation.
                    const auto start = Clock::now();
                    std::vector<Employee> sorted(employees.begin(), employees.end());
                    std::sort(sorted.begin(), sorted.end(), salaryLess);
                    recordTime(start);
                    result.checksum += sortedChecksum(sorted);
                } else {
                    auto sorted = employees;
                    const auto start = Clock::now();
                    if constexpr (std::is_same_v<Container, EmployeeList>) {
                        sorted.sort(salaryLess);
                    } else {
                        std::sort(sorted.begin(), sorted.end(), salaryLess);
                    }
                    recordTime(start);
                    result.checksum += sortedChecksum(sorted);
                }
            } else {
                const auto start = Clock::now();
                const double value = config.strategy == "recursive"
                    ? recursive(employees, config.operation, config.department,
                                config.threshold, config.searchId)
                    : runIterative(employees, config);
                recordTime(start);
                result.checksum += value;
            }
        }
    }
    result.averageElapsedMs = elapsedMs / config.repetitions;
    result.checksum /= config.repetitions;
    return result;
}
} // namespace

BenchmarkResult runBenchmark(const BenchmarkConfig& config) {
    if (config.repetitions < 1) {
        throw std::invalid_argument("Benchmark repetitions must be at least 1");
    }
    if (config.strategy != "iterative" && config.strategy != "recursive") {
        throw std::invalid_argument("Unknown benchmark strategy: " + config.strategy);
    }
    if (config.strategy == "recursive" &&
        (config.operation == "load" || config.operation == "sort_salary")) {
        throw std::invalid_argument("This operation supports the iterative strategy only");
    }

    const auto loadVector = [&] { return EmployeeIO::loadVector(config.filePath); };
    if (config.container == "vector") {
        return measure(config, loadVector, recursiveVectorOperation);
    }
    // List and set loading include parsing into the shared vector, conversion,
    // and disposal of the intermediate vector.
    if (config.container == "list") {
        return measure(config, [&] { return makeEmployeeList(loadVector()); },
                       recursiveListOperation);
    }
    if (config.container == "set") {
        return measure(config, [&] { return makeEmployeeSet(loadVector()); },
                       recursiveSetOperation);
    }
    throw std::invalid_argument("Unknown benchmark container: " + config.container);
}
