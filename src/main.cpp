// PROJECT SHELL / CLI — OWNER: Masroor
#include "Analytics.h"
#include "Benchmark.h"
#include "EmployeeContainers.h"
#include "EmployeeIO.h"

#include <cstdlib>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    struct Options
    {
        std::string mode = "report"; // report | benchmark
        BenchmarkConfig benchmark;
        bool csv = false;
    };

    void usage(const char *executable)
    {
        std::cout
            << "Usage: " << executable << " [options]\n"
            << "  --file PATH                  default: data/employees.txt\n"
            << "  --mode report|benchmark      default: report\n"
            << "  --container vector|list|set  default: vector\n"
            << "  --threshold NUMBER           default: 4.0\n"
            << "  --department NAME            default: Engineering\n"
            << "  --search-id INTEGER          default: 1001\n"
            << "  --operation load|aggregate|filter_department|filter_performance|sort_salary|search_id\n"
            << "  --strategy iterative|recursive (benchmark mode only)\n"
            << "  --repetitions INTEGER        default: 5\n"
            << "  --csv                        print benchmark CSV row without header\n"
            << "  --help\n";
    }

    bool oneOf(const std::string &value, const std::vector<std::string> &choices)
    {
        for (const auto &choice : choices)
        {
            if (value == choice)
                return true;
        }
        return false;
    }

    int parseInteger(const std::string& value) {
        std::size_t used = 0;
        const int result = std::stoi(value, &used);
        if (used != value.size()) throw std::invalid_argument("Invalid integer: " + value);
        return result;
    }

    double parseNumber(const std::string& value) {
        std::size_t used = 0;
        const double result = std::stod(value, &used);
        if (used != value.size() || !std::isfinite(result))
            throw std::invalid_argument("Invalid finite number: " + value);
        return result;
    }

    Options parseOptions(int argc, char *argv[])
    {
        Options options;
        for (int i = 1; i < argc; ++i)
        {
            const std::string flag = argv[i];
            if (flag == "--help")
            {
                usage(argv[0]);
                std::exit(0);
            }
            if (flag == "--csv")
            {
                options.csv = true;
                continue;
            }
            if (i + 1 >= argc)
            {
                throw std::invalid_argument("Missing value after " + flag);
            }
            const std::string value = argv[++i];
            if (flag == "--file")
                options.benchmark.filePath = value;
            else if (flag == "--mode")
                options.mode = value;
            else if (flag == "--container")
                options.benchmark.container = value;
            else if (flag == "--strategy")
                options.benchmark.strategy = value;
            else if (flag == "--operation")
                options.benchmark.operation = value;
            else if (flag == "--threshold")
                options.benchmark.threshold = parseNumber(value);
            else if (flag == "--department")
                options.benchmark.department = value;
            else if (flag == "--search-id")
                options.benchmark.searchId = parseInteger(value);
            else if (flag == "--repetitions")
                options.benchmark.repetitions = parseInteger(value);
            else
                throw std::invalid_argument("Unknown option: " + flag);
        }

        if (!oneOf(options.mode, {"report", "benchmark"}))
            throw std::invalid_argument("--mode must be report or benchmark");
        if (!oneOf(options.benchmark.container, {"vector", "list", "set"}))
            throw std::invalid_argument("Invalid container: " + options.benchmark.container);
        if (!oneOf(options.benchmark.strategy, {"iterative", "recursive"}))
            throw std::invalid_argument("Invalid strategy: " + options.benchmark.strategy);
        if (!oneOf(options.benchmark.operation, {"load", "aggregate", "filter_department",
                                                 "filter_performance", "sort_salary", "search_id"}))
            throw std::invalid_argument("Invalid operation: " + options.benchmark.operation);
        if (options.benchmark.repetitions < 1)
            throw std::invalid_argument("--repetitions must be at least 1");
        if (options.mode == "benchmark" && options.benchmark.strategy == "recursive" &&
            oneOf(options.benchmark.operation, {"load", "sort_salary"}))
            throw std::invalid_argument("Recursion is not required for file loading/salary sorting");
        if (options.csv && options.mode != "benchmark")
            throw std::invalid_argument("--csv is only supported in benchmark mode");
        return options;
    }

    void printBenchmarkRow(const BenchmarkResult &result)
    {
        std::cout << result.container << ',' << result.strategy << ','
                  << result.operation << ',' << result.employeeCount << ','
                  << std::fixed << std::setprecision(6)
                  << result.averageElapsedMs << ',' << result.checksum << '\n';
    }
} // namespace

int main(int argc, char *argv[])
{
    try
    {
        const Options options = parseOptions(argc, argv);
        const BenchmarkConfig &config = options.benchmark;

        if (options.mode == "benchmark")
        {
            const BenchmarkResult result = runBenchmark(config);
            if (!options.csv)
            {
                std::cout << "container,strategy,operation,employees,elapsed_ms,checksum\n";
            }
            printBenchmarkRow(result);
            return 0;
        }

        const std::vector<Employee> employees = EmployeeIO::loadVector(config.filePath);
        AnalyticsReport report;
        if (config.container == "vector")
        {
            report = analyzeVector(employees, config.threshold);
        }
        else if (config.container == "list")
        {
            report = analyzeList(makeEmployeeList(employees), config.threshold);
        }
        else
        {
            report = analyzeSet(makeEmployeeSet(employees), config.threshold);
        }
        printReport(report, std::cout);
        return 0;
    }
    catch (const std::exception &error)
    {
        std::cerr << "ERROR: " << error.what() << '\n';
        return 1;
    }
}
