#!/usr/bin/env bash
# Requires macOS with Xcode Instruments; hardware-counter access may prompt.
set -euo pipefail
cd "$(dirname "$0")/.."
OUTPUT="${1:-results/profiling}"
mkdir -p "$OUTPUT" build
OUTPUT="$(cd "$OUTPUT" && pwd)"
if [[ -e "$OUTPUT/employee_l1d.trace" ]]; then
    echo "Recording already exists; choose a new output directory to preserve it." >&2
    exit 1
fi
clang++ -std=c++17 -O2 -g -Wall -Wextra -Wpedantic -Iinclude \
    scripts/profile_driver.cpp src/Employee.cpp src/EmployeeIO.cpp \
    src/EmployeeContainers.cpp src/RecursiveAlgorithms.cpp src/Benchmark.cpp \
    -o build/profile_driver
xcrun xctrace record --template 'CPU Counters' \
    --recording-options scripts/cache_recording_options.json \
    --output "$OUTPUT/employee_l1d.trace" \
    --launch -- "$PWD/build/profile_driver" "$PWD" "$OUTPUT/profile_timings.csv"
for schema in MetricTable OSSignpostIntervals InvalidMetricTable; do
    xcrun xctrace export --input "$OUTPUT/employee_l1d.trace" \
        --xpath "/trace-toc/run[@number=\"1\"]/data/table[@schema=\"$schema\"]" \
        --output "$OUTPUT/$schema.xml"
done
xcrun xctrace export --input "$OUTPUT/employee_l1d.trace" --toc --output "$OUTPUT/toc.xml"
python3 scripts/summarize_cache_profile.py "$OUTPUT"
