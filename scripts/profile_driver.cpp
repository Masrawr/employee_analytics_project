// macOS-only profiling harness. Keeps normal application code portable.
#include "Benchmark.h"
#include <os/log.h>
#include <os/signpost.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char** argv) {
    if (argc != 3 && argc != 4) {
        std::cerr << "Usage: profile_driver PROJECT_ROOT OUTPUT_CSV [CASE_SUFFIX]\n";
        return 1;
    }
    std::ofstream out(argv[2]);
    if (!out) return 1;
    out << "case,dataset,container,strategy,operation,repetitions,employees,elapsed_ms,checksum\n";
    auto log = os_log_create("edu.csc326.employee", OS_LOG_CATEGORY_POINTS_OF_INTEREST);
    for (const auto& dataset : {"employees.txt", "employees_large.txt"}) {
        for (const auto& container : {"vector", "list", "set"}) {
            for (const auto& operation : {"load", "aggregate", "filter_department",
                                          "filter_performance", "sort_salary", "search_id"}) {
                for (const auto& strategy : {"iterative", "recursive"}) {
                    if (std::string(strategy) == "recursive" &&
                        (std::string(operation) == "load" || std::string(operation) == "sort_salary")) continue;
                    const std::string suffix = std::string(container) + ":" + strategy + ":" + operation;
                    if (argc == 4) {
                        const std::string selection = argv[3];
                        const bool retry = selection == "short" &&
                            (suffix == "set:iterative:search_id" ||
                             (std::string(dataset) == "employees.txt" &&
                              suffix == "set:recursive:filter_performance"));
                        if (!retry && suffix != selection) continue;
                    }
                    BenchmarkConfig config;
                    config.filePath = std::string(argv[1]) + "/data/" + dataset;
                    config.container = container;
                    config.operation = operation;
                    config.strategy = strategy;
                    // Missing ID makes every sequential search traverse the whole input.
                    config.searchId = -1;
                    config.repetitions = 100;
                    const auto calibration = runBenchmark(config);
                    // Calibrate from operation time, excluding one-time file loading.
                    // This matters especially for logarithmic set search.
                    config.repetitions = std::clamp(static_cast<int>(
                        500.0 / std::max(calibration.averageElapsedMs, 0.00005)), 100, 10000000);
                    const std::string label = std::string(dataset) + ":" + container + ":" + strategy + ":" + operation;
                    std::this_thread::sleep_for(std::chrono::milliseconds(40));
                    const auto id = os_signpost_id_generate(log);
                    os_signpost_interval_begin(log, id, "EmployeeCase", "%{public}s", label.c_str());
                    const auto result = runBenchmark(config);
                    os_signpost_interval_end(log, id, "EmployeeCase", "%{public}s", label.c_str());
                    out << label << ',' << dataset << ',' << container << ',' << strategy << ',' << operation
                        << ',' << config.repetitions << ',' << result.employeeCount << ','
                        << std::setprecision(12) << result.averageElapsedMs << ',' << result.checksum << '\n';
                    out.flush();
                    std::cerr << label << " completed\n";
                }
            }
        }
    }
}
