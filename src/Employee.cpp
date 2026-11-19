/*
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
*/

#include <sstream>
#include "Employee.h"

using namespace std;


// NEW - default constructor required by new Employee.h
Employee::Employee()
{
}


// EXISTING - constructor, updated names only
Employee::Employee(int employeeId, string firstName, string lastName,
    string department, string jobTitle, int age,
    int yearOfService, double salary, double performanceScore,
    bool isFullTime)
    :
    employeeId_(employeeId),
    firstName_(firstName),
    lastName_(lastName),
    department_(department),
    jobTitle_(jobTitle),
    age_(age),
    yearOfService_(yearOfService),
    salary_(salary),
    performanceScore_(performanceScore),
    isFullTime_(isFullTime)
{
}


// NEW GETTERS

int Employee::getEmployeeId() const
{
    return employeeId_;
}

const string& Employee::getFirstName() const
{
    return firstName_;
}

const string& Employee::getLastName() const
{
    return lastName_;
}

const string& Employee::getDepartment() const
{
    return department_;
}

const string& Employee::getJobTitle() const
{
    return jobTitle_;
}

int Employee::getAge() const
{
    return age_;
}

int Employee::getYearOfService() const
{
    return yearOfService_;
}


// EXISTING getSalary - name unchanged, required const/member rename added
double Employee::getSalary() const
{
    return salary_;
}


// EXISTING getPerformance renamed to getPerformanceScore
double Employee::getPerformanceScore() const
{
    return performanceScore_;
}


// EXISTING getIsFullTime renamed to isFullTime
bool Employee::isFullTime() const
{
    return isFullTime_;
}


// NEW SETTERS

void Employee::setEmployeeId(int value)
{
    employeeId_ = value;
}

void Employee::setFirstName(const string& value)
{
    firstName_ = value;
}

void Employee::setLastName(const string& value)
{
    lastName_ = value;
}

void Employee::setDepartment(const string& value)
{
    department_ = value;
}

void Employee::setJobTitle(const string& value)
{
    jobTitle_ = value;
}

void Employee::setAge(int value)
{
    age_ = value;
}

void Employee::setYearOfService(int value)
{
    yearOfService_ = value;
}


// EXISTING setSalary - body preserved except member rename
void Employee::setSalary(double value)
{
    salary_ = value;
}


// EXISTING setPerformance renamed to setPerformanceScore
void Employee::setPerformanceScore(double value)
{
    performanceScore_ = value;
}


// NEW
void Employee::setIsFullTime(bool value)
{
    isFullTime_ = value;
}


// EXISTING getName renamed to fullName
string Employee::fullName() const
{
    return firstName_ + " " + lastName_;
}


// NEW - replaces displayInfo because new header requires serialization
string Employee::serialize() const
{
    stringstream ss;

    ss << employeeId_ << "|"
       << firstName_ << "|"
       << lastName_ << "|"
       << department_ << "|"
       << jobTitle_ << "|"
       << age_ << "|"
       << yearOfService_ << "|"
       << salary_ << "|"
       << performanceScore_ << "|"
       << isFullTime_;

    return ss.str();
}


// EXISTING BODY PRESERVED
bool Employee::isHighPerformer() const
{
    if (performanceScore_ >= 4.0) return true;
    return false;
}


// EXISTING BODY PRESERVED
double Employee::annualBonusEstimate() const
{
    // Initialize each bonus as 0 
    double yearBonus = 0;
    double performanceBonus = 0;
    double fullTimeBonus = 0;

    if (yearOfService_ >= 5) yearBonus = salary_ * 0.15;  // 5 or more years of service -> 15% salary

    if (performanceScore_ >= 4.0) performanceBonus = salary_ * 0.10; // Performance score greater than 4.0 -> 10% salary

    if (isFullTime_) fullTimeBonus = salary_ * 0.02; // Full time bonus is 2%

    return yearBonus + performanceBonus + fullTimeBonus; // Return bonus sum
}


// EXISTING BODY PRESERVED
bool Employee::isEligibleForPromotion() const
{
    if (yearOfService_ >= 3 && performanceScore_ >= 4.0) return true;
    return false;
}
