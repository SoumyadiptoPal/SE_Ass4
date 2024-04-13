#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to hold student details
struct Student {
    string name;
    int rollNumber;
    int marksMaths;
    int marksScience;
    int marksEnglish;
    int totalMarks;
};

// Function to read student data from CSV file
vector<Student> readStudentDataFromCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return students;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, rollNumber, marksMaths, marksScience, marksEnglish;
        getline(ss, name, ',');
        getline(ss, rollNumber, ',');
        getline(ss, marksMaths, ',');
        getline(ss, marksScience, ',');
        getline(ss, marksEnglish, ',');
        int totalMarks = stoi(marksMaths) + stoi(marksScience) + stoi(marksEnglish);
        Student student = {name, stoi(rollNumber), stoi(marksMaths), stoi(marksScience), stoi(marksEnglish), totalMarks};
        students.push_back(student);
    }

    file.close();
    return students;
}

// Function to update marks for a specific subject
void updateMarks(vector<Student>& students, int rollNumber, int marks, const string& subject) {
    for (auto& student : students) {
        if (student.rollNumber == rollNumber) {
            if (subject == "Maths") {
                student.marksMaths = marks;
            } else if (subject == "Science") {
                student.marksScience = marks;
            } else if (subject == "English") {
                student.marksEnglish = marks;
            }
            student.totalMarks = student.marksMaths + student.marksScience + student.marksEnglish;
            return;
        }
    }
    cout << "Student with roll number " << rollNumber << " not found." << endl;
}

// Function to sort students by total marks
void sortStudentsByTotalMarks(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });
}

// Function to display student details
void displayStudentDetails(const vector<Student>& students) {
    cout << setw(10) << left << "Roll No." << setw(20) << "Name" << setw(10) << "Maths" << setw(10) << "Science" << setw(10) << "English" << setw(10) << "Total" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (const auto& student : students) {
        cout << setw(10) << left << student.rollNumber << setw(20) << student.name << setw(10) << student.marksMaths << setw(10) << student.marksScience << setw(10) << student.marksEnglish << setw(10) << student.totalMarks << endl;
    }
    cout << "------------------------------------------------------------" << endl;
}

int main() {
    const string filename = "students.csv";
    vector<Student> students = readStudentDataFromCSV(filename);
    if (students.empty()) {
        cerr << "No student data available. Exiting." << endl;
        return 1;
    }

    int choice;
    do {
        cout << "=====================================" << endl;
        cout << "   Student Marks Management System" << endl;
        cout << "=====================================" << endl;
        cout << "Options:" << endl;
        cout << "1. Update Marks" << endl;
        cout << "2. View Student Details" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                {
                    int rollNumber, marks;
                    string subject;
                    cout << "Enter roll number of student: ";
                    cin >> rollNumber;
                    cout << "Enter subject (Maths/Science/English): ";
                    cin >> subject;
                    cout << "Enter new marks: ";
                    cin >> marks;
                    updateMarks(students, rollNumber, marks, subject);
                }
                break;
            case 2:
                sortStudentsByTotalMarks(students);
                displayStudentDetails(students);
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 3);

    return 0;
}