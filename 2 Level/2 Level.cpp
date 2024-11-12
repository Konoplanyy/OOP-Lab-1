#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string lastName;
    string gender;
    int birthYear;
    int birthMonth;

    // Method to write a Student to a file
    void writeToFile(ofstream& outFile) const {
        size_t lastNameLength = lastName.size();
        outFile.write(reinterpret_cast<const char*>(&lastNameLength), sizeof(lastNameLength));
        outFile.write(lastName.c_str(), lastName.size());
        size_t genderLength = gender.size();
        outFile.write(reinterpret_cast<const char*>(&genderLength), sizeof(genderLength));
        outFile.write(gender.c_str(), gender.size());
        outFile.write(reinterpret_cast<const char*>(&birthYear), sizeof(birthYear));
        outFile.write(reinterpret_cast<const char*>(&birthMonth), sizeof(birthMonth));
    }

    // Method to read a Student from a file
    void readFromFile(ifstream& inFile) {
        size_t lastNameLength;
        inFile.read(reinterpret_cast<char*>(&lastNameLength), sizeof(lastNameLength));
        lastName.resize(lastNameLength);
        inFile.read(&lastName[0], lastNameLength);

        size_t genderLength;
        inFile.read(reinterpret_cast<char*>(&genderLength), sizeof(genderLength));
        gender.resize(genderLength);
        inFile.read(&gender[0], genderLength);

        inFile.read(reinterpret_cast<char*>(&birthYear), sizeof(birthYear));
        inFile.read(reinterpret_cast<char*>(&birthMonth), sizeof(birthMonth));
    }
};

void writeToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (const auto& student : students) {
        student.writeToFile(outFile);
    }

    outFile.close();
}

vector<Student> readFromFile(const string& filename) {
    vector<Student> students;
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return students;
    }

    while (inFile.peek() != EOF) {
        Student student;
        student.readFromFile(inFile);
        students.push_back(student);
    }

    inFile.close();
    return students;
}

void printSummerBirths(const vector<Student>& students) {
    for (const auto& student : students) {
        if (student.birthMonth >= 6 && student.birthMonth <= 8) {
            cout << student.lastName << endl;
        }
    }
}

int main() {
    vector<Student> students = {
        {"John Doe", "Male", 2000, 6},
        {"Jane Smith", "Female", 1999, 8},
        {"Alice Johnson", "Female", 2001, 12},
        {"Bob Brown", "Male", 1998, 7},
        {"Charlie White", "Male", 2000, 5}
    };

    string filename = "INFO.DAT";

    writeToFile(students, filename);
    vector<Student> loadedStudents = readFromFile(filename);

    cout << "Students born in summer: " << endl;
    printSummerBirths(loadedStudents);

    return 0;
}
