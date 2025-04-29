#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

// Struct for storing employee data
struct Employee {
    int id;
    string name;
    string department;
};

// Struct for index table entries (for searching employee positions)
struct IndexEntry {
    int id;
    int position;
};

// Function to search for an employee by ID
Employee searchEmployee(int searchId, const vector<IndexEntry>& indexTable) {
    int startPos = -1;  // Start position for search, -1 means not found

    // Find the start position from the index table
    for (const auto& entry : indexTable) {
        if (searchId >= entry.id) {
            startPos = entry.position;
        } else {
            break;
        }
    }

    // If a start position is found, search from there
    if (startPos != -1) {
        ifstream file("employees.txt");
        file.seekg(startPos);  // Jump to start position

        Employee emp;
        while (file >> emp.id >> emp.name >> emp.department) {
            if (emp.id == searchId) {
                return emp;  // Found the employee, return it
            }
        }
    }

    // If not found, throw an error
    throw runtime_error("Employee not found.");
}

int main() {
    // Example index table: {ID, position in file}
    vector<IndexEntry> indexTable = {{100, 0}, {200, 10}, {300, 20}};

    try {
        // Searching for employee with ID 200
        Employee result = searchEmployee(200, indexTable);
        cout << "Employee Found: " << result.id << ", " << result.name << ", " << result.department << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;  // If not found, show error
    }

    return 0;
}

