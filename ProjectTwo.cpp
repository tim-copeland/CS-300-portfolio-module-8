#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Structure to hold course information 
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course() {}
};

// Hash Table Implementation for efficient searching 
class HashTable {
private:
    struct Node {
        Course course;
        Node* next;
        Node() : next(nullptr) {}
        Node(Course aCourse) : course(aCourse), next(nullptr) {}
    };

    vector<Node*> nodes;
    unsigned int tableSize = 179; // Prime number to reduce collisions

    // Hash function to map course numbers to table indices
    unsigned int hash(string key) {
        unsigned int hashVal = 0;
        for (char ch : key) {
            hashVal = hashVal * 31 + ch;
        }
        return hashVal % tableSize;
    }

public:
    HashTable() {
        nodes.resize(tableSize, nullptr);
    }

    // Insert a course into the hash table
    void Insert(Course course) {
        unsigned int index = hash(course.courseNumber);
        Node* newNode = new Node(course);
        
        if (nodes[index] == nullptr) {
            nodes[index] = newNode;
        } else {
            // Collision handling using chaining
            newNode->next = nodes[index];
            nodes[index] = newNode;
        }
    }

    // Search for a specific course by its number
    Course Search(string courseNumber) {
        unsigned int index = hash(courseNumber);
        Node* curr = nodes[index];
        while (curr != nullptr) {
            if (curr->course.courseNumber == courseNumber) {
                return curr->course;
            }
            curr = curr->next;
        }
        return Course(); // Return empty course if not found
    }

    // Helper to retrieve all courses for sorting purposes
    vector<Course> GetAllCourses() {
        vector<Course> allCourses;
        for (auto node : nodes) {
            Node* curr = node;
            while (curr != nullptr) {
                allCourses.push_back(curr->course);
                curr = curr->next;
            }
        }
        return allCourses;
    }
};

//  Logic to format and display course data 
void displayCourse(Course course) {
    cout << course.courseNumber << ", " << course.courseTitle << endl;
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "No prerequisites." << endl;
    }
}

// Logic to parse the input file 
void loadCourses(string filename, HashTable* hashTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> row;

        while (getline(ss, token, ',')) {
            row.push_back(token);
        }

        // Validate that line has at least a number and a title
        if (row.size() < 2) continue;

        Course course;
        course.courseNumber = row[0];
        course.courseTitle = row[1];
        for (size_t i = 2; i < row.size(); ++i) {
            course.prerequisites.push_back(row[i]);
        }
        hashTable->Insert(course);
    }
    file.close();
    cout << "Data loaded successfully." << endl;
}

// Main User Interface 
int main() {
    HashTable* courseTable = new HashTable();
    string filename;
    string searchId;
    int choice = 0;

    cout << "Welcome to the ABCU Advising Assistance Program." << endl;

    while (choice != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        
        // Input validation for menu selection
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter the file name containing course data: ";
                cin >> filename;
                loadCourses(filename, courseTable);
                break;

            case 2: {
                vector<Course> courses = courseTable->GetAllCourses();
                if (courses.empty()) {
                    cout << "Error: No data loaded. Please select option 1 first." << endl;
                } else {
                    // Sort alphanumerically for the display list
                    sort(courses.begin(), courses.end(), [](Course a, Course b) {
                        return a.courseNumber < b.courseNumber;
                    });
                    cout << "Here is a sample schedule:" << endl;
                    for (const auto& c : courses) {
                        cout << c.courseNumber << ", " << c.courseTitle << endl;
                    }
                }
                break;
            }

            case 3:
                cout << "What course do you want to know about? ";
                cin >> searchId;
                // Standardize input to uppercase for matching
                for (auto & c: searchId) c = toupper(c);
                
                {
                    Course c = courseTable->Search(searchId);
                    if (!c.courseNumber.empty()) {
                        displayCourse(c);
                    } else {
                        cout << "Course " << searchId << " not found." << endl;
                    }
                }
                break;

            case 9:
                cout << "Thank you for using the advising assistant program!" << endl;
                break;

            default:
                cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}