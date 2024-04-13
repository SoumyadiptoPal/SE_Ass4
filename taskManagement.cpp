#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Structure to hold task details
struct Task {
    int id;
    string description;
    string status;
};

// Function to read task data from CSV file
vector<Task> readTasksFromCSV(const string& filename) {
    vector<Task> tasks;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return tasks;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, description, status;
        getline(ss, id, ',');
        getline(ss, description, ',');
        getline(ss, status, ',');
        Task task = {stoi(id), description, status};
        tasks.push_back(task);
    }

    file.close();
    return tasks;
}

// Function to write task data to CSV file
void writeTasksToCSV(const string& filename, const vector<Task>& tasks) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto& task : tasks) {
        file << task.id << "," << task.description << "," << task.status << endl;
    }

    file.close();
}

// Function to add a new task
void addTask(vector<Task>& tasks, const string& description) {
    int nextID = tasks.size()+1;
    Task task = {nextID, description, "Incomplete"};
    tasks.push_back(task);
    cout << "Task with ID " << nextID << " added successfully." << endl;
}

// Function to edit an existing task
void editTask(vector<Task>& tasks, int id, const string& newDescription) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.description = newDescription;
            cout << "Task with ID " << id << " edited successfully." << endl;
            return;
        }
    }
    cout << "Task with ID " << id << " not found." << endl;
}

// Function to mark a task as completed
void completeTask(vector<Task>& tasks, int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.status = "Complete";
            cout << "Congrats!! Task with ID " << id << " completed successfully." << endl;
            return;
        }
    }
    cout << "Task with ID " << id << " not found." << endl;
}

// Function to display task details
void displayTasks(const vector<Task>& tasks) {
    cout << setw(5) << left << "ID" << setw(40) << "Description" << setw(15) << "Status" << endl;
    cout << "-----------------------------------------------" << endl;
    for (const auto& task : tasks) {
        cout << setw(5) << left << task.id << setw(40) << task.description << setw(15) << task.status << endl;
    }
    cout << "-----------------------------------------------" << endl;
}

int main() {
    const string filename = "tasks.csv";
    vector<Task> tasks = readTasksFromCSV(filename);

    int choice;
    do {
        cout << "======================================" << endl;
        cout << "     Task Management CLI Tool" << endl;
        cout << "======================================" << endl;
        cout << "Options:" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Edit Task" << endl;
        cout << "3. Complete Task" << endl;
        cout << "4. View Tasks" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                {
                    string description;
                    cout << "Enter task description: ";
                    cin.ignore(); // Ignore newline character
                    getline(cin, description);
                    addTask(tasks, description);
                    writeTasksToCSV(filename, tasks);
                }
                break;
            case 2:
                {
                    int id;
                    string newDescription;
                    cout << "Enter task ID to edit: ";
                    cin >> id;
                    cout << "Enter new task description: ";
                    cin.ignore(); // Ignore newline character
                    getline(cin, newDescription);
                    editTask(tasks, id, newDescription);
                    writeTasksToCSV(filename, tasks);
                }
                break;
            case 3:
                {
                    int id;
                    cout << "Enter task ID to mark as complete: ";
                    cin >> id;
                    completeTask(tasks, id);
                    writeTasksToCSV(filename, tasks);
                }
                break;
            case 4:
                displayTasks(tasks);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 5);

    return 0;
}
