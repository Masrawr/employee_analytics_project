#pragma once

#include "Employee.h"
#include <list>
#include <set>
#include <vector>

// PART F — OWNER: MEMBER 3
// A set must have a stable ordering. Use employee ID as the unique key.
struct EmployeeIdLess {
    using is_transparent = void; // Allows set.find(int) once implemented.
    bool operator()(const Employee& a, const Employee& b) const;
    bool operator()(const Employee& a, int id) const;
    bool operator()(int id, const Employee& b) const;
};

using EmployeeList = std::list<Employee>;
using EmployeeSet = std::set<Employee, EmployeeIdLess>;

EmployeeList makeEmployeeList(const std::vector<Employee>& employees);
EmployeeSet makeEmployeeSet(const std::vector<Employee>& employees);
