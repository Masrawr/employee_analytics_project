# Integration and Test Plan — Member 1 tracks this

These are tests to **run after** Members 2 and 3 complete the TODOs.

- [ ] `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release` and `cmake --build build` succeed.
- [ ] `--mode report --container vector` correctly loads 35 records.
- [ ] `--mode report --container list` shows the same analytics values as vector.
- [ ] `--mode report --container set` shows the same analytics values as vector.
- [ ] The 6001-record dataset loads; total count is 6001 in every container.
- [ ] Average salary/performance and department stats agree for every container.
- [ ] Highest/lowest salaries and full-time/part-time counts agree.
- [ ] Threshold filtering uses `>` (not `>=`) if using the assignment's "above" wording.
- [ ] Bonus/promotion results match the documented rules in README.
- [ ] Empty file yields a safe, meaningful report without dividing by zero.
- [ ] Malformed record causes a useful filename/line-number error.
- [ ] Duplicate IDs are handled consistently (important for `set`).
- [ ] All five Part E operations (and both filtering choices) can be profiled separately.
- [ ] All three containers are compared with the same dataset.
- [ ] Iterative and recursive aggregation/filter/search produce equivalent checksums.
- [ ] Recursive tests do not exhaust stack capacity (document limits if encountered).
- [ ] Actual cache statistics are measured with a profiler; they are not inferred from elapsed time.
- [ ] Charts/tables and presentation conclusions match collected measurements.
