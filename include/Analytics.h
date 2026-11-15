#pragma once

#include "Employee.h"
#include "EmployeeContainers.h"
#include <cstddef>
#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

struct DepartmentSummary {
    std::string name;
    std::size_t employeeCount{0};
    double averageSalary{0.0};
};

// Shared report format for every container, so outputs are comparable.
struct AnalyticsReport {
    std::size_t totalEmployees{0};
    double averageSalary{0.0};
    std::optional<Employee> highestPaid;
    std::optional<Employee> lowestPaid;
    double averagePerformanceScore{0.0};
    std::vector<DepartmentSummary> departments;
    std::string highestAverageSalaryDepartment;
    std::size_t fullTimeCount{0};
    std::size_t partTimeCount{0};
    double threshold{4.0};
    std::vector<Employee> aboveThreshold;
    std::vector<Employee> promotionEligible;
    std::vector<Employee> bonusEligible;
};

// PART D — OWNER: MEMBER 2
AnalyticsReport analyzeVector(const std::vector<Employee>& employees, double threshold);
void printReport(const AnalyticsReport& report, std::ostream& out);

// PART F — OWNER: MEMBER 3
AnalyticsReport analyzeList(const EmployeeList& employees, double threshold);
AnalyticsReport analyzeSet(const EmployeeSet& employees, double threshold);
