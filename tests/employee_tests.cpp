#include "Analytics.h"
#include "EmployeeIO.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

void require(bool condition) {
    if (!condition) throw std::runtime_error("Employee unit check failed");
}

int main() {
    Employee employee;
    require(employee.getEmployeeId() == 0 && employee.getSalary() == 0);
    employee.setEmployeeId(42);
    employee.setFirstName("Test");
    employee.setLastName("Person");
    employee.setDepartment("Engineering");
    employee.setJobTitle("Developer");
    employee.setAge(30);
    employee.setYearOfService(5);
    employee.setSalary(12345.678912345);
    employee.setPerformanceScore(4.123456789);
    employee.setIsFullTime(true);
    const auto copy = EmployeeIO::parseRecord(employee.serialize());
    require(copy.getEmployeeId() == 42 && copy.fullName() == "Test Person");
    require(copy.getDepartment() == "Engineering" && copy.getJobTitle() == "Developer");
    require(copy.getAge() == 30 && copy.getYearOfService() == 5);
    require(copy.getSalary() == employee.getSalary());
    require(copy.getPerformanceScore() == employee.getPerformanceScore() && copy.isFullTime());
    require(copy.isHighPerformer() && copy.isEligibleForPromotion());
    require(std::abs(copy.annualBonusEstimate() - copy.getSalary() * .27) < 1e-9);
    employee.setPerformanceScore(4);
    employee.setYearOfService(3);
    employee.setIsFullTime(false);
    require(employee.isHighPerformer() && employee.isEligibleForPromotion());
    employee.setPerformanceScore(3.99);
    employee.setYearOfService(2);
    require(!employee.isHighPerformer() && !employee.isEligibleForPromotion());
    require(employee.annualBonusEstimate() == 0);
    std::vector<Employee> zeroSalary{Employee(1,"A","B","Zero","Dev",20,0,0,0,false)};
    require(highestAvg(zeroSalary) == "Zero");
    require(analyzeVector(zeroSalary, 4).highestAverageSalaryDepartment == "Zero");
    std::cout << "PASS: Employee accessors, serialization precision, rule boundaries, zero-salary department\n";
}
