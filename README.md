# Employee Analytics — Group Assignment 2

**CSC 326 | Masroor Jehangiri, Malaak Ghanem, Doston Botirjonov**

## 1. What does our project do?

Our C++ program reads employee records from a text file and produces a report
about salaries, departments, performance, bonuses, and promotions.

We then run the same kinds of operations using three ways of storing data:
**vector, list, and set**. We compare loops with recursion and measure execution
time and CPU cache misses.

**Status:** Parts A–G are implemented. Both datasets passed the functional checks.
We collected real cache measurements for **60 combinations** of dataset,
container, operation, and strategy. The full findings are in
[the Part E–G report](results/PARTS_E_G.md).

## 2. How does the program work?

```text
Employee text file
        ↓
Read and check each record
        ↓
Create Employee objects and put them in a vector
        ↓
Keep the vector OR create a list OR create a set
        ↓
Print an analytics report OR run a performance benchmark
```

An **object** holds one employee's information. A **container** holds the employees.
A **benchmark** measures how long an operation takes. A **profiler** measures what
happens while the program runs, including hardware cache activity.

The program rejects bad records and duplicate employee IDs. Empty files are
handled safely. All three containers use the same reporting rules and are
traversed directly when calculating their reports.

## 3. What does each member contribute?

This table describes the original work recorded in the project's commits.

| Member | Work | Simple way to explain it |
|---|---|---|
| **Masroor Jehangiri** | Set up the project folders, starter code, build instructions, CLI, generated datasets, test plan, and presentation outline. Updated the entry point and merged the members' work. | “I organized the project and connected the different parts so we could build and run one program.” |
| **Malaak Ghanem** | Implemented the Employee class, employee-file parsing/loading, and vector analytics functions. | “Malaak built the employee records and the calculations used to analyze them.” |
| **Doston Botirjonov** | Implemented list/set construction and analytics, operation benchmarks, and recursive versions. | “Doston made it possible to compare containers and loops against recursion.” |

**Final integration:** after the merge, Masroor used Codex assistance to fix the
shared interfaces and parsing issues, complete report output, add automated
tests, collect Instruments measurements, and prepare the analysis/documentation.
Those later changes are separate from the members' original commits.

## 4. What results does the report show?

These are the ten items required by Part D:

1. Total number of employees.
2. Average salary.
3. Highest-paid employee.
4. Lowest-paid employee.
5. Average performance score.
6. Number of employees in each department.
7. Department with the highest average salary.
8. Full-time and part-time counts.
9. Employees whose performance score is above a chosen threshold.
10. Employees eligible for promotion or a bonus.

Our chosen rules are:

| Rule | Meaning |
|---|---|
| High performer | Performance score is **4.0 or higher**. |
| Promotion | At least **3 years of service** and a score of **4.0 or higher**. Part-time employees can qualify. |
| Bonus | Add **15%** of salary for at least 5 years of service, **10%** for a score of at least 4.0, and **2%** for being full-time. |
| Above-threshold report filter | Score must be **greater than** the threshold. At a threshold of 4.0, exactly 4.0 does not pass this filter. |

Bonus percentages add together. For example, a full-time employee earning
$100,000 with 5 years of service and a score of 4.2 gets a **27% bonus: $27,000**.

## 5. What is each file for?

A `.h` file declares the structures and functions other files can use.
A `.cpp` file contains the code that performs the work. Files in `scripts/` help
run experiments; they are not all needed to run the normal C++ program.

### Main C++ code — start here when studying

| File | Purpose |
|---|---|
| [src/main.cpp](src/main.cpp) | Starts the program, reads command-line options, and chooses report or benchmark mode. |
| [include/Employee.h](include/Employee.h) | Declares the Employee class and its ten fields and methods. |
| [src/Employee.cpp](src/Employee.cpp) | Implements constructors, getters/setters, full names, text output, and bonus/promotion rules. |
| [include/EmployeeIO.h](include/EmployeeIO.h) | Declares functions for reading employee records. |
| [src/EmployeeIO.cpp](src/EmployeeIO.cpp) | Splits records at `\|`, checks their values, and loads Employee objects into a vector. |
| [include/Analytics.h](include/Analytics.h) | Defines the shared report structure and declares analytics functions. |
| [include/AnalyticsDetail.h](include/AnalyticsDetail.h) | Contains the shared calculation code so all three containers follow the same rules. |
| [src/Analytics.cpp](src/Analytics.cpp) | Provides vector analytics and prints the report. It also retains the earlier individual calculation functions. |
| [include/EmployeeContainers.h](include/EmployeeContainers.h) | Defines the list/set types and how the set compares employee IDs. |
| [src/EmployeeContainers.cpp](src/EmployeeContainers.cpp) | Creates lists and sets. The set is ordered by employee ID. |
| [src/ContainerAnalytics.cpp](src/ContainerAnalytics.cpp) | Connects list and set reports to the shared calculations. |
| [include/RecursiveAlgorithms.h](include/RecursiveAlgorithms.h) | Declares recursive aggregation, filtering, and searching functions. |
| [src/RecursiveAlgorithms.cpp](src/RecursiveAlgorithms.cpp) | Implements those operations using actual recursive calls. |
| [include/Benchmark.h](include/Benchmark.h) | Defines benchmark settings and the result format. |
| [src/Benchmark.cpp](src/Benchmark.cpp) | Runs and times loading, aggregation, filtering, sorting, and searching. |

### Data, building, and tests

| File | Purpose |
|---|---|
| [data/employees.txt](data/employees.txt) | Small dataset: **35 employees**. |
| [data/employees_large.txt](data/employees_large.txt) | Large dataset: **6001 employees**. |
| [CMakeLists.txt](CMakeLists.txt) | Tells CMake which source files to compile and which tests to run. |
| [.gitignore](.gitignore) | Keeps generated binaries, temporary files, and large trace bundles out of Git. |
| [tests/employee_tests.cpp](tests/employee_tests.cpp) | Checks the Employee methods, bonus/promotion boundaries, and text round-trip accuracy. |
| [tests/verify.py](tests/verify.py) | Runs **226 command-line cases** and independently checks report values and benchmark answers. |
| [tests/TEST_PLAN.md](tests/TEST_PLAN.md) | Records which checks were completed and any verification limits. |

### Experiment scripts

| File | Purpose |
|---|---|
| [scripts/generate_data.py](scripts/generate_data.py) | Recreates both datasets using a fixed random seed, so the same inputs can be reproduced. |
| [scripts/run_benchmarks.sh](scripts/run_benchmarks.sh) | Runs all supported timing combinations on one dataset and saves a CSV. |
| [scripts/profile_driver.cpp](scripts/profile_driver.cpp) | Runs labeled benchmark batches so Instruments can identify each experiment. |
| [scripts/cache_recording_options.json](scripts/cache_recording_options.json) | Selects Instruments' L1 data-cache counters. |
| [scripts/run_cache_profile.sh](scripts/run_cache_profile.sh) | Builds the profiling harness, records hardware counters, and exports the results on macOS. |
| [scripts/trace_xml.py](scripts/trace_xml.py) | Reads Instruments' exported XML files and resolves their internal references. |
| [scripts/summarize_cache_profile.py](scripts/summarize_cache_profile.py) | Matches counter samples to benchmark intervals and calculates summary measurements. |
| [scripts/write_profile_report.py](scripts/write_profile_report.py) | Combines the original run and corrected measurements, checks answers, and builds the final results tables. |

### Reports and measurement evidence

| File | Purpose |
|---|---|
| [README.md](README.md) | This simple project and presentation guide. |
| [presentation/OUTLINE.md](presentation/OUTLINE.md) | Suggested slide order. It is an outline, not a finished slide deck. |
| [results/REVIEW.md](results/REVIEW.md) | Summarizes assignment coverage, integration fixes, and verification. |
| [results/PARTS_E_G.md](results/PARTS_E_G.md) | Full measured analysis: tables, explanations, best/worst comparisons, and limitations. |
| [results/cache_metrics.csv](results/cache_metrics.csv) | Final cache measurements for all **60** combinations. CSV files can be opened as tables. |
| [results/timings_small.csv](results/timings_small.csv) | Earlier elapsed-time measurements on 35 employees, without Instruments. |
| [results/timings_large.csv](results/timings_large.csv) | Earlier elapsed-time measurements on 6001 employees, without Instruments. |
| [results/metrics_template.csv](results/metrics_template.csv) | Original blank measurement template. Final measurements are in `cache_metrics.csv`. |
| `results/profiling/profile_timings.csv` | Timing and answer checks from the original profiling run. |
| `results/profiling/cache_summary.csv` | Summary of the original 60 profiling cases, before replacing three short measurements. |
| `results/profiling/OSSignpostIntervals.xml` | Start/end markers identifying which experiment was running. |
| `results/profiling/MetricTable.xml.gz` | Compressed export of the actual hardware counter samples. |
| `results/profiling/InvalidMetricTable.xml` | Instruments' invalid-sample report; no invalid rows were reported. |
| `results/profiling/short_retry/` | Corrected measurements for three initially short cases. Its same-named files have the same purposes as above. |
| `results/profiling/short_retry/toc.xml` | Lists the retry recording's settings and available data tables. |
| `results/profiling/**/MetricTable.xml` | Uncompressed local copies of the counter exports; ignored by Git. |
| `results/profiling/**/employee_l1d.trace/` | Original Instruments recordings kept locally; ignored by Git because they are large. |
| `build/` | Generated executables. This folder is created when building and is ignored by Git. |

## 6. How do we explain Parts E–G?

### The basic terms

| Term | Simple meaning |
|---|---|
| Vector | A growable array. Employee objects sit next to each other in memory. |
| List | Separate nodes linked together. The program follows links to reach the next employee. |
| Set | An ordered collection with unique keys. Ours orders employees by ID and supports efficient ID lookup. |
| Iteration | Repeating work using a loop. |
| Recursion | A function calls itself to work through smaller parts of the problem. |
| CPU cache | Small, fast memory close to the processor that holds recently used data. |
| Cache miss | Needed data is not in the cache being measured, so it must be obtained from elsewhere. |
| Aggregation | Combining values, such as adding all salaries. |
| Checksum | A value derived from the answer that helps verify that different versions did the same work. |

**Part E:** profile loading, aggregation, filtering, sorting, and searching.
We measured both department filtering and performance filtering, giving six
operations in total.

**Part F:** compare those operations using vector, list, and set.

**Part G:** compare iterative and recursive aggregation, filtering, and searching.
Loading and library sorting keep their normal implementations because recursive
replacements were not appropriate here.

There are **30 supported combinations per dataset × 2 datasets = 60 cases**.

### Main findings you can present

- On the large dataset, **vector iteration had the fewest measured L1D misses per
  run for aggregation and performance filtering**. Its predictable layout helps
  sequential traversal.
- **Iterative set lookup performed best for our repeated missing-ID search.** It
  follows a short tree path instead of scanning every employee. Repeating the
  same search also keeps that path warm.
- **Recursion was not automatically faster or more cache-friendly.** It adds calls
  and stack activity. A lower miss figure per memory operation can simply mean
  that the recursive version performed more memory operations.
- There is **no single best container for every operation**. Use the per-operation
  rankings in [the full report](results/PARTS_E_G.md).

### Important details to say honestly

We used **Apple Instruments**, not Intel VTune. The assignment permits a profiling
tool such as VTune. Our selected Instruments mode measures **L1 data-cache misses**,
loads/stores, and writebacks. It does **not directly measure cache hits**.

The counter measurements cover repeated benchmark batches, including supporting
work. The elapsed-time timer covers a narrower operation section. These scopes
are documented in the report. A set must create a separate representation to
sort by salary because its existing order is by ID.

The profile searches for ID **-1**, which does not exist. The older timing CSVs
use ID **1001**, the first record. Do not present their search results as the same
experiment. The normal CLI also defaults to 1001.

All final cases passed independent answer checks and had no invalid counter rows
reported by Instruments. These are results from this machine and workload, not
proof that the same rankings hold on every computer.

## 7. Build and demonstrate the program

Run these commands **from the project folder**. This direct Clang build was
verified on this Mac:

```bash
mkdir -p build
clang++ -std=c++17 -O2 -g -Wall -Wextra -Wpedantic -Iinclude src/*.cpp -o build/employee_analytics
```

Start with the small report so the output is easy to explain:

```bash
./build/employee_analytics --file data/employees.txt --container vector
```

Then show that another container produces the same analytics:

```bash
./build/employee_analytics --file data/employees.txt --container list
./build/employee_analytics --file data/employees.txt --container set
```

Show one iterative and recursive salary-total benchmark:

```bash
./build/employee_analytics --mode benchmark --file data/employees_large.txt --container vector --operation aggregate --strategy iterative
./build/employee_analytics --mode benchmark --file data/employees_large.txt --container vector --operation aggregate --strategy recursive
```

Explain: **the checksums should match; the elapsed times can differ**.
These commands time the operations; they do not collect hardware cache counters.
Show `results/PARTS_E_G.md` for the already-collected cache evidence.

Run the automated checks:

```bash
python3 tests/verify.py ./build/employee_analytics
```

For additional options:

```bash
./build/employee_analytics --help
```

### Optional: CMake build

If CMake is installed, this is the project's alternative build/test setup.
CMake itself was unavailable during our review, so these commands were not
verified here; the direct Clang build and tests were verified.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

### Optional: repeat the measurements

```bash
bash scripts/run_benchmarks.sh ./build/employee_analytics data/employees_large.txt results/new_timings.csv
bash scripts/run_cache_profile.sh results/new_profile
```

The second command requires macOS, Xcode Instruments, and permission to access
hardware counters. It takes longer than a normal report. You do not need to run
it live during the presentation; the saved measurements are already available.

## 8. A short presentation script

> “Our project reads employee records and creates a report covering salaries,
> departments, performance, and eligibility for bonuses and promotions.
>
> We tested 35 employees and 6001 employees. We compared vector, list, and set,
> then compared loops with recursive versions of aggregation, filtering, and
> searching. We used Instruments to measure real L1 data-cache misses.
>
> Vector iteration worked well for large sequential calculations. Iterative set
> search worked well for repeated ID lookup because it avoided a full scan.
> Recursion added overhead and was not always better. Our conclusion is that the
> best choice depends on the operation, not just the container's name.
>
> I organized the project and integration, Malaak implemented the employee model
> and vector analytics, and Doston implemented the container comparisons,
> benchmarks, and recursion. We then completed integration checks and profiling
> with Codex assistance.”

**Study order:** read sections 1–4, follow the flow in `main.cpp`, review the core
files in section 5, then practice sections 6–8. Use the detailed Part E–G report
when you need an exact measurement or a deeper explanation.
