#!/usr/bin/env python3
"""Join xctrace counter intervals to benchmark signposts; never invent hit counts."""
import bisect
import csv
from pathlib import Path
import sys
from trace_xml import rows

EVENTS = ('cycle', 'ld_uop_spec', 'st_uop_spec', 'l1d_miss_ld_spec',
          'l1d_miss_st_spec', 'l1d_writeback')


def summarize(directory):
    directory = Path(directory)
    timing = {r['case']: r for r in csv.DictReader((directory / 'profile_timings.csv').open())}
    cases = []
    for row in rows(directory / 'OSSignpostIntervals.xml'):
        if row['name'][0] != 'EmployeeCase' or row['subsystem'][0] != 'edu.csc326.employee':
            continue
        label = row['start-message'][0]
        assert label == row['end-message'][0] and label in timing
        start = int(row['start'][0])
        duration = int(row['duration'][0])
        cases.append(dict(label=label, start=start, end=start+duration,
                          thread=row['start-thread'][0], totals=dict.fromkeys(EVENTS, 0.0),
                          samples=0, covered_ns=0, cores=set(), boundaries=0))
    cases.sort(key=lambda c: c['start'])
    assert len(cases) == len(timing), (len(cases), len(timing))
    assert all(a['end'] <= b['start'] for a, b in zip(cases, cases[1:]))
    starts = [c['start'] for c in cases]
    for row in rows(directory / 'MetricTable.xml'):
        event = row['pmi-event'][0]
        if event not in EVENTS:
            continue
        start = int(row['timestamp'][0])
        duration = int(row['duration'][0])
        value = float(row['metric-value'][0])
        assert value >= 0 and duration >= 0
        if not duration:
            continue
        end = start + duration
        index = max(0, bisect.bisect_right(starts, start)-1)
        while index < len(cases) and cases[index]['start'] < end:
            case = cases[index]
            overlap = max(0, min(end, case['end']) - max(start, case['start']))
            if overlap and row['thread'][0] == case['thread']:
                case['totals'][event] += value * overlap / duration
                if event == 'cycle':
                    case['samples'] += 1
                    case['covered_ns'] += overlap
                    case['cores'].add(row['core'][1])
                    case['boundaries'] += int(overlap < duration)
            index += 1
    invalid_path = directory / 'InvalidMetricTable.xml'
    invalid_count = sum(1 for _ in rows(invalid_path)) if invalid_path.exists() else None
    assert invalid_count == 0, f'Inspect invalid metrics before publishing: {invalid_count}'
    output = []
    for case in cases:
        result = dict(timing[case['label']])
        result.update(case['totals'])
        result['batch_ms'] = (case['end']-case['start'])/1e6
        result['sampled_main_thread_ms'] = case['covered_ns']/1e6
        result['counter_intervals'] = case['samples']
        result['boundary_intervals'] = case['boundaries']
        result['cores'] = '; '.join(sorted(case['cores']))
        result['cache_hits'] = 'not directly measured'
        misses = result['l1d_miss_ld_spec'] + result['l1d_miss_st_spec']
        memory_ops = result['ld_uop_spec'] + result['st_uop_spec']
        assert memory_ops > 0 and case['samples'] > 0, case['label']
        result['l1d_misses_per_1000_memory_uops'] = 1000*misses/memory_ops
        result['estimated_l1d_misses_per_repetition'] = misses/int(result['repetitions'])
        result['invalid_metric_rows'] = invalid_count
        result['source'] = str(directory)
        output.append(result)
    destination = directory / 'cache_summary.csv'
    with destination.open('w', newline='') as stream:
        writer = csv.DictWriter(stream, fieldnames=list(output[0]))
        writer.writeheader()
        writer.writerows(output)
    print(f'Summarized {len(output)} cases to {destination}; invalid rows: {invalid_count}')
    for result in output:
        if result['batch_ms'] < 20 or result['counter_intervals'] < 10:
            print('SHORT CASE:', result['case'], result['batch_ms'], result['counter_intervals'])
    return output


if __name__ == '__main__':
    summarize(sys.argv[1])
