#include <sstream>
#include <iomanip>
#include <limits>
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

    ss << setprecision(numeric_limits<double>::max_digits10) << employeeId_ << "|"
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
