 #include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <windows.h>
void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#else
void setConsoleColor(int color) {
    std::cout << "\033[" << color << "m";
}
#endif

using namespace std;

struct Course {
    string name;
    float credit;
    float grade;
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printCourseDetails(const Course& course, int index) {
    cout << fixed << setprecision(2);
    cout << "Course " << index + 1 << ": " << course.name << "\n";
    cout << "  Credits: " << course.credit << "\n";
    cout << "  Grade: " << course.grade << "\n";
    cout << "  Grade Points: " << course.credit * course.grade << "\n\n";
}

int main() {
    int numCourses;
    vector<Course> courses;
    float totalCredits = 0, totalGradePoints = 0;

    cout << "=== CGPA CALCULATOR ===\n";
    cout << "Enter the number of courses: ";
    while (!(cin >> numCourses) || numCourses <= 0) {
        cout << "Please enter a valid positive integer: ";
        clearInputBuffer();
    }

    clearInputBuffer();

    for (int i = 0; i < numCourses; ++i) {
        Course c;
        cout << "\n--- Enter details for Course " << i + 1 << " ---\n";
        cout << "Course name: ";
        getline(cin, c.name);

        cout << "Credits (e.g., 3): ";
        while (!(cin >> c.credit) || c.credit <= 0) {
            cout << "Enter a valid credit value: ";
            clearInputBuffer();
        }

        cout << "Grade (on 10-point scale): ";
        while (!(cin >> c.grade) || c.grade < 0 || c.grade > 10) {
            cout << "Enter grade between 0 and 10: ";
            clearInputBuffer();
        }

        clearInputBuffer();

        totalCredits += c.credit;
        totalGradePoints += c.credit * c.grade;
        courses.push_back(c);
    }

    setConsoleColor(36); // Cyan color
    cout << "\n=== Course Summary ===\n";
    for (size_t i = 0; i < courses.size(); ++i) {
        printCourseDetails(courses[i], i);
    }

    float cgpa = (totalCredits == 0) ? 0 : totalGradePoints / totalCredits;

    setConsoleColor(33); // Yellow color
    cout << "Total Credits: " << totalCredits << "\n";
    cout << "Total Grade Points: " << totalGradePoints << "\n";

    setConsoleColor(32); // Green color
    cout << "Your CGPA is: " << fixed << setprecision(2) << cgpa << "\n";

    setConsoleColor(0); // Reset to default
    return 0;
}
