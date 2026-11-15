#pragma once

#include "Employee.h"
#include <string>
#include <vector>

// PART B and C — OWNER: MEMBER 2
namespace EmployeeIO {
    // Parse EXACTLY 10 pipe-separated fields into an Employee.
    // Throw a useful exception for malformed lines.
    Employee parseRecord(const std::string& line);

    // Read file, ignore blank lines, report useful file/line errors,
    // and return the required vector<Employee>.
    std::vector<Employee> loadVector(const std::string& path);
}
