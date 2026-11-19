#pragma once

#include "Analytics.h"
#include <map>

// Traverse each original container directly; share the report rules.
namespace AnalyticsDetail {
struct DepartmentTotals {
    std::size_t count{};
    double salary{};
};

template <typename Container>
AnalyticsReport analyze(const Container& employees, double threshold) {
    AnalyticsReport report;
    report.threshold = threshold;
    report.totalEmployees = employees.size();
    if (employees.empty()) {
        return report;
    }

    std::map<std::string, DepartmentTotals> departments;
    double totalSalary = 0.0;
    double totalPerformance = 0.0;
    for (const Employee& employee : employees) {
        const double salary = employee.getSalary();
        const double score = employee.getPerformanceScore();
        totalSalary += salary;
        totalPerformance += score;

        if (!report.highestPaid || salary > report.highestPaid->getSalary() ||
            (salary == report.highestPaid->getSalary() &&
             employee.getEmployeeId() < report.highestPaid->getEmployeeId())) {
            report.highestPaid = employee;
        }
        if (!report.lowestPaid || salary < report.lowestPaid->getSalary() ||
            (salary == report.lowestPaid->getSalary() &&
             employee.getEmployeeId() < report.lowestPaid->getEmployeeId())) {
            report.lowestPaid = employee;
        }

        auto& department = departments[employee.getDepartment()];
        ++department.count;
        department.salary += salary;

        if (employee.isFullTime()) {
            ++report.fullTimeCount;
        } else {
            ++report.partTimeCount;
        }
        if (score > threshold) {
            report.aboveThreshold.push_back(employee);
        }
        if (employee.isEligibleForPromotion()) {
            report.promotionEligible.push_back(employee);
        }
        if (employee.annualBonusEstimate() > 0.0) {
            report.bonusEligible.push_back(employee);
        }
    }

    report.averageSalary = totalSalary / report.totalEmployees;
    report.averagePerformanceScore = totalPerformance / report.totalEmployees;
    double bestAverage = 0.0;
    for (const auto& [name, totals] : departments) {
        const double average = totals.salary / totals.count;
        if (report.departments.empty() || average > bestAverage) {
            report.highestAverageSalaryDepartment = name;
            bestAverage = average;
        }
        report.departments.push_back({name, totals.count, average});
    }
    return report;
}
} // namespace AnalyticsDetail
