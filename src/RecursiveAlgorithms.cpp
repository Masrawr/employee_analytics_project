// PART G — OWNER: MEMBER 3
#include "RecursiveAlgorithms.h"
#include <stdexcept>

double recursiveVectorOperation(const std::vector<Employee>& employees,
                                const std::string& operation,
                                const std::string& department,
                                double threshold, int searchId) {
    // TODO MEMBER 3: Write recursive helper(s) with an index and a base case.
    // Support aggregate, filter_department, filter_performance, search_id.
    // Do not loop or create a copy inside the recursive calls.
    (void)employees; (void)operation; (void)department;
    (void)threshold; (void)searchId;
    throw std::logic_error("TODO MEMBER 3: recursiveVectorOperation");
}

double recursiveListOperation(const EmployeeList& employees,
                              const std::string& operation,
                              const std::string& department,
                              double threshold, int searchId) {
    // TODO MEMBER 3: Recursively advance a const_iterator with a base case;
    // do not index the list (std::list has no random access).
    (void)employees; (void)operation; (void)department;
    (void)threshold; (void)searchId;
    throw std::logic_error("TODO MEMBER 3: recursiveListOperation");
}

double recursiveSetOperation(const EmployeeSet& employees,
                             const std::string& operation,
                             const std::string& department,
                             double threshold, int searchId) {
    // TODO MEMBER 3: Recursively traverse set using a const_iterator.
    // Document the difference between traversal and set.find(id) lookup.
    (void)employees; (void)operation; (void)department;
    (void)threshold; (void)searchId;
    throw std::logic_error("TODO MEMBER 3: recursiveSetOperation");
}
