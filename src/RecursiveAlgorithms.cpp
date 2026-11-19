// PART G — OWNER: MEMBER 3
#include "RecursiveAlgorithms.h"

#include <stdexcept>

namespace {
// Split by count to limit stack depth to O(log n). The cursor is shared
// across the two halves so node-based containers are traversed only once.
template <typename Next, typename Visit>
bool visitRange(std::size_t count, Next& next, const Visit& visit) {
    if (count == 0) {
        return false;
    }
    if (count == 1) {
        return visit(next());
    }
    const auto half = count / 2;
    return visitRange(half, next, visit) ||
           visitRange(count - half, next, visit);
}

template <typename Next>
double runRecursive(std::size_t count, Next next, const std::string& operation,
                    const std::string& department, double threshold, int searchId) {
    double result = 0.0;
    if (operation == "aggregate") {
        visitRange(count, next, [&](const Employee& employee) {
            result += employee.getSalary();
            return false;
        });
    } else if (operation == "filter_department") {
        visitRange(count, next, [&](const Employee& employee) {
            result += employee.getDepartment() == department;
            return false;
        });
    } else if (operation == "filter_performance") {
        visitRange(count, next, [&](const Employee& employee) {
            result += employee.getPerformanceScore() > threshold;
            return false;
        });
    } else if (operation == "search_id") {
        return visitRange(count, next, [searchId](const Employee& employee) {
            return employee.getEmployeeId() == searchId;
        });
    } else {
        throw std::invalid_argument("Unsupported recursive operation: " + operation);
    }
    return result;
}
} // namespace

double recursiveVectorOperation(const std::vector<Employee>& employees,
                                const std::string& operation,
                                const std::string& department,
                                double threshold, int searchId) {
    auto next = [&employees, index = std::size_t{0}]() mutable -> const Employee& {
        return employees[index++];
    };
    return runRecursive(employees.size(), next, operation, department, threshold, searchId);
}

double recursiveListOperation(const EmployeeList& employees,
                              const std::string& operation,
                              const std::string& department,
                              double threshold, int searchId) {
    auto next = [cursor = employees.cbegin()]() mutable -> const Employee& {
        return *cursor++;
    };
    return runRecursive(employees.size(), next, operation, department, threshold, searchId);
}

double recursiveSetOperation(const EmployeeSet& employees,
                             const std::string& operation,
                             const std::string& department,
                             double threshold, int searchId) {
    // This is a sequential scan. The iterative benchmark uses tree lookup.
    auto next = [cursor = employees.cbegin()]() mutable -> const Employee& {
        return *cursor++;
    };
    return runRecursive(employees.size(), next, operation, department, threshold, searchId);
}
