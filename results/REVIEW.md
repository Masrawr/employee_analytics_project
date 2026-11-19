# Assignment compliance review — November 18, 2026

Reviewed all three pages of `../Group Assignment 2.pdf` and the merged project
at commit `7a344cd`. Changes in this review are uncommitted working-tree changes.

## Status against the PDF

| Part | Verified result |
|---|---|
| A | All ten fields, constructors, getters/setters, full name, serialization and three rule methods implemented. Round-trip numeric precision tested. |
| B | 35-record and 6001-record datasets meet the required sizes. Parser creates objects and reports malformed records with file/line details. |
| C | Objects loaded into `vector<Employee>`. |
| D | All ten required report sections implemented and checked against independent calculations. |
| E | All five operation categories implemented; both filter variants included. Actual elapsed-time CSVs saved. L1D measurements and explanations completed in PARTS_E_G.md. |
| F | Direct list/set report traversal and all benchmark operations implemented. Functional parity passed. Measured cache comparison completed in PARTS_E_G.md. |
| G | Actual recursive aggregation, filtering and search implemented and verified. Measured per-operation cache and timing rankings completed in PARTS_E_G.md. |

**Parts A–G are implemented and the required profiling analysis is now supplied.**
The follow-up hardware experiment is documented in `PARTS_E_G.md`, with all 60
final comparisons in `cache_metrics.csv`. Limitations are disclosed there;
CMake/CTest itself remains unverified because CMake is not installed.
The PDF does not explicitly require a slide deck.

## Fixed integration problems

- Restored the commented-out shared `AnalyticsReport` and function declarations,
  added the missing `<map>` include, and updated obsolete Employee getter calls.
- Implemented vector report integration and the missing report printer. Preserved
  Member 3's report traversal in a common helper for vector, list and set.
- Fixed missing parser declarations/namespace usage; rejected partial numeric
  conversions, NaN/infinity, empty/extra fields and inconsistent duplicate IDs.
- Supported CRLF files and whitespace-only blank lines.
- Preserved Member 2's cumulative bonus/promotion rules and documented them.
- Removed obsolete commented-out stubs and preserved serialization precision.
- Made report salary ties deterministic by ID and fixed the zero-salary department
  case in the older `highestAvg` helper.
- Rejected malformed CLI numeric values. Added repeatable automated tests and
  separate CSV destinations so one dataset's results do not overwrite the other.

## Verification performed

- Apple Clang 21.0.0, C++17, `-O2 -g -Wall -Wextra -Wpedantic`: builds with no warnings.
- 226 CLI cases passed against an independent Python oracle, covering both real
  datasets, all 30 benchmark combinations, empty data, ties, exact thresholds,
  end/missing-ID searches, bad records, duplicates and invalid CLI options.
- The same 226 cases passed with AddressSanitizer and UndefinedBehaviorSanitizer.
- Employee unit tests passed under both sanitizers: getters/setters, numeric
  serialization round-trip, bonus/promotion boundaries and zero salaries.
- CMake is not installed here, so CMake/CTest execution remains unverified.
  Equivalent source files were compiled directly; CTest integration was added.

## Recorded elapsed times

Machine: arm64 MacBook Pro, 8 GB RAM, macOS 27.2.1, Apple Clang 21.0.0.
Release-style `-O2 -g` binary; 100 repetitions per row; means in milliseconds.
Inputs, threshold 4.0, department Engineering and search ID 1001 were held fixed.
Both CSVs have 30 rows with matching checksums for equivalent operations.

The following is a descriptive ranking within this one 6001-record timing run,
not a cache ranking or a statistically established speed comparison.

| Operation | Lowest measured mean (ms) | Highest measured mean (ms) |
|---|---|---|
| load | vector/iterative: 4.353578 | set/iterative: 4.885663 |
| sort_salary | list/iterative: 0.607492 | set/iterative: 0.897515 |
| aggregate | vector/iterative: 0.006066 | set/recursive: 0.031035 |
| filter_department | list/iterative: 0.016344 | set/recursive: 0.042722 |
| filter_performance | vector/iterative: 0.006195 | set/recursive: 0.031082 |
| search_id | list/iterative: 0.000018 | vector/iterative: 0.000062 |

Search ID 1001 is first in the input: these search times are extremely short and
near timer/noise limits. Do not use that ranking to recommend a search algorithm.
The tests also verify last/missing-ID searches but do not claim timings for them.
Set iterative search is tree lookup, unlike recursive sequential search. Set
sorting includes conversion to a vector; vector/list copying is outside timing.
List/set loading includes an intermediate vector. See README for all boundaries.

## Completed profiling follow-up

The initial CPU Bottlenecks smoke test was superseded by a configured Instruments
L1D Cache Metrics experiment. It measured both datasets, all three containers,
six operations and appropriate recursive counterparts (60 combinations).
Three short intervals were replaced by longer recordings. Every final case has
at least 20 ms batch duration, at least 10 counter intervals, matching independently
computed checksums, and zero invalid metric rows reported by Instruments.

See `PARTS_E_G.md` for the full analysis, per-operation rankings, exact counter
semantics and measurement limitations. `cache_metrics.csv` contains final measured
values and provenance. The selected mode does not directly count hits; these are
marked unmeasured. This is a disclosed tool limitation, not a fabricated value.
