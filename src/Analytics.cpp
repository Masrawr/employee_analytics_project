// PART D — OWNER: MEMBER 2
#include <vector>
#include <map>
#include "Analytics.h"
#include "AnalyticsDetail.h"
#include <iomanip>
#include <ostream>

using namespace std;

int numOfEmployees(vector<Employee>& emp)
{
	return static_cast<int>(emp.size());
}

double AverageSalary(vector<Employee>& emp)
{
	if (emp.empty()) return 0.0;

	double total = 0.0; // initialize total as 0

	for (auto& e : emp) {
		total += e.getSalary(); // add each salary to total
	}

	return total / emp.size(); // divide total by vector size to get average
}

string HighestPaidEmp(vector<Employee>& emp)
{
	if (emp.empty()) return "";

	double max = emp[0].getSalary(); // Initialize maximum salary as the first salary
	string empMax = emp[0].fullName(); // Initialize the highest paid employee as the first employee
	// This helps keep track of the employee with the current maximum salary
	for (auto& e : emp) {
		if (e.getSalary() > max)
		{
			max = e.getSalary();
			empMax = e.fullName();
		}
	}

	return empMax;

}

string LowestPaidEmp(vector<Employee>& emp)
{
	if (emp.empty()) return "";

	double min = emp[0].getSalary(); // Initialize minimum salary as the first salary
	string empMin = emp[0].fullName(); // Initialize the lowest paid employee as the first employee
	// This helps keep track of the employee with the current minimum salary
	for (auto& e : emp) {
		if (e.getSalary() < min)
		{
			min = e.getSalary();
			empMin = e.fullName();
		}
	}

	return empMin;
}

double AveragePerformance(vector<Employee>& emp)
{
	if (emp.empty()) return 0.0;

	double total = 0.0; // initialize total as 0

	for (auto& e : emp) {
		total += e.getPerformanceScore(); // add each performance score to the total
	}

	return total / emp.size(); // divide the total by the number of employees to get average
}

map<string, int> departmentCount(vector<Employee>& emp)
{
	map<string, int> depCounts;

	for (auto& e : emp) {
		if (depCounts.find(e.getDepartment()) == depCounts.end())
			depCounts[e.getDepartment()] = 1; // if we encounter the department but it is not already in the map, we initialize the key to 1
		else
			depCounts[e.getDepartment()]++;  // if it is found then we increment the key by one
	}

	return depCounts;
}

string highestAvg(vector<Employee>& emp)
{
	map<string, int> depCounts;

	for (auto& e : emp) {
		if (depCounts.find(e.getDepartment()) == depCounts.end())
			depCounts[e.getDepartment()] = 1; // if we encounter the department but it is not already in the map, we initialize the key to 1
		else
			depCounts[e.getDepartment()]++;  // if it is found then we increment the key by one
	}

	map<string, double> depTotal;

	for (auto& e : emp) {
		if (depTotal.find(e.getDepartment()) == depTotal.end())
			depTotal[e.getDepartment()] = e.getSalary(); // initialize with the first salary if this is the first encounter
		else
			depTotal[e.getDepartment()] += e.getSalary(); // add salary to total otherwise
	}

	double maxSal = 0.0; // initialize as 0
	string maxDep = "";  // initialize as empty

	for (auto& department : depTotal) {
		if (maxDep.empty() || (department.second / depCounts[department.first]) > maxSal) {
			maxSal = department.second / depCounts[department.first];
			maxDep = department.first;
		}
		// department.first  -> department name
		// department.second -> total salary
	}

	return maxDep;
}

int countFullTime(vector<Employee>& emp)
{
	int count = 0;

	for (auto& e : emp) {
		if (e.isFullTime())
			count++;
	}

	return count;
}

int countPartTime(vector<Employee>& emp)
{
	int count = 0;

	for (auto& e : emp) {
		if (!e.isFullTime())
			count++;
	}

	return count;
}

int abovePerformanceThreshold(vector<Employee>& emp, double threshold)
{
	int count = 0;

	for (auto& e : emp) {
		if (e.getPerformanceScore() > threshold)
			count++;
	}

	return count;
}

int eligibleForPromotionOrBonus(vector<Employee>& emp)
{
	int count = 0;

	for (auto& e : emp) {
		if (e.isEligibleForPromotion() || e.annualBonusEstimate() > 0)
			count++;
	}

	return count;
}


AnalyticsReport analyzeVector(const std::vector<Employee>& employees, double threshold) {
    return AnalyticsDetail::analyze(employees, threshold);
}

void printReport(const AnalyticsReport& report, std::ostream& out) {
    out << std::fixed << std::setprecision(2);
    out << "Total employees: " << report.totalEmployees << '\n'
        << "Average salary: " << report.averageSalary << '\n';
    const auto paidEmployee = [&](const char* label, const std::optional<Employee>& employee) {
        out << label << ": ";
        if (employee) {
            out << employee->fullName() << " (ID " << employee->getEmployeeId()
                << "), salary " << employee->getSalary();
        } else {
            out << "N/A";
        }
        out << '\n';
    };
    paidEmployee("Highest-paid employee", report.highestPaid);
    paidEmployee("Lowest-paid employee", report.lowestPaid);
    out << "Average performance score: " << report.averagePerformanceScore << '\n'
        << "Departments (count, average salary):\n";
    for (const auto& department : report.departments) {
        out << "  " << department.name << ": " << department.employeeCount
            << ", " << department.averageSalary << '\n';
    }
    out << "Department with highest average salary: "
        << (report.departments.empty() ? "N/A" : report.highestAverageSalaryDepartment) << '\n'
        << "Full-time employees: " << report.fullTimeCount << '\n'
        << "Part-time employees: " << report.partTimeCount << '\n'
        << "Employees above performance threshold " << report.threshold
        << " (" << report.aboveThreshold.size() << "):\n";
    for (const auto& employee : report.aboveThreshold) {
        out << "  " << employee.getEmployeeId() << " | " << employee.fullName()
            << " | score " << employee.getPerformanceScore() << '\n';
    }
    out << "Promotion eligible (" << report.promotionEligible.size() << "):\n";
    for (const auto& employee : report.promotionEligible) {
        out << "  " << employee.getEmployeeId() << " | " << employee.fullName() << '\n';
    }
    out << "Bonus eligible (" << report.bonusEligible.size() << "):\n";
    for (const auto& employee : report.bonusEligible) {
        out << "  " << employee.getEmployeeId() << " | " << employee.fullName()
            << " | bonus " << employee.annualBonusEstimate() << '\n';
    }
}
