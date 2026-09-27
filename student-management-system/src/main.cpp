#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

struct Student {
    int id{};
    std::string name;
    std::string course;
    double marks{};
};

namespace {
const std::string DATA_FILE = "students.csv";

std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::string readText(const std::string& prompt) {
    std::string value;
    do {
        std::cout << prompt;
        std::getline(std::cin, value);
        value = trim(value);
        if (value.empty()) std::cout << "This field cannot be empty.\n";
        else if (value.find(',') != std::string::npos) {
            std::cout << "Commas are not supported in names or courses.\n";
            value.clear();
        }
    } while (value.empty());
    return value;
}

int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream input(line);
        int value;
        char extra;
        if (input >> value && !(input >> extra)) return value;
        std::cout << "Please enter a whole number.\n";
    }
}

double readMarks() {
    while (true) {
        std::cout << "Marks (0-100): ";
        std::string line;
        std::getline(std::cin, line);
        std::istringstream input(line);
        double value;
        char extra;
        if ((input >> value) && !(input >> extra) && value >= 0 && value <= 100)
            return value;
        std::cout << "Enter a number from 0 to 100.\n";
    }
}

std::vector<Student> loadStudents() {
    std::vector<Student> students;
    std::ifstream file(DATA_FILE);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream row(line);
        std::string idText, name, course, marksText;
        if (!std::getline(row, idText, ',') || !std::getline(row, name, ',') ||
            !std::getline(row, course, ',') || !std::getline(row, marksText)) continue;
        try {
            Student student{std::stoi(idText), name, course, std::stod(marksText)};
            students.push_back(student);
        } catch (const std::exception&) {
            // Skip malformed rows so one damaged record does not stop the app.
        }
    }
    return students;
}

bool saveStudents(const std::vector<Student>& students) {
    std::ofstream file(DATA_FILE, std::ios::trunc);
    if (!file) return false;
    file << std::fixed << std::setprecision(2);
    for (const auto& student : students)
        file << student.id << ',' << student.name << ',' << student.course << ','
             << student.marks << '\n';
    return static_cast<bool>(file);
}

auto findStudent(std::vector<Student>& students, int id) {
    return std::find_if(students.begin(), students.end(),
                        [id](const Student& student) { return student.id == id; });
}

void displayStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }
    std::cout << '\n' << std::left << std::setw(10) << "ID" << std::setw(28)
              << "NAME" << std::setw(24) << "COURSE" << "MARKS\n"
              << std::string(72, '-') << '\n';
    for (const auto& student : students)
        std::cout << std::left << std::setw(10) << student.id << std::setw(28)
                  << student.name.substr(0, 26) << std::setw(24)
                  << student.course.substr(0, 22) << std::fixed << std::setprecision(2)
                  << student.marks << '\n';
}

void addStudent(std::vector<Student>& students) {
    const int id = readInt("Student ID: ");
    if (id <= 0) {
        std::cout << "ID must be greater than zero.\n";
        return;
    }
    if (findStudent(students, id) != students.end()) {
        std::cout << "That ID already exists.\n";
        return;
    }
    Student student{id, readText("Name: "), readText("Course: "), readMarks()};
    students.push_back(student);
    std::cout << (saveStudents(students) ? "Student added.\n" : "Could not save the data file.\n");
}

void updateStudent(std::vector<Student>& students) {
    const int id = readInt("Enter the ID to update: ");
    auto student = findStudent(students, id);
    if (student == students.end()) {
        std::cout << "Student not found.\n";
        return;
    }
    student->name = readText("New name: ");
    student->course = readText("New course: ");
    student->marks = readMarks();
    std::cout << (saveStudents(students) ? "Student updated.\n" : "Could not save the data file.\n");
}

void deleteStudent(std::vector<Student>& students) {
    const int id = readInt("Enter the ID to delete: ");
    auto student = findStudent(students, id);
    if (student == students.end()) {
        std::cout << "Student not found.\n";
        return;
    }
    students.erase(student);
    std::cout << (saveStudents(students) ? "Student deleted.\n" : "Could not save the data file.\n");
}

void showMenu() {
    std::cout << "\n=== Student Management System ===\n"
              << "1. Add student\n2. Update student\n3. Delete student\n"
              << "4. Display all students\n5. Exit\n";
}
}  // namespace

int main() {
    auto students = loadStudents();
    std::cout << "Student records are stored in " << DATA_FILE
              << " in the current working directory.\n";
    while (true) {
        showMenu();
        switch (readInt("Choose an option: ")) {
            case 1: addStudent(students); break;
            case 2: updateStudent(students); break;
            case 3: deleteStudent(students); break;
            case 4: displayStudents(students); break;
            case 5: std::cout << "Goodbye!\n"; return 0;
            default: std::cout << "Choose an option from 1 to 5.\n";
        }
    }
}
