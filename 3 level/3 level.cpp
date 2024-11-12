#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    string firstName;
    string lastName;
    string address;
    string phone;
};


void RW(const vector<Student>& students) {
    ofstream outFile("INFO.DAT", ios::binary);
    if (outFile.is_open()) {
        for (const auto& student : students) {
            size_t firstNameLen = student.firstName.size();
            size_t lastNameLen = student.lastName.size();
            size_t addressLen = student.address.size();
            size_t phoneLen = student.phone.size();

            outFile.write(reinterpret_cast<char*>(&firstNameLen), sizeof(firstNameLen));
            outFile.write(student.firstName.c_str(), firstNameLen);
            outFile.write(reinterpret_cast<char*>(&lastNameLen), sizeof(lastNameLen));
            outFile.write(student.lastName.c_str(), lastNameLen);
            outFile.write(reinterpret_cast<char*>(&addressLen), sizeof(addressLen));
            outFile.write(student.address.c_str(), addressLen);
            outFile.write(reinterpret_cast<char*>(&phoneLen), sizeof(phoneLen));
            outFile.write(student.phone.c_str(), phoneLen);
        }
        outFile.close();
    }
    else {
        cout << "Error opening file INFO.DAT" << endl;
    }
}


void RD() {
    ifstream inFile("INFO.DAT", ios::binary);
    if (inFile.is_open()) {
        while (inFile) {
            size_t firstNameLen;
            inFile.read(reinterpret_cast<char*>(&firstNameLen), sizeof(firstNameLen));
            if (inFile.eof()) break;

            string firstName(firstNameLen, '\0');
            inFile.read(&firstName[0], firstNameLen);

            size_t lastNameLen;
            inFile.read(reinterpret_cast<char*>(&lastNameLen), sizeof(lastNameLen));
            string lastName(lastNameLen, '\0');
            inFile.read(&lastName[0], lastNameLen);

            size_t addressLen;
            inFile.read(reinterpret_cast<char*>(&addressLen), sizeof(addressLen));
            string address(addressLen, '\0');
            inFile.read(&address[0], addressLen);

            size_t phoneLen;
            inFile.read(reinterpret_cast<char*>(&phoneLen), sizeof(phoneLen));
            string phone(phoneLen, '\0');
            inFile.read(&phone[0], phoneLen);

            cout << "Name: " << firstName << " " << lastName << ", Address: " << address << ", Phone: " << phone << endl;
        }
        inFile.close();
    }
    else {
        cout << "Error opening file INFO.DAT" << endl;
    }
}


void RWText(const vector<Student>& students) {
    ofstream outFile("INFO.TXT");
    if (outFile.is_open()) {
        for (const auto& student : students) {
            outFile << student.firstName << " " << student.lastName << ", " << student.address << ", " << student.phone << endl;
        }
        outFile.close();
    }
    else {
        cout << "Error opening file INFO.TXT" << endl;
    }
}


void RDText() {
    ifstream inFile("INFO.TXT");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
    else {
        cout << "Error opening file INFO.TXT" << endl;
    }
}


bool compareByPhone(const Student& a, const Student& b) {
    return a.phone < b.phone;
}


void displaySortedStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), compareByPhone);
    for (const auto& student : students) {
        cout << "Phone: " << student.phone << ", Name: " << student.lastName << ", " << student.firstName << endl;
    }
}

int main() {
    vector<Student> students = {
        {"John", "Doe", "123 Elm St", "555-1234"},
        {"Jane", "Smith", "456 Oak St", "555-5678"},
        {"Alice", "Johnson", "789 Pine St", "555-8765"},
        {"Bob", "Brown", "101 Maple St", "555-4321"}
    };

    RW(students);    
    RD();         

    RWText(students); 
    RDText();         

    cout << "\nSorted Students by Phone Number:" << endl;
    displaySortedStudents(students); 

    return 0;
}
