// PARTS E/F/G — OWNER: MEMBER 3
#include "Benchmark.h"
#include <stdexcept>

BenchmarkResult runBenchmark(const BenchmarkConfig& config) {
    // TODO MEMBER 3 — STAGE 1: Load data and construct chosen container.
    // For operation 'load', time file loading/object construction, and include
    // list/set insertion when that is the selected storage container.
    // For other operations, perform data loading BEFORE starting the timer.
    //
    // TODO MEMBER 3 — STAGE 2: Implement ONE operation per run so it can be
    // individually profiled using VTune, Instruments, or Linux perf:
    //   aggregate           -> sequential total salary
    //   filter_department   -> count records matching config.department
    //   filter_performance  -> count records with score > config.threshold
    //   sort_salary         -> sort records in salary order
    //   search_id           -> find config.searchId
    //   load                -> file load and object creation
    //
    // TODO MEMBER 3 — STAGE 3: Implement vector/list/set equivalents.
    // Sort vector via std::sort, list via list.sort. A set keyed by ID cannot
    // be salary-sorted in place: clearly document and time the construction
    // of a separate salary-ordered representation, with ID as tie-breaker.
    //
    // TODO MEMBER 3 — STAGE 4: For recursive mode call functions in
    // RecursiveAlgorithms.cpp (only aggregate/filter/search where suitable).
    //
    // TODO MEMBER 3 — STAGE 5: Use std::chrono::steady_clock, repeat
    // config.repetitions times, record mean elapsed milliseconds, and return
    // a checksum so the compiler cannot trivially eliminate the work.
    // Keep setup and timed sections consistent across all configurations.
    //
    // NOTE: chrono does NOT measure cache hits or misses. Record hardware
    // counters separately with a profiler in results/metrics_template.csv.
    (void)config;
    throw std::logic_error("TODO MEMBER 3: runBenchmark");
}
