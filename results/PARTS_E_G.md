# Parts E–G: cache profiling, containers, and recursion

## Experiment

Hardware: Apple Silicon MacBook Pro, 8 GB RAM. Software: macOS 27.2.1,
Apple Clang 21.0.0, C++17, `-O2 -g`; Instruments 27.2 CPU Counters in
**L1D Cache Metrics** mode, user-space (`EL0`) counting.

The 35- and 6001-employee datasets are used for all three containers. The six
operations cover all five required code sections: loading, aggregation,
department filtering, performance filtering, salary sorting and ID searching.
Aggregation, both filters and searching have actual recursive counterparts.
File loading and standard-library sorting retain their appropriate nonrecursive
implementations, yielding 30 combinations per dataset (60 total).

Threshold is 4.0, department is Engineering, and profiled ID searches use -1,
which is absent. Sequential searches must therefore scan the entire input.
Iterative set search uses `set.find`, so that comparison includes the change
from linear scan to logarithmic tree lookup, not just iteration versus recursion.

The harness marks every benchmark batch with an `EmployeeCase` signpost. Only
counter samples overlapping that case, on its main thread, are assigned to it.
Boundary samples are prorated by overlap: these are interval estimates from
hardware measurements, not exact instruction-by-instruction attribution.

Cache totals refer to the **complete benchmark batch**: one-time setup,
repeated operations, timing/checksum bookkeeping and teardown. Loading includes
parsing, validation, construction and destruction; list/set also use a temporary
vector. Sorting includes fresh copies, sorting, checksum traversal and destruction.
Repeated traversal/filter/search batches amortize the one-time load. Mean elapsed
milliseconds from `runBenchmark` cover its narrower operation-only timer scope;
they must not be treated as the duration of the entire profiled batch.

The first run calibrated repetition counts from whole-batch time. The updated
harness calibrates from operation time to avoid undersampling very fast set
lookup. The two iterative set-search cases and the small-set recursive performance
filter are repeated using corrected calibration; the replacements are identified
in the results.

## Counter definitions and limits

The installed Instruments `RecountDT.framework/Resources/Analysis/metrics.json`
defines the events used here:

- `ld_uop_spec`: speculative micro-operations through the Load Unit.
- `st_uop_spec`: speculative micro-operations through the Store Unit.
- `l1d_miss_ld_spec`: speculative loads that missed L1D.
- `l1d_miss_st_spec`: speculative stores that missed L1D.
- `l1d_writeback`: dirty cache lines written toward shared L2.
- `cycle`: active CPU cycles.

The report uses **L1D misses per 1,000 load/store micro-operations** as a
normalized comparison, not an exact demand-access miss probability. A load/store
micro-operation is not guaranteed to correspond one-to-one with a cache access.
This mode does not directly measure cache hits, so hits are marked unmeasured;
subtracting misses from micro-operations would not establish a reliable hit count.

These are warm, repeated workloads. OS file caching, string allocation, background
activity, frequency scaling, scheduler migration and instrumentation can affect
results. Speculative events include work that may not retire. The recorded core
IDs are retained, rather than assuming every case ran on the same core. Rankings
are descriptive for this experiment, not universal properties of containers.
## Measured results

All 60 final cases have at least 20 ms of batch duration, at least 10 counter
intervals, and no invalid metric rows reported by Instruments. Every checksum
matches an independent calculation from the dataset. The three short original
cases were replaced by the corrected retry. See `cache_metrics.csv` for raw event
totals, repetition counts, interval coverage, CPU cores and source recording.

“Misses/run” below is estimated L1D load-plus-store misses divided by repetitions,
including the documented batch overhead. “Misses/1k µops” divides total misses
by total load-plus-store micro-operations and multiplies by 1000. Elapsed time
is the mean **instrumented operation-only** time in milliseconds.

### employees.txt

| Container | Strategy | Operation | Mean ms | Misses/run | Misses/1k µops |
|---|---|---|---:|---:|---:|
| vector | iterative | load | 0.089396 | 4641.1 | 39.03 |
| vector | iterative | aggregate | 0.000040 | 0.1 | 0.47 |
| vector | recursive | aggregate | 0.000139 | 0.1 | 0.21 |
| vector | iterative | filter_department | 0.000069 | 0.1 | 0.39 |
| vector | recursive | filter_department | 0.000153 | 0.2 | 0.28 |
| vector | iterative | filter_performance | 0.000040 | 0.1 | 0.48 |
| vector | recursive | filter_performance | 0.000134 | 0.1 | 0.12 |
| vector | iterative | sort_salary | 0.001513 | 0.6 | 0.04 |
| vector | iterative | search_id | 0.000048 | 0.0 | 0.26 |
| vector | recursive | search_id | 0.000108 | 0.0 | 0.08 |
| list | iterative | load | 0.051264 | 4771.3 | 38.74 |
| list | iterative | aggregate | 0.000041 | 0.0 | 0.12 |
| list | recursive | aggregate | 0.000128 | 0.1 | 0.11 |
| list | iterative | filter_department | 0.000072 | 0.0 | 0.11 |
| list | recursive | filter_department | 0.000141 | 0.0 | 0.06 |
| list | iterative | filter_performance | 0.000049 | 0.0 | 0.17 |
| list | recursive | filter_performance | 0.000128 | 0.0 | 0.06 |
| list | iterative | sort_salary | 0.000753 | 0.3 | 0.04 |
| list | iterative | search_id | 0.000052 | 0.0 | 0.20 |
| list | recursive | search_id | 0.000107 | 0.1 | 0.14 |
| set | iterative | load | 0.051834 | 4575.4 | 36.21 |
| set | iterative | aggregate | 0.000076 | 0.0 | 0.09 |
| set | recursive | aggregate | 0.000135 | 0.0 | 0.07 |
| set | iterative | filter_department | 0.000123 | 0.0 | 0.09 |
| set | recursive | filter_department | 0.000181 | 0.1 | 0.09 |
| set | iterative | filter_performance | 0.000073 | 0.0 | 0.10 |
| set | recursive | filter_performance | 0.000154 | 0.1 | 0.14 |
| set | iterative | sort_salary | 0.001731 | 0.9 | 0.07 |
| set | iterative | search_id | 0.000021 | 0.0 | 0.07 |
| set | recursive | search_id | 0.000141 | 0.0 | 0.07 |

### employees_large.txt

| Container | Strategy | Operation | Mean ms | Misses/run | Misses/1k µops |
|---|---|---|---:|---:|---:|
| vector | iterative | load | 5.116254 | 457294.1 | 23.50 |
| vector | iterative | aggregate | 0.007012 | 11349.5 | 850.60 |
| vector | recursive | aggregate | 0.024891 | 14790.5 | 162.75 |
| vector | iterative | filter_department | 0.017908 | 14588.1 | 247.43 |
| vector | recursive | filter_department | 0.031071 | 13275.8 | 87.97 |
| vector | iterative | filter_performance | 0.006719 | 11084.1 | 575.21 |
| vector | recursive | filter_performance | 0.024612 | 14788.3 | 152.39 |
| vector | iterative | sort_salary | 0.849816 | 140914.9 | 31.61 |
| vector | iterative | search_id | 0.008281 | 10847.9 | 563.44 |
| vector | recursive | search_id | 0.017861 | 14896.1 | 186.03 |
| list | iterative | load | 14.734563 | 594815.7 | 28.90 |
| list | iterative | aggregate | 0.077349 | 17679.2 | 505.73 |
| list | recursive | aggregate | 0.083928 | 15979.0 | 154.76 |
| list | iterative | filter_department | 0.064726 | 19727.8 | 244.78 |
| list | recursive | filter_department | 0.043488 | 18196.1 | 108.02 |
| list | iterative | filter_performance | 0.020113 | 17390.8 | 432.54 |
| list | recursive | filter_performance | 0.053765 | 16338.8 | 156.13 |
| list | iterative | sort_salary | 1.100134 | 248197.1 | 93.28 |
| list | iterative | search_id | 0.069708 | 15310.2 | 393.26 |
| list | recursive | search_id | 0.050263 | 15147.7 | 204.06 |
| set | iterative | load | 7.195454 | 548968.6 | 25.34 |
| set | iterative | aggregate | 0.028566 | 19071.9 | 382.80 |
| set | recursive | aggregate | 0.045924 | 18244.9 | 145.26 |
| set | iterative | filter_department | 0.034715 | 19897.9 | 214.97 |
| set | recursive | filter_department | 0.045643 | 19599.8 | 112.60 |
| set | iterative | filter_performance | 0.030779 | 19067.5 | 328.25 |
| set | recursive | filter_performance | 0.035333 | 18327.3 | 138.57 |
| set | iterative | sort_salary | 0.970915 | 162441.8 | 35.64 |
| set | iterative | search_id | 0.000022 | 0.1 | 0.39 |
| set | recursive | search_id | 0.039397 | 7969.6 | 75.58 |

## Best and worst configurations in this run

These rankings compare configurations **within the same operation** on 6001
employees. Comparing raw misses across unrelated operations would confound
workload size. Here “best/worst cache” means lowest/highest measured misses per
repetition under the documented scope; it does not claim every cache level or
all memory access patterns were measured. Small differences are not statistically
significant evidence because this is one recording per final case.

| Operation | Fewest L1D misses/run | Most L1D misses/run | Fastest measured | Slowest measured |
|---|---|---|---|---|
| load | vector/iterative (457294.1) | list/iterative (594815.7) | vector/iterative | list/iterative |
| aggregate | vector/iterative (11349.5) | set/iterative (19071.9) | vector/iterative | list/recursive |
| filter_department | vector/recursive (13275.8) | set/iterative (19897.9) | vector/iterative | list/iterative |
| filter_performance | vector/iterative (11084.1) | set/iterative (19067.5) | vector/iterative | list/recursive |
| sort_salary | vector/iterative (140914.9) | list/iterative (248197.1) | vector/iterative | list/iterative |
| search_id | set/iterative (0.1) | list/iterative (15310.2) | set/iterative | list/iterative |


## Why the operations behave differently (Parts E and F)

**File loading/object construction:** this is a mixed workload: sequential file
reads are friendly to locality, but parsing, strings, duplicate-ID validation and
allocations touch more locations. List and set construction add separate nodes
and tree/list bookkeeping after the shared vector loader. Their measured totals
must include that extra work; they are not pure comparisons of disk speed.
Repeated loads also benefit from the OS page cache.

**Sequential aggregation:** the vector places Employee objects contiguously.
Walking them gives the CPU a predictable address stream, whereas list/set follow
node links. An Employee contains several strings and fields, so its salary is
only a small part of its footprint: contiguous objects do not imply all salary
reads hit L1. In the large dataset, vector iteration has fewer measured misses
per aggregation than list/set iteration. This supports its locality advantage
for this workload, while the nonzero miss count reflects the working-set size.

**Filtering:** the performance filter reads a numeric field at predictable
positions. Department filtering additionally accesses strings and compares
characters, so the observed memory-operation volume and branch behavior differ.
The vector layout generally helps traversal, but the department-filter result
also shows that fewer cache misses need not imply the lowest elapsed time.
A filtering operation here counts matches; full report mode also copies matching
employees, which is a different workload and is not being claimed as profiled.

**Salary sorting:** vector sorting rearranges relatively large Employee objects;
list sorting relinks nodes and follows pointers. The ID-ordered set cannot be
reordered by salary, so its pipeline creates and sorts a separate vector.
Measured batch counters include copies, checksums and destruction for these
pipelines; the narrow timer excludes the initial copy for vector/list but includes
set conversion. Consequently the table compares complete implementations, not
three identical sorting algorithms. On this run the vector pipeline has the
fewest large-dataset L1D misses and shortest measured operation time.

**ID searching:** a missing-ID scan touches every employee for vector/list and
all recursive variants. Iterative set search visits only a logarithmic path.
Repeated lookup of the same missing ID keeps that small tree path warm, explaining
its very low misses per repetition after setup is amortized. This result does not
mean the tree is preferable for scanning or sorting, nor does it establish
performance for random IDs or cold-cache searches.

The 35-record results are also included above. Much more of their working sets
can remain warm, and timer/checksum/allocator overhead becomes a larger fraction
of the work. Compare small and large inputs using the recorded numbers, rather
than extrapolating tiny-workload timings to the 6001-record case.

## Iteration versus recursion (Part G)

The recursive code splits each traversal by count and advances a shared cursor
in traversal order. This uses actual recursive calls, O(n) work and O(log n)
stack depth. It does not recursively copy containers. Loading and library sorting
have no recursive replacements because those replacements are not appropriate
for this implementation; the handout explicitly qualifies recursion with
“where appropriate.”

Recursion preserves the main container access order but adds call/control flow
and stack accesses. Its lower misses per 1,000 memory micro-operations can reflect
additional mostly-local stack traffic increasing the denominator. The
misses-per-repetition and elapsed-time columns are therefore essential: a lower
normalized miss figure alone does not prove improved data locality. The large
vector aggregation results illustrate this: recursion has a lower normalized
miss figure but more misses per run and a longer execution time than iteration.

There is no defensible single winner across unrelated operations. For the large
aggregation and numeric-filter workloads, vector iteration is the best measured
configuration by misses per run. Repeated missing-ID lookup strongly favors the
iterative set algorithm. The per-operation best/worst table states the remaining
observed rankings. Scheduler/core changes, instrumentation overhead and the lack
of independent repeated recording trials limit small-difference conclusions.

## Evidence and reproduction

- `cache_metrics.csv`: all 60 final cases, raw event totals and derived metrics.
- `profiling/cache_summary.csv` and `profiling/short_retry/cache_summary.csv`:
  original and replacement measurements with trace provenance.
- `profiling/*/` and `profiling/`: counter/signpost XML exports (counter XML also
  compressed), invalid-counter tables, timing CSVs and locally retained traces.
- `scripts/cache_recording_options.json`: selected Instruments counter settings.
- `scripts/profile_driver.cpp`: labeled benchmark harness, corrected calibration.
- `scripts/trace_xml.py`, `summarize_cache_profile.py`, `write_profile_report.py`:
  reference resolution, interval attribution, checksum verification and reporting.

Run `bash scripts/run_cache_profile.sh results/new_profile` from the project root
to make a fresh 60-case recording without overwriting this evidence. The runner
compiles its own harness, records, exports and creates a cache summary. Hardware
counter access requires Xcode Instruments and may require macOS authorization.
The original recording plus the three-case retry are retained for reproducibility;
the corrected harness uses longer intervals for new recordings.
