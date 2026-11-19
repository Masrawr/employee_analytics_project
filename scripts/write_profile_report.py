#!/usr/bin/env python3
"""Merge verified measurements, validate checksums, and render reproducible tables."""
import csv
import math
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'results/profiling'
rows = list(csv.DictReader((BASE / 'cache_summary.csv').open()))
retry = {r['case']: r for r in csv.DictReader((BASE / 'short_retry/cache_summary.csv').open())}
rows = [retry.get(r['case'], r) for r in rows]
assert len(rows) == len({r['case'] for r in rows}) == 60
for r in rows:
    assert float(r['batch_ms']) >= 20 and int(r['counter_intervals']) >= 10, r['case']
    assert int(r['invalid_metric_rows']) == 0
    data = list(csv.reader((ROOT / 'data' / r['dataset']).open(), delimiter='|'))
    expected = {
        'load': len(data),
        'aggregate': sum(float(e[7]) for e in data),
        'filter_department': sum(e[3] == 'Engineering' for e in data),
        'filter_performance': sum(float(e[8]) > 4 for e in data),
        'search_id': 0,
        'sort_salary': sum(i*int(e[0]) for i,e in enumerate(
            sorted(data,key=lambda e:(float(e[7]),int(e[0]))),1)),
    }
    assert int(r['employees']) == len(data)
    assert math.isclose(float(r['checksum']),expected[r['operation']],abs_tol=1e-6)
with (ROOT / 'results/cache_metrics.csv').open('w', newline='') as f:
    writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)

report = ROOT / 'results/PARTS_E_G.md'
text = report.read_text().split('## Measured results')[0]
text += '''## Measured results

All 60 final cases have at least 20 ms of batch duration, at least 10 counter
intervals, and no invalid metric rows reported by Instruments. Every checksum
matches an independent calculation from the dataset. The three short original
cases were replaced by the corrected retry. See `cache_metrics.csv` for raw event
totals, repetition counts, interval coverage, CPU cores and source recording.

“Misses/run” below is estimated L1D load-plus-store misses divided by repetitions,
including the documented batch overhead. “Misses/1k µops” divides total misses
by total load-plus-store micro-operations and multiplies by 1000. Elapsed time
is the mean **instrumented operation-only** time in milliseconds.

'''
for dataset in ('employees.txt','employees_large.txt'):
    text+=f'### {dataset}\n\n| Container | Strategy | Operation | Mean ms | Misses/run | Misses/1k µops |\n|---|---|---|---:|---:|---:|\n'
    for r in rows:
        if r['dataset'] != dataset: continue
        text+=f"| {r['container']} | {r['strategy']} | {r['operation']} | {float(r['elapsed_ms']):.6f} | {float(r['estimated_l1d_misses_per_repetition']):.1f} | {float(r['l1d_misses_per_1000_memory_uops']):.2f} |\n"
    text+='\n'
text+='''## Best and worst configurations in this run

These rankings compare configurations **within the same operation** on 6001
employees. Comparing raw misses across unrelated operations would confound
workload size. Here “best/worst cache” means lowest/highest measured misses per
repetition under the documented scope; it does not claim every cache level or
all memory access patterns were measured. Small differences are not statistically
significant evidence because this is one recording per final case.

| Operation | Fewest L1D misses/run | Most L1D misses/run | Fastest measured | Slowest measured |
|---|---|---|---|---|
'''
for op in ('load','aggregate','filter_department','filter_performance','sort_salary','search_id'):
    group=[r for r in rows if r['dataset']=='employees_large.txt' and r['operation']==op]
    label=lambda r:r['container']+'/'+r['strategy']
    low=min(group,key=lambda r:float(r['estimated_l1d_misses_per_repetition']))
    high=max(group,key=lambda r:float(r['estimated_l1d_misses_per_repetition']))
    fast=min(group,key=lambda r:float(r['elapsed_ms']))
    slow=max(group,key=lambda r:float(r['elapsed_ms']))
    text+=f"| {op} | {label(low)} ({float(low['estimated_l1d_misses_per_repetition']):.1f}) | {label(high)} ({float(high['estimated_l1d_misses_per_repetition']):.1f}) | {label(fast)} | {label(slow)} |\n"
text += """

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
"""
report.write_text(text)
print('Validated all 60 final cases and generated cache_metrics.csv and report tables.')
