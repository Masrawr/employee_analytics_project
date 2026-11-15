#!/usr/bin/env bash
# OWNER: MEMBER 1 — automation runner; it works AFTER Member 2/3 implement TODOs.
set -euo pipefail
cd "$(dirname "$0")/.."
EXE="${1:-./build/employee_analytics}"
DATASET="${2:-data/employees_large.txt}"
mkdir -p results
OUTPUT="results/timings.csv"
printf 'container,strategy,operation,employees,elapsed_ms,checksum\n' > "$OUTPUT"

for container in vector list set; do
  for operation in load sort_salary; do
    "$EXE" --mode benchmark --file "$DATASET" --container "$container" \
      --strategy iterative --operation "$operation" --csv >> "$OUTPUT"
  done
  for strategy in iterative recursive; do
    for operation in aggregate filter_department filter_performance search_id; do
      "$EXE" --mode benchmark --file "$DATASET" --container "$container" \
        --strategy "$strategy" --operation "$operation" --csv >> "$OUTPUT"
    done
  done
done
printf 'Saved timing results to %s\n' "$OUTPUT"
