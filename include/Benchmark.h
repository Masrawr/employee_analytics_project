#pragma once

#include <cstddef>
#include <string>

// PARTS E, F, G — OWNER: MEMBER 3
struct BenchmarkConfig {
    std::string filePath = "data/employees.txt";
    std::string container = "vector";     // vector | list | set
    std::string strategy = "iterative";   // iterative | recursive
    std::string operation = "aggregate";  // load | aggregate |
                                          // filter_department | filter_performance |
                                          // sort_salary | search_id
    std::string department = "Engineering";
    double threshold = 4.0;
    int searchId = 1001;
    int repetitions = 5;
};

struct BenchmarkResult {
    std::string container;
    std::string strategy;
    std::string operation;
    std::size_t employeeCount{0};
    double averageElapsedMs{0.0};
    double checksum{0.0};
};

// Use chrono for elapsed time. Use an external profiler for hardware cache data.
BenchmarkResult runBenchmark(const BenchmarkConfig& config);
