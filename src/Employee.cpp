// PART A — OWNER: MEMBER 2
#include "Employee.h"
#include <stdexcept>
#include <utility>

Employee::Employee() {
    // TODO MEMBER 2: Initialize a reasonable default Employee.
    throw std::logic_error("TODO MEMBER 2: Employee default constructor");
}

Employee::Employee(int employeeId, std::string firstName, std::string lastName,
                   std::string department, std::string jobTitle, int age,
                   int yearOfService, double salary, double performanceScore,
                   bool isFullTime) {
    // TODO MEMBER 2: Initialize all 10 fields (initializer list recommended).
    // Validate ID/age/service years, nonnegative salary, 0–5 performance.
    (void)employeeId; (void)firstName; (void)lastName;
    (void)department; (void)jobTitle; (void)age;
    (void)yearOfService; (void)salary; (void)performanceScore;
    (void)isFullTime;
    throw std::logic_error("TODO MEMBER 2: Employee parameterized constructor");
}

int Employee::getEmployeeId() const {
    // TODO MEMBER 2: Return employeeId_.
    throw std::logic_error("TODO MEMBER 2: Employee::getEmployeeId");
}

const std::string& Employee::getFirstName() const {
    // TODO MEMBER 2: Return firstName_.
    throw std::logic_error("TODO MEMBER 2: Employee::getFirstName");
}

const std::string& Employee::getLastName() const {
    // TODO MEMBER 2: Return lastName_.
    throw std::logic_error("TODO MEMBER 2: Employee::getLastName");
}

const std::string& Employee::getDepartment() const {
    // TODO MEMBER 2: Return department_.
    throw std::logic_error("TODO MEMBER 2: Employee::getDepartment");
}

const std::string& Employee::getJobTitle() const {
    // TODO MEMBER 2: Return jobTitle_.
    throw std::logic_error("TODO MEMBER 2: Employee::getJobTitle");
}

int Employee::getAge() const {
    // TODO MEMBER 2: Return age_.
    throw std::logic_error("TODO MEMBER 2: Employee::getAge");
}

int Employee::getYearOfService() const {
    // TODO MEMBER 2: Return yearOfService_.
    throw std::logic_error("TODO MEMBER 2: Employee::getYearOfService");
}

double Employee::getSalary() const {
    // TODO MEMBER 2: Return salary_.
    throw std::logic_error("TODO MEMBER 2: Employee::getSalary");
}

double Employee::getPerformanceScore() const {
    // TODO MEMBER 2: Return performanceScore_.
    throw std::logic_error("TODO MEMBER 2: Employee::getPerformanceScore");
}

bool Employee::isFullTime() const {
    // TODO MEMBER 2: Return isFullTime_.
    throw std::logic_error("TODO MEMBER 2: Employee::isFullTime");
}

void Employee::setEmployeeId(int value) {
    // TODO MEMBER 2: Validate as appropriate, then assign employeeId_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setEmployeeId");
}

void Employee::setFirstName(const std::string& value) {
    // TODO MEMBER 2: Validate as appropriate, then assign firstName_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setFirstName");
}

void Employee::setLastName(const std::string& value) {
    // TODO MEMBER 2: Validate as appropriate, then assign lastName_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setLastName");
}

void Employee::setDepartment(const std::string& value) {
    // TODO MEMBER 2: Validate as appropriate, then assign department_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setDepartment");
}

void Employee::setJobTitle(const std::string& value) {
    // TODO MEMBER 2: Validate as appropriate, then assign jobTitle_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setJobTitle");
}

void Employee::setAge(int value) {
    // TODO MEMBER 2: Validate as appropriate, then assign age_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setAge");
}

void Employee::setYearOfService(int value) {
    // TODO MEMBER 2: Validate as appropriate, then assign yearOfService_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setYearOfService");
}

void Employee::setSalary(double value) {
    // TODO MEMBER 2: Validate as appropriate, then assign salary_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setSalary");
}

void Employee::setPerformanceScore(double value) {
    // TODO MEMBER 2: Validate as appropriate, then assign performanceScore_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setPerformanceScore");
}

void Employee::setIsFullTime(bool value) {
    // TODO MEMBER 2: Validate as appropriate, then assign isFullTime_.
    (void)value;
    throw std::logic_error("TODO MEMBER 2: Employee::setIsFullTime");
}

std::string Employee::fullName() const {
    // TODO MEMBER 2: Return first name + space + last name.
    throw std::logic_error("TODO MEMBER 2: Employee::fullName");
}

std::string Employee::serialize() const {
    // TODO MEMBER 2: Return all 10 fields joined by pipes with bool as 0/1.
    throw std::logic_error("TODO MEMBER 2: Employee::serialize");
}

bool Employee::isHighPerformer() const {
    // TODO MEMBER 2: Apply the chosen high-performer threshold, consistently.
    throw std::logic_error("TODO MEMBER 2: Employee::isHighPerformer");
}

double Employee::annualBonusEstimate() const {
    // TODO MEMBER 2: Use agreed-on bonus rule; return 0 for ineligible employees.
    throw std::logic_error("TODO MEMBER 2: Employee::annualBonusEstimate");
}

bool Employee::isEligibleForPromotion() const {
    // TODO MEMBER 2: Apply agreed-on promotion rule (document in README).
    throw std::logic_error("TODO MEMBER 2: Employee::isEligibleForPromotion");
}

