#pragma once

#include <string>

// PART A — OWNER: MEMBER 2
// Every method is declared here; implement its TODO in src/Employee.cpp.
class Employee {
private:
    int employeeId_{};
    std::string firstName_;
    std::string lastName_;
    std::string department_;
    std::string jobTitle_;
    int age_{};
    int yearOfService_{};
    double salary_{};
    double performanceScore_{};
    bool isFullTime_{};

public:
    Employee();
    Employee(int employeeId, std::string firstName, std::string lastName,
             std::string department, std::string jobTitle, int age,
             int yearOfService, double salary, double performanceScore,
             bool isFullTime);

    int getEmployeeId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getDepartment() const;
    const std::string& getJobTitle() const;
    int getAge() const;
    int getYearOfService() const;
    double getSalary() const;
    double getPerformanceScore() const;
    bool isFullTime() const;

    void setEmployeeId(int value);
    void setFirstName(const std::string& value);
    void setLastName(const std::string& value);
    void setDepartment(const std::string& value);
    void setJobTitle(const std::string& value);
    void setAge(int value);
    void setYearOfService(int value);
    void setSalary(double value);
    void setPerformanceScore(double value);
    void setIsFullTime(bool value);

    std::string fullName() const;
    std::string serialize() const; // pipe-separated output
    bool isHighPerformer() const;
    double annualBonusEstimate() const;
    bool isEligibleForPromotion() const;
};
