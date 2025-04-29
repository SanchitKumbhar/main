#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Employee {
    int id;
    string name;
    string department;
};

struct IndexEntry {
    int id;      // starting id
    int position; // line number or position in file
};

// Global index
vector<IndexEntry> indexTable;

// Function to build index
void buildIndex() {
    ifstream file("employees.txt");
    Employee emp;
    int pos = 0;

    while (file >> emp.id >> emp.name >> emp.department) {
        // Add every 3rd record to index (example)
        if (pos % 3 == 0) {
            IndexEntry entry;
            entry.id = emp.id;
            entry.position = pos;
            indexTable.push_back(entry);
        }
        pos++;
    }
    file.close();
}

// Function to search using index
void searchEmployeeById(int searchId) {
    ifstream file("employees.txt");
    Employee emp;
    int pos = 0;
    int startPos = 0;

    // Find the nearest lower ID from index
    for (const auto& entry : indexTable) {
        if (searchId >= entry.id) {
            startPos = entry.position;
        } else {
            break;
        }
    }

    // Now move to startPos
    file.clear();
    file.seekg(0); // Go to beginning
    int skipLines = startPos;
    while (skipLines--) {
        file >> emp.id >> emp.name >> emp.department;
    }

    // Now sequential search from here
    bool found = false;
    while (file >> emp.id >> emp.name >> emp.department) {
        if (emp.id == searchId) {
            cout << "Employee Found!\n";
            cout << "ID: " << emp.id
                 << ", Name: " << emp.name
                 << ", Department: " << emp.department << endl;
            found = true;
            break;
        }
        // Stop if ids are bigger
        if (emp.id > searchId) {
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << searchId << " not found.\n";
    }

    file.close();
}

// Function to add new employee
void addEmployee() {
    ofstream file("employees.txt", ios::app);
    Employee emp;

    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter Department: ";
    getline(cin, emp.department);

    file << emp.id << " " << emp.name << " " << emp.department << endl;
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\nIndexed Sequential File System - Employee Management\n";
        cout << "1. Add Employee\n";
        cout << "2. Build Index\n";
        cout << "3. Search Employee by ID\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                buildIndex();
                cout << "Index built successfully!\n";
                break;
            case 3: {
                int id;
                cout << "Enter Employee ID to search: ";
                cin >> id;
                searchEmployeeById(id);
                break;
            }
            case 0:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
