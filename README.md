# CSC 326 — Group Assignment #2: Employee Analytics & Cache Profiling

**Deadline:** Wednesday, November 18, 2026, at 11:59 PM.

This is a **compilable project skeleton**, not a finished analytics implementation.
Member 2 and Member 3 must replace every `TODO MEMBER 2` / `TODO MEMBER 3` stub before the
program will produce reports or benchmark results. Each unfinished stub throws a
`std::logic_error` on purpose instead of producing a fake answer.

## File owners

| Owner | Responsibilities | Files |
|---|---|---|
| Member 1 - Masroor Jehangiri | Project organization, command-line entry point, build setup, test data, test plan, presentation, final integration | `src/main.cpp`, `CMakeLists.txt`, `.gitignore`, `README.md`, `scripts/`, `data/`, `tests/`, `presentation/`, `results/` |
| Member 2 - Malaak Ghanem| Part A Employee class; Part B parsing/loading; Part C vector; Part D full report | `include/Employee.h`, `src/Employee.cpp`, `include/EmployeeIO.h`, `src/EmployeeIO.cpp`, `src/Analytics.cpp` (vector and report printer), shared declarations in `include/Analytics.h` |
| Member 3 - Name | Parts E–G: benchmarking, cache profiling coordination, list and set analytics, iteration vs recursion | `include/EmployeeContainers.h`, `src/EmployeeContainers.cpp`, `src/ContainerAnalytics.cpp`, `include/RecursiveAlgorithms.h`, `src/RecursiveAlgorithms.cpp`, `include/Benchmark.h`, `src/Benchmark.cpp` |

**Shared contract:** Do not change function names, parameters, return types, or
`AnalyticsReport` fields without coordinating with the other two members.

## How each assignment section maps to the project

| Part | Where |
|---|---|
| A — Employee class, 10 fields, constructors/getters/setters/full name/serialize/three analytics methods | `include/Employee.h`, `src/Employee.cpp` |
| B — `employees.txt` pipe-separated records, parse and load | `data/employees.txt`, `src/EmployeeIO.cpp` |
| C — `vector<Employee>` | `EmployeeIO::loadVector()`, `main.cpp` |
| D — employee analytics (a) through (j) | `AnalyticsReport`, `analyzeVector()`, `printReport()` |
| E — loading, aggregation, filtering, sorting and searching benchmarks | `Benchmark.cpp`, `results/metrics_template.csv` |
| F — `list<Employee>` and `set<Employee>` analytical pipelines | `EmployeeContainers.cpp`, `ContainerAnalytics.cpp` |
| G — recursive counterparts and comparisons | `RecursiveAlgorithms.cpp`, `Benchmark.cpp` |

## Build on macOS, Linux or Windows with CMake and a C++17 compiler

From **inside the project directory**:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Executable on macOS/Linux: `./build/employee_analytics`.
On Windows, it may be `build/Release/employee_analytics.exe` depending on generator.

**Important:** Compilation succeeds before teammates finish, but running
analytics or benchmarks will produce `ERROR: TODO MEMBER ...`. This is intentional.

## CLI commands after implementations are filled

```bash
# Part D: Vector report, 35 employee records
./build/employee_analytics --file data/employees.txt --mode report --container vector

# Part F: Equivalent reports using list and set
./build/employee_analytics --file data/employees.txt --mode report --container list
./build/employee_analytics --file data/employees.txt --mode report --container set

# Repeat reports on the >5000 employee dataset
./build/employee_analytics --file data/employees_large.txt --mode report --container vector

# Part E: Time a single operation in a release build
./build/employee_analytics --file data/employees_large.txt --mode benchmark \
  --container vector --strategy iterative --operation aggregate

# Part G: Recursive counterpart, same dataset
./build/employee_analytics --file data/employees_large.txt --mode benchmark \
  --container vector --strategy recursive --operation aggregate

# Show all supported command-line options
./build/employee_analytics --help

# After implementation, collect all supported combinations in a CSV
bash scripts/run_benchmarks.sh
```

Benchmark operations: `load`, `aggregate`, `filter_department`,
`filter_performance`, `sort_salary`, `search_id`. Recursive operation modes are
used for aggregation, both filters and ID search; iterative mode is used for
file loading and salary sorting. Optional flags: `--threshold 4.0`,
`--department Engineering`, `--search-id 1001`, `--repetitions 5`.

## Dataset files

- `data/employees.txt`: **35 employees** (the first five examples are the same as
  the assignment handout), pipe-delimited with no header.
- `data/employees_large.txt`: **6001 employees** (exceeds 5000), same schema.
- `scripts/generate_data.py`: recreates both using a deterministic random seed.

Run the generator from the project directory:

```bash
python3 scripts/generate_data.py
```

The 10 fields in each record are, in order:

```text
employee_id|first_name|last_name|department|job_title|age|years_of_service|salary|performance_score|is_full_time
```

**Note:** There is no literal header row in the actual text files. Both files
contain unique employee IDs, and every record contains exactly ten fields.

## Agree on your analytics rules before coding

The assignment lets the group **choose** the bonus/promotion rules; it does
not prescribe numerical thresholds. One reasonable proposal (not yet implemented):

- `isHighPerformer()`: `performanceScore >= 4.0`.
- `annualBonusEstimate()`: `8% of salary` for a full-time high performer;
  otherwise `0`.
- `isEligibleForPromotion()`: full-time, at least **3 years of service**, and
  `performanceScore >= 4.3`.
- Report filter Part D(i): use `performanceScore > threshold` (strictly
  above the supplied threshold).

Member 2 should confirm these with the group and apply them consistently to
all containers. Empty inputs must not cause division by zero.

## Fair benchmark/profiler protocol

1. Compare **the same data**, compiler optimization level, threshold, ID, and
   machine for all containers. Use a Release build.
2. Run one named operation at a time so its code section can be isolated in a
   profiler. Perform setup outside timing except in the `load` benchmark.
3. Repeat each operation; report the average elapsed milliseconds in
   `results/timings.csv`. A checksum helps catch accidentally skipped work.
4. Use a **hardware profiler** for cache hit/miss counters and memory-access
   behavior. Fill `results/metrics_template.csv` with real measurements.
   `std::chrono` measures elapsed time **only**. VTune is an assignment example;
   alternatives depend on hardware/OS and available tooling (e.g. Instruments
   on macOS or `perf` on Linux).
5. Identify best/worst from actual results, not from expectations.

Expected qualitative behavior to **test**, not assume proven: vector usually
benefits from contiguous storage during sequential traversal; list/set nodes
can cause extra pointer chasing. Recursion may add call-stack overhead. Cache
performance can still depend on the compiler, workload and data size.

### Important fairness issues

- `set<Employee>` is **ordered by employee ID** using `EmployeeIdLess`. Equal
  employee IDs are considered duplicates; dataset IDs must be unique.
- A set cannot be sorted by salary **in place** while remaining keyed by ID.
  For `sort_salary`, build a separate salary-ordered representation using a
  salary comparator with employee ID as the tie-breaker. The timed operation
  should explicitly include that conversion, and this limitation should be
  explained in the presentation.
- `set.find(id)` is logarithmic, and can behave differently from a sequential
  recursive scan. Label which search algorithm is being measured.
- On large inputs, recursive traversal has stack-depth risks. Record if a test
  cannot complete safely instead of fabricating a number.
- Note that `loadVector()` is also used before list/set **report** mode. For
  list/set **load benchmarks**, include the creation of the selected container;
  clearly state how the file-read component was measured.

## Integration / contribution workflow

1. Masroor shares this project and assigns files by owner.
2. Member 2 fills `Employee.cpp`, `EmployeeIO.cpp`, `Analytics.cpp`.
3. Member 3 fills `EmployeeContainers.cpp`, `ContainerAnalytics.cpp`,
   `RecursiveAlgorithms.cpp`, `Benchmark.cpp`.
4. Replace all TODO-throwing stubs. Check for leftover `TODO MEMBER` strings.
5. Run `tests/TEST_PLAN.md` and benchmark script on both datasets.
6. Populate actual measurements and presentation slides from results.

**Submission check:** source code, both datasets, instructions, actual profiler
results, and presentation all need to be collected and reviewed against the
professor's submission instructions. The handout does not specify a required
slide format, a specific debugger/profiler, or a fixed bonus formula.
