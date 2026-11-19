#include "AnalyticsDetail.h"

AnalyticsReport analyzeList(const EmployeeList& employees, double threshold) {
    return AnalyticsDetail::analyze(employees, threshold);
}

AnalyticsReport analyzeSet(const EmployeeSet& employees, double threshold) {
    return AnalyticsDetail::analyze(employees, threshold);
}
