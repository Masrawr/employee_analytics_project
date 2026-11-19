# Verification

Run `python3 tests/verify.py ./build/employee_analytics` after building, or use
`ctest --test-dir build --output-on-failure` with CMake and Python 3 installed.
The C++ unit test is `tests/employee_tests.cpp`.

Verified during the November 18 review:

- [x] Direct C++17 Clang build with warnings enabled.
- [x] 226 CLI cases, including independent expected report values and checksums.
- [x] Both supplied datasets and all three containers.
- [x] Iterative/recursive parity, present/last/missing-ID searches and sorting checksums.
- [x] Empty inputs, salary ties, threshold equality, CRLF and malformed input.
- [x] Consistent duplicate-ID rejection with useful filename/line-number errors.
- [x] Employee serialization precision, accessors and analytics rule boundaries.
- [x] AddressSanitizer and UndefinedBehaviorSanitizer checks.
- [x] Actual elapsed-time CSVs for both datasets, 100 repetitions per combination.
- [ ] CMake/CTest execution (CMake unavailable on this machine).
- [x] Hardware L1D counters for 60 combinations; corrected short intervals, zero invalid-counter rows, independent checksum validation, measured explanations.

See `results/REVIEW.md` for evidence, limitations and outstanding submission work.
