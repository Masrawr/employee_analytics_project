#!/usr/bin/env python3
"""Independent CSV-based oracle for reports, benchmark operations, and invalid input.
Usage: python3 tests/verify.py /path/to/employee_analytics
"""
import csv
import math
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EXE = str(Path(sys.argv[1]).resolve())
checks = 0


def run(*args, ok=True):
    global checks
    result = subprocess.run([EXE, *map(str, args)], text=True, capture_output=True, cwd=ROOT)
    assert (result.returncode == 0) == ok, (args, result.stdout, result.stderr)
    checks += 1
    return result.stdout if ok else result.stderr


def verify(path):
    with open(path) as file:
        records = list(csv.reader(file, delimiter='|'))
    n = len(records)
    salaries = [float(r[7]) for r in records]
    scores = [float(r[8]) for r in records]
    expected = {
        'load': n,
        'aggregate': sum(salaries),
        'filter_department': sum(r[3] == 'Engineering' for r in records),
        'filter_performance': sum(s > 4 for s in scores),
        'search_id': int(any(int(r[0]) == 1001 for r in records)),
        'sort_salary': sum(i * int(r[0]) for i, r in enumerate(
            sorted(records, key=lambda r: (float(r[7]), int(r[0]))), 1)),
    }
    for container in ('vector', 'list', 'set'):
        report = run('--file', path, '--container', container)
        def contains(text):
            assert text in report, (container, text)
        contains(f'Total employees: {n}\n')
        contains(f'Average salary: {sum(salaries) / n if n else 0:.2f}\n')
        contains(f'Average performance score: {sum(scores) / n if n else 0:.2f}\n')
        full = sum(r[9] == '1' for r in records)
        contains(f'Full-time employees: {full}\n')
        contains(f'Part-time employees: {n - full}\n')
        for label, sign in [('Highest', -1), ('Lowest', 1)]:
            if records:
                r = min(records, key=lambda r: (sign * float(r[7]), int(r[0])))
                contains(f'{label}-paid employee: {r[1]} {r[2]} (ID {r[0]}), salary {float(r[7]):.2f}\n')
            else:
                contains(f'{label}-paid employee: N/A\n')
        departments = sorted({r[3] for r in records})
        averages = {}
        for department in departments:
            selected = [r for r in records if r[3] == department]
            averages[department] = sum(float(r[7]) for r in selected) / len(selected)
            contains(f'  {department}: {len(selected)}, {averages[department]:.2f}\n')
        best = max(departments, key=lambda d: averages[d]) if departments else 'N/A'
        contains(f'Department with highest average salary: {best}\n')
        above = [r for r in records if float(r[8]) > 4]
        promoted = [r for r in records if int(r[6]) >= 3 and float(r[8]) >= 4]
        bonuses = [(r, float(r[7]) * ((.15 if int(r[6]) >= 5 else 0) +
                   (.10 if float(r[8]) >= 4 else 0) + (.02 if r[9] == '1' else 0))) for r in records]
        bonuses = [(r, b) for r, b in bonuses if b > 0]
        contains(f'Employees above performance threshold 4.00 ({len(above)}):\n')
        contains(f'Promotion eligible ({len(promoted)}):\n')
        contains(f'Bonus eligible ({len(bonuses)}):\n')
        for r in above:
            contains(f'  {r[0]} | {r[1]} {r[2]} | score {float(r[8]):.2f}\n')
        promotion_section = report.split('Promotion eligible (')[1].split('Bonus eligible (')[0]
        for r in promoted:
            assert f'  {r[0]} | {r[1]} {r[2]}\n' in promotion_section
        for r, bonus in bonuses:
            contains(f'  {r[0]} | {r[1]} {r[2]} | bonus {bonus:.2f}\n')
        for operation, checksum in expected.items():
            strategies = ('iterative',) if operation in ('load', 'sort_salary') else ('iterative', 'recursive')
            for strategy in strategies:
                output = run('--file', path, '--container', container, '--mode', 'benchmark',
                             '--operation', operation, '--strategy', strategy, '--csv', '--repetitions', 2)
                row = next(csv.reader([output.strip()]))
                assert row[:4] == [container, strategy, operation, str(n)], row
                assert math.isfinite(float(row[4])) and float(row[4]) >= 0
                assert math.isclose(float(row[5]), checksum, abs_tol=1e-6), (row, checksum)
        for search_id in (-1, int(records[-1][0]) if records else 1001):
            for strategy in ('iterative', 'recursive'):
                output = run('--file', path, '--container', container, '--mode', 'benchmark',
                             '--operation', 'search_id', '--strategy', strategy, '--search-id', search_id, '--csv')
                assert float(output.strip().split(',')[-1]) == any(int(r[0]) == search_id for r in records)


for filename in ('employees.txt', 'employees_large.txt'):
    verify(ROOT / 'data' / filename)
with tempfile.TemporaryDirectory() as directory:
    path = Path(directory) / 'fixture.txt'
    path.write_text('')
    verify(path)
    # Unsorted IDs, salary ties, exact threshold, zero salary, part-time promotion.
    path.write_text('3|A|Three|Z|Dev|30|5|100|4|0\n'
                    '1|B|One|A|Dev|30|3|100|4.5|1\n'
                    '2|C|Two|Z|Dev|30|0|0|3|0\n')
    verify(path)
    base = '1|A|B|Engineering|Dev|30|3|100|4|1'
    invalid = [base + '|', base + '|extra', base[:-1], base[:-1] + '2',
               base.replace('100|4', '100oops|4'), base.replace('100|4', 'nan|4'),
               base.replace('100|4', 'inf|4'), base.replace('100|4', '-1|4'),
               base.replace('30|3', '30x|3'), base.replace('|A|', '||'),
               base.replace('30|3', '999999999999999999999|3'), base + '\n' + base]
    for record in invalid:
        path.write_text(record + '\n')
        for container in ('vector', 'list', 'set'):
            error = run('--file', path, '--container', container, ok=False)
            assert str(path) in error and 'line ' in error, error
    path.write_bytes((' \r\n' + base + '\r\n').encode())
    assert 'Total employees: 1\n' in run('--file', path)
for args in [('--threshold', 'nan'), ('--threshold', '4oops'), ('--repetitions', '2x'),
             ('--search-id', '1x'), ('--repetitions', '0'), ('--container', 'bad'),
             ('--file', '/nonexistent/employee-input.txt'), ('--csv',),
             ('--mode', 'benchmark', '--strategy', 'recursive', '--operation', 'sort_salary')]:
    run(*args, ok=False)
print(f'PASS: {checks} CLI cases; independent report and benchmark checks on both datasets, empty input, ties, and malformed records.')
