// PART B/C — OWNER: MEMBER 2
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace EmployeeIO {
Employee parseRecord(const std::string& line) {
    // TODO MEMBER 2: Split by '|', confirm 10 fields, convert numeric values,
    // validate is_full_time (0 or 1), and construct Employee.
     stringstream ss(line);

    vector<string> fields;
    string field;

    // Separate each field using | as the delimiter
    while (getline(ss, field, '|')) {
        fields.push_back(field);
    }

    // Each employee record must contain exactly 10 fields
    if (fields.size() != 10) {
        throw runtime_error(
            "Employee record must contain exactly 10 fields."
        );
    }

    // is_full_time must contain either 0 or 1
    if (fields[9] != "0" && fields[9] != "1") {
        throw runtime_error(
            "is_full_time must be either 0 or 1."
        );
    }

    try {
        Employee employee(
            stoi(fields[0]),
            fields[1],
            fields[2],
            fields[3],
            fields[4],
            stoi(fields[5]),
            stoi(fields[6]),
            stod(fields[7]),
            stod(fields[8]),
            stoi(fields[9])
        );

        return employee;
    }
    catch (const invalid_argument&) {
        throw runtime_error(
            "Employee record contains an invalid numeric value."
        );
    }
    catch (const out_of_range&) {
        throw runtime_error(
            "Employee record contains a numeric value that is out of range."
        );
    }
    /*(void)line;
    throw std::logic_error("TODO MEMBER 2: EmployeeIO::parseRecord");*/
}

std::vector<Employee> loadVector(const std::string& path) {
    // TODO MEMBER 2: Open path; parse each nonempty line using parseRecord;
    // include file name and line number in malformed-record exceptions.
    // Must return the assignment's required vector<Employee>.
    vector<Employee> emp;

    ifstream file(path);

    // Make sure the file opened successfully
    if (!file.is_open()) {
        throw runtime_error(
            "Could not open file: " + path
        );
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line)) {

        lineNumber++;

        // Ignore blank lines
        if (line.empty()) {
            continue;
        }

        try {
            Employee employee = parseRecord(line);

            emp.push_back(employee);
        }
        catch (const exception& e) {
            throw runtime_error(
                "Error in " + path +
                " at line " + to_string(lineNumber) +
                ": " + e.what()
            );
        }
    }

    file.close();

    return emp;
}
} // namespace EmployeeIO
