// PART F — OWNER: MEMBER 3
#include "Analytics.h"
#include <stdexcept>

AnalyticsReport analyzeList(const EmployeeList& employees, double threshold) {
    // TODO MEMBER 3: Reimplement ALL analytics (a)-(j) while traversing
    // list<Employee> directly. Do not convert it back into vector<Employee>.
    // Return AnalyticsReport in the same format as Member 2's vector report.
    (void)employees;
    (void)threshold;
    throw std::logic_error("TODO MEMBER 3: analyzeList");
}

AnalyticsReport analyzeSet(const EmployeeSet& employees, double threshold) {
    // TODO MEMBER 3: Reimplement ALL analytics (a)-(j) while traversing
    // set<Employee> directly. Use unique employee IDs as the set ordering key.
    // Return AnalyticsReport in the same format as Member 2's vector report.
    (void)employees;
    (void)threshold;
    throw std::logic_error("TODO MEMBER 3: analyzeSet");
}
