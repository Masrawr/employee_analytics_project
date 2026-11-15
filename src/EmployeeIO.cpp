// PART B/C — OWNER: MEMBER 2
#include "EmployeeIO.h"
#include <stdexcept>

namespace EmployeeIO {
Employee parseRecord(const std::string& line) {
    // TODO MEMBER 2: Split by '|', confirm 10 fields, convert numeric values,
    // validate is_full_time (0 or 1), and construct Employee.
    (void)line;
    throw std::logic_error("TODO MEMBER 2: EmployeeIO::parseRecord");
}

std::vector<Employee> loadVector(const std::string& path) {
    // TODO MEMBER 2: Open path; parse each nonempty line using parseRecord;
    // include file name and line number in malformed-record exceptions.
    // Must return the assignment's required vector<Employee>.
    (void)path;
    throw std::logic_error("TODO MEMBER 2: EmployeeIO::loadVector");
}
} // namespace EmployeeIO
