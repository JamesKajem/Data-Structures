#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define the Course class
class Course {
private:
    string code;
    string title;
    vector<string> prerequisites;

public:
    Course(const string& c, const string& t, const vector<string>& p) : code(c), title(t), prerequisites(p) {}

    string getCode() const { return code; }
    string getTitle() const { return title; }
    const vector<string>& getPrerequisites() const { return prerequisites; }
};

// Function to load data from file
void loadData(const string& fileName, vector<Course>& courses) {
    cout << "Loading data from file: " << fileName << endl;

    ifstream file(fileName); // Open the file for reading

    if (file.is_open()) {
        string line;
        while (getline(file, line)) { // Read each line from the file
            istringstream iss(line);
            string code, title, prerequisite;
            vector<string> prerequisites;

            getline(iss, code, ','); // Extract course code
            getline(iss, title, ','); // Extract course title

            while (getline(iss, prerequisite, ',')) { // Extract prerequisites
                prerequisites.push_back(prerequisite);
            }

            // Create the Course object and add it to the vector
            courses.push_back(Course(code, title, prerequisites));
        }
        file.close(); 
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to print course list in alphanumeric order
void printAlphanumeric(const vector<Course>& courseList) {
    vector<Course> sortedList = courseList;
    sort(sortedList.begin(), sortedList.end(), [](const Course& a, const Course& b) {
        return a.getCode() < b.getCode();
    });
    cout << "Alphanumeric list of courses:\n";
    for (const Course& course : sortedList) {
        cout << "Code: " << course.getCode() << ", Title: " << course.getTitle() << endl;
    }
}

// Function to print course information based on course code
void printCourse(const string& courseCode, const vector<Course>& courses) {
    for (const Course& course : courses) {
        if (course.getCode() == courseCode) {
            cout << "Course Code: " << course.getCode() << endl;
            cout << "Course Title: " << course.getTitle() << endl;
            cout << "Prerequisites: ";
            for (const string& prereq : course.getPrerequisites()) {
                cout << prereq << " ";
            }
            cout << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

// Function to print the menu and get user choice
int menu() {
    int choice;
    cout << "\n Menu:\n";
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course Information\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Main function
int main() {
    vector<Course> courses;
    int choice;
    string fileName, courseCode;
    do {
        choice = menu();
        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin >> fileName;
                loadData(fileName, courses);
                break;
            case 2:
                printAlphanumeric(courses);
                break;
            case 3:
                cout << "Enter course code: ";
                cin >> courseCode;
                printCourse(courseCode, courses);
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
    return 0;
}
