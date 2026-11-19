// PART F — OWNER: MEMBER 3
#include "EmployeeContainers.h"

#include <stdexcept>

bool EmployeeIdLess::operator()(const Employee& a, const Employee& b) const {
    return a.getEmployeeId() < b.getEmployeeId();
}

bool EmployeeIdLess::operator()(const Employee& a, int id) const {
    return a.getEmployeeId() < id;
}

bool EmployeeIdLess::operator()(int id, const Employee& b) const {
    return id < b.getEmployeeId();
}

EmployeeList makeEmployeeList(const std::vector<Employee>& employees) {
    return EmployeeList(employees.begin(), employees.end());
}

EmployeeSet makeEmployeeSet(const std::vector<Employee>& employees) {
    EmployeeSet result;
    for (const Employee& employee : employees) {
        if (!result.insert(employee).second) {
            throw std::invalid_argument("Duplicate employee ID: " +
                                        std::to_string(employee.getEmployeeId()));
        }
    }
    return result;
}
