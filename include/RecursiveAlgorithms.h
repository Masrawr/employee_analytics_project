#pragma once

#include "EmployeeContainers.h"
#include <string>
#include <vector>

// PART G — OWNER: MEMBER 3
// Valid operations here: aggregate, filter_department,
// filter_performance, search_id. Each function must use actual recursion.
// Return a numeric checksum so the benchmark can ensure work is not optimized away:
//   aggregate -> total salary
//   filter_department / filter_performance -> number matching
//   search_id -> 1.0 if found, else 0.0
// No recursive sort/file loading is required if not appropriate.
double recursiveVectorOperation(const std::vector<Employee>& employees,
                                const std::string& operation,
                                const std::string& department,
                                double threshold, int searchId);

double recursiveListOperation(const EmployeeList& employees,
                              const std::string& operation,
                              const std::string& department,
                              double threshold, int searchId);

double recursiveSetOperation(const EmployeeSet& employees,
                             const std::string& operation,
                             const std::string& department,
                             double threshold, int searchId);
