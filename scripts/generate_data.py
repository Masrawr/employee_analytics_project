#!/usr/bin/env python3
"""MEMBER 1: Deterministic data generator, no external packages needed.
Run from the project root: python3 scripts/generate_data.py
Writes 35 employees to data/employees.txt and 6001 to data/employees_large.txt.
"""
from pathlib import Path
import argparse
import random

DEPARTMENTS = {
    "Engineering": ("Software Engineer", "Data Analyst", "Systems Engineer"),
    "HR": ("HR Officer", "Recruiter", "HR Specialist"),
    "Finance": ("Accountant", "Financial Analyst", "Controller"),
    "Marketing": ("Marketing Associate", "Brand Manager", "Content Specialist"),
    "Operations": ("Operations Coordinator", "Operations Manager", "Planner"),
    "Sales": ("Sales Representative", "Account Manager", "Sales Analyst"),
}
FIRST = ("Amina", "John", "Linda", "Brian", "Grace", "Sara", "Omar", "Maya",
         "Noah", "Leah", "Zara", "Daniel", "Ella", "Adam", "Iris", "Sam")
LAST = ("Kato", "Okello", "Nabwire", "Ssemanda", "Nansubuga", "Patel",
        "Lee", "Garcia", "Wilson", "Ali", "Reed", "Martin", "Chen", "Khan")

# First five records are copied from the assignment example.
EXAMPLES = [
    "1001|Amina|Kato|Engineering|Software Engineer|29|4|72000|4.3|1",
    "1002|John|Okello|HR|HR Officer|35|7|54000|3.8|1",
    "1003|Linda|Nabwire|Finance|Accountant|41|10|68000|4.1|1",
    "1004|Brian|Ssemanda|Engineering|Data Analyst|26|2|61000|4.6|1",
    "1005|Grace|Nansubuga|Marketing|Marketing Associate|31|5|50000|3.9|0",
]


def generate_records(count: int) -> list[str]:
    if count < len(EXAMPLES):
        raise ValueError(f"At least {len(EXAMPLES)} records required")
    rng = random.Random(326)  # same contents on every run
    records = list(EXAMPLES)
    departments = list(DEPARTMENTS)
    for n in range(len(EXAMPLES), count):
        department = rng.choice(departments)
        job = rng.choice(DEPARTMENTS[department])
        first = rng.choice(FIRST)
        last = rng.choice(LAST)
        age = rng.randint(21, 64)
        years = rng.randint(0, min(38, age - 18))
        salary = rng.randrange(38000, 160001, 500)
        performance = round(rng.uniform(2.5, 5.0), 1)
        full_time = 1 if rng.random() < 0.8 else 0
        records.append(
            f"{1001 + n}|{first}|{last}|{department}|{job}|{age}|{years}|"
            f"{salary}|{performance:.1f}|{full_time}"
        )
    return records


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--small", type=int, default=35)
    parser.add_argument("--large", type=int, default=6001)
    args = parser.parse_args()
    if not 20 <= args.small <= 100:
        parser.error("Small dataset must have 20–100 employees")
    if args.large <= 5000:
        parser.error("Large dataset must have more than 5000 employees")
    data_dir = Path(__file__).resolve().parent.parent / "data"
    data_dir.mkdir(parents=True, exist_ok=True)
    for path, count in ((data_dir / "employees.txt", args.small),
                        (data_dir / "employees_large.txt", args.large)):
        path.write_text("\n".join(generate_records(count)) + "\n", encoding="utf-8")
        print(f"Created {path} with {count} employees")


if __name__ == "__main__":
    main()
