// PART B/C — record parsing and vector loading.
#include "EmployeeIO.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

namespace {
int integer(const std::string& text) {
    std::size_t used = 0;
    const int value = std::stoi(text, &used);
    if (used != text.size()) throw std::invalid_argument("Invalid integer: " + text);
    return value;
}

double number(const std::string& text) {
    std::size_t used = 0;
    const double value = std::stod(text, &used);
    if (used != text.size() || !std::isfinite(value)) {
        throw std::invalid_argument("Invalid finite number: " + text);
    }
    return value;
}
} // namespace

namespace EmployeeIO {
Employee parseRecord(const std::string& line) {
    std::string record = line;
    if (!record.empty() && record.back() == '\r') record.pop_back();
    if (std::count(record.begin(), record.end(), '|') != 9) {
        throw std::invalid_argument("Employee record must contain exactly 10 fields");
    }
    std::istringstream stream(record);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(stream, field, '|')) fields.push_back(field);
    if (fields.size() != 10) {
        throw std::invalid_argument("Employee record must contain exactly 10 nonempty fields");
    }
    for (const auto& value : fields) {
        if (value.find_first_not_of(" \t\r\n") == std::string::npos) {
            throw std::invalid_argument("Employee fields cannot be empty");
        }
    }
    if (fields[9] != "0" && fields[9] != "1") {
        throw std::invalid_argument("is_full_time must be either 0 or 1");
    }
    const int id = integer(fields[0]);
    const int age = integer(fields[5]);
    const int years = integer(fields[6]);
    const double salary = number(fields[7]);
    const double score = number(fields[8]);
    if (id < 0 || age < 0 || years < 0 || salary < 0 || score < 0) {
        throw std::invalid_argument("Numeric employee fields cannot be negative");
    }
    return Employee(id, fields[1], fields[2], fields[3], fields[4],
                    age, years, salary, score, fields[9] == "1");
}

std::vector<Employee> loadVector(const std::string& path) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Could not open file: " + path);
    std::vector<Employee> employees;
    std::unordered_set<int> ids;
    std::string line;
    std::size_t lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        try {
            Employee employee = parseRecord(line);
            if (!ids.insert(employee.getEmployeeId()).second) {
                throw std::invalid_argument("Duplicate employee ID: " +
                                            std::to_string(employee.getEmployeeId()));
            }
            employees.push_back(employee);
        } catch (const std::exception& error) {
            throw std::runtime_error(path + ": line " + std::to_string(lineNumber) +
                                     ": " + error.what());
        }
    }
    if (file.bad()) throw std::runtime_error("Error reading file: " + path);
    return employees;
}
} // namespace EmployeeIO
