// PART D — OWNER: MEMBER 2
#include <vector>
#include <map>
#include "Employee.h"

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
	string empMax = emp[0].getName(); // Initialize the highest paid employee as the first employee
	// This helps keep track of the employee with the current maximum salary
	for (auto& e : emp) {
		if (e.getSalary() > max)
		{
			max = e.getSalary();
			empMax = e.getName();
		}
	}

	return empMax;

}

string LowestPaidEmp(vector<Employee>& emp)
{
	if (emp.empty()) return "";

	double min = emp[0].getSalary(); // Initialize minimum salary as the first salary
	string empMin = emp[0].getName(); // Initialize the lowest paid employee as the first employee
	// This helps keep track of the employee with the current minimum salary
	for (auto& e : emp) {
		if (e.getSalary() < min)
		{
			min = e.getSalary();
			empMin = e.getName();
		}
	}

	return empMin;
}

double AveragePerformance(vector<Employee>& emp)
{
	if (emp.empty()) return 0.0;

	double total = 0.0; // initialize total as 0

	for (auto& e : emp) {
		total += e.getPerformance(); // add each performance score to the total
	}

	return total / emp.size(); // divide the total by the number of employees to get average
}

map<string, int> departmentCount(vector<Employee>& emp)
{
	map<string, int> depCounts;

	for (auto& e : emp) {
		if (depCounts.find(e.getDep()) == depCounts.end())
			depCounts[e.getDep()] = 1; // if we encounter the department but it is not already in the map, we initialize the key to 1
		else
			depCounts[e.getDep()]++;  // if it is found then we increment the key by one
	}

	return depCounts;
}

string highestAvg(vector<Employee>& emp)
{
	map<string, int> depCounts;

	for (auto& e : emp) {
		if (depCounts.find(e.getDep()) == depCounts.end())
			depCounts[e.getDep()] = 1; // if we encounter the department but it is not already in the map, we initialize the key to 1
		else
			depCounts[e.getDep()]++;  // if it is found then we increment the key by one
	}

	map<string, double> depTotal;

	for (auto& e : emp) {
		if (depTotal.find(e.getDep()) == depTotal.end())
			depTotal[e.getDep()] = e.getSalary(); // initialize with the first salary if this is the first encounter 
		else
			depTotal[e.getDep()] += e.getSalary(); // add salary to total otherwise
	}

	double maxSal = 0.0; // initialize as 0
	string maxDep = "";  // initialize as empty

	for (auto& department : depTotal) {
		if ((department.second / depCounts[department.first]) > maxSal) {
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
		if (e.getIsFullTime())
			count++;
	}

	return count;
}

int countPartTime(vector<Employee>& emp)
{
	int count = 0;

	for (auto& e : emp) {
		if (!e.getIsFullTime())
			count++;
	}

	return count;
}

int abovePerformanceThreshold(vector<Employee>& emp, double threshold)
{
	int count = 0;

	for (auto& e : emp) {
		if (e.getPerformance() > threshold)
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

/*#include "Analytics.h"
#include <stdexcept>

AnalyticsReport analyzeVector(const std::vector<Employee>& employees,
                              double threshold) {
    // TODO MEMBER 2 (a): Count employees.
    // TODO MEMBER 2 (b): Average salary (guard empty input).
    // TODO MEMBER 2 (c-d): Highest/lowest paid employee.
    // TODO MEMBER 2 (e): Average performance score.
    // TODO MEMBER 2 (f): Department-wise counts.
    // TODO MEMBER 2 (g): Department with highest average salary.
    // TODO MEMBER 2 (h): Full-time versus part-time counts.
    // TODO MEMBER 2 (i): Employees with performanceScore > threshold.
    // TODO MEMBER 2 (j): Bonus/promotion groups using Employee methods.
    (void)employees;
    (void)threshold;
    throw std::logic_error("TODO MEMBER 2: analyzeVector");
}

void printReport(const AnalyticsReport& report, std::ostream& out) {
    // TODO MEMBER 2: Print each part (a) through (j) in a readable report;
    // show full names and bonus amounts where appropriate.
    (void)report;
    (void)out;
    throw std::logic_error("TODO MEMBER 2: printReport");
}*/
