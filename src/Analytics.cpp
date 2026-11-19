// PART D — OWNER: MEMBER 2
#pragma once

#include <vector>
#include <map>
#include <string>

#include "Employee.h"

int numOfEmployees(std::vector<Employee>& emp);
double AverageSalary(std::vector<Employee>& emp);
std::string HighestPaidEmp(std::vector<Employee>& emp);
std::string LowestPaidEmp(std::vector<Employee>& emp);
double AveragePerformance(std::vector<Employee>& emp);
std::map<std::string, int> departmentCount(std::vector<Employee>& emp);
std::string highestAvg(std::vector<Employee>& emp);
int countFullTime(std::vector<Employee>& emp);
int countPartTime(std::vector<Employee>& emp);
int abovePerformanceThreshold(
    std::vector<Employee>& emp,
    double threshold
);
int eligibleForPromotionOrBonus(std::vector<Employee>& emp);
/*#include "Analytics.h"
#include <stdexcept>

AnalyticsReport analyzeVector(const std::vector<Employee>& employees,
                              double threshold) {
    // TODO MEMBER 2 (a): Count employees.
    // TODO MEMBER 2 (b): Average salary (guard empty input).
    // TODO MEMBER 2 (c-d): Highest/lowest paid employee.
    // TODO MEMBER 2 (e): Average performance score.
    // TODO MEMBER 2 (f): Department-wise counts.
    // TODO MEMBER 2 (g): Department with highest average salary.
    // TODO MEMBER 2 (h): Full-time versus part-time counts.
    // TODO MEMBER 2 (i): Employees with performanceScore > threshold.
    // TODO MEMBER 2 (j): Bonus/promotion groups using Employee methods.
    (void)employees;
    (void)threshold;
    throw std::logic_error("TODO MEMBER 2: analyzeVector");
}

void printReport(const AnalyticsReport& report, std::ostream& out) {
    // TODO MEMBER 2: Print each part (a) through (j) in a readable report;
    // show full names and bonus amounts where appropriate.
    (void)report;
    (void)out;
    throw std::logic_error("TODO MEMBER 2: printReport");
}*/
