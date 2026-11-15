// PART F — OWNER: MEMBER 3
#include "EmployeeContainers.h"
#include <stdexcept>

bool EmployeeIdLess::operator()(const Employee& a, const Employee& b) const {
    // TODO MEMBER 3: Compare IDs, not names or salaries.
    (void)a;
    (void)b;
    throw std::logic_error("TODO MEMBER 3: EmployeeIdLess(Employee, Employee)");
}

bool EmployeeIdLess::operator()(const Employee& a, int id) const {
    // TODO MEMBER 3: Support efficient heterogeneous set.find(id).
    (void)a;
    (void)id;
    throw std::logic_error("TODO MEMBER 3: EmployeeIdLess(Employee, int)");
}

bool EmployeeIdLess::operator()(int id, const Employee& b) const {
    // TODO MEMBER 3: Support efficient heterogeneous set.find(id).
    (void)id;
    (void)b;
    throw std::logic_error("TODO MEMBER 3: EmployeeIdLess(int, Employee)");
}

EmployeeList makeEmployeeList(const std::vector<Employee>& employees) {
    // TODO MEMBER 3: Copy records into std::list<Employee>.
    (void)employees;
    throw std::logic_error("TODO MEMBER 3: makeEmployeeList");
}

EmployeeSet makeEmployeeSet(const std::vector<Employee>& employees) {
    // TODO MEMBER 3: Insert records into std::set<Employee, EmployeeIdLess>.
    // Verify unique employee IDs; duplicates are otherwise discarded.
    (void)employees;
    throw std::logic_error("TODO MEMBER 3: makeEmployeeSet");
}
