# Presentation Outline — OWNER: Masroor

Keep the presentation based on *measured* results. Do not fill tables with fabricated numbers.

## Slide 1 — Title
**Employee Analytics in C++: STL Containers, Cache Behavior, and Recursion**
Group Assignment #2, CSC 326 Data Structures; group members and submission date.

## Slide 2 — Problem & Requirements (Parts A–D)
10-field Employee class; pipe-separated file; vector; salary, performance,
headcounts, department stats, promotion/bonus analyses.

## Slide 3 — Program Design
Diagram: employees.txt → parseRecord → vector<Employee> → analytics report;
parallel branches for list<Employee> and set<Employee>.
Mention encapsulation and EmployeeIdLess used by set.

## Slide 4 — Datasets & Methods
Small dataset: 35 employees; large dataset: 6001 employees.
Explain fixed seed, identical input for every container, release build, repeated timings.

## Slide 5 — Profiling Operations (Part E)
Loading/object construction, sequential aggregation, filters by department/score,
salary sorting, searching by ID. Tools used and hardware counters actually captured.

## Slide 6 — Vector vs List vs Set (Part F)
Insert actual timing chart and cache-miss table by operation.
Explain contiguous storage versus pointer-linked nodes versus tree nodes.
Caution: set is ordered by employee ID, and salary sorting requires a separate representation.

## Slide 7 — Iteration vs Recursion (Part G)
Insert actual results table for aggregate, filter and search, for each container.
Discuss function call overhead, memory locality, and recursive call-stack effects.

## Slide 8 — Best/Worst Configuration
State the fastest/slowest and best/worst cache results **according to measurements**.
Avoid presenting general expectations as actual empirical results.

## Slide 9 — Lessons & Limitations
Timing is not the same as cache hits/misses; why workloads must be comparable;
profiler access, set ordering, dataset scale and recursion stack limits.

## Slide 10 — Contributions & Questions
Member 1: project organization/data/build/presentation/integration.
Member 2: Employee model/file loading/vector analytics.
Member 3: list/set, benchmarking and recursive comparison.
