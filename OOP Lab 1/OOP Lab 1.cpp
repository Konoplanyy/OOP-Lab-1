#include <iostream>
#include <fstream>
#include <string>

struct Student {
    char name[50];
    int age;
    int studentID;
    char faculty[50];
    char major[50];
    int year;
    float GPA;
    char address[100];
    char phone[15];
    char email[50];
};

// Запис інформації у текстовому форматі
void saveAsText(const Student& student) {
    std::ofstream file("student_info.txt");
    if (file.is_open()) {
        file << "Name: " << student.name << "\n";
        file << "Age: " << student.age << "\n";
        file << "Student ID: " << student.studentID << "\n";
        file << "Faculty: " << student.faculty << "\n";
        file << "Major: " << student.major << "\n";
        file << "Year: " << student.year << "\n";
        file << "GPA: " << student.GPA << "\n";
        file << "Address: " << student.address << "\n";
        file << "Phone: " << student.phone << "\n";
        file << "Email: " << student.email << "\n";
        file.close();
        std::cout << "Text information saved to student_info.txt\n";
    }
    else {
        std::cerr << "Error opening file for text output.\n";
    }
}

// Запис інформації у бінарному форматі
void saveAsBinary(const Student& student) {
    std::ofstream file("student_info.bin", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        file.close();
        std::cout << "Binary information saved to student_info.bin\n";
    }
    else {
        std::cerr << "Error opening file for binary output.\n";
    }
}

// Тестова функція для перевірки правильності збереження
void testSaveFunction() {
    Student student = {
        "John Doe", 21, 123456, "Engineering", "Computer Science",
        3, 3.8f, "123 Main St, City", "+1234567890", "johndoe@example.com"
    };

    saveAsText(student);
    saveAsBinary(student);

    // Перевірка коректності запису
    std::ifstream textFile("student_info.txt");
    std::ifstream binaryFile("student_info.bin", std::ios::binary);

    if (textFile.is_open() && binaryFile.is_open()) {
        std::cout << "Test passed: Files successfully created.\n";
    }
    else {
        std::cerr << "Test failed: Files could not be created.\n";
    }

    textFile.close();
    binaryFile.close();
}

int main() {
    testSaveFunction();
    return 0;
}
