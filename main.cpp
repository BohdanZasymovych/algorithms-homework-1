#include "include/student_base_1.h"
#include "include/student_base_2.h"
#include "include/student_base_3.h"
#include "include/student_base_sort.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

std::vector<Student> csvToVector(const std::string& pathToCSV);


int main() {
    // StudentBase1 studentBase1 = StudentBase1::fromCSV("/home/bohdan/code/algorithms/homework-1/students.csv");
    // StudentBase2 studentBase2 = StudentBase2::fromCSV("/home/bohdan/code/algorithms/homework-1/students.csv");
    // StudentBase3 studentBase3 = StudentBase3::fromCSV("/home/bohdan/code/algorithms/homework-1/students.csv");

    std::vector<Student> students = csvToVector("/home/bohdan/code/algorithms/homework-1/students.csv");
    std::locale::global(std::locale("uk_UA.UTF-8"));
    std::wcout.imbue(std::locale("uk_UA.UTF-8"));
    std::cout << std::boolalpha;
    //
    // std::vector<Student> students = {
    //     {"Іван", "Петренко", "ivan.petrenko@student.org", 2002, 5, 13, "CS-21", 90.5, "38(067)12-34-567"},
    //     {"Андрій", "Шевченко", "andriy.shevchenko@student.org", 2001, 2, 8, "CS-21", 82.1, "38(095)55-22-111"},
    //     {"Богдан", "Засимович", "bohdan.zasymovych@student.org", 2003, 7, 20, "CS-22", 95.3, "38(073)77-66-555"},
    //     {"Ганна", "Іваненко", "hanna.ivanenko@student.org", 2000, 9, 2, "CS-20", 88.0, "38(096)33-22-444"},
    //     {"Андрій", "Андрухов", "andriy.andrukhov@student.org", 2002, 1, 30, "CS-21", 80.0, "38(068)99-88-777"},
    //     {"Іван", "Арсенюк", "ivan.arseniuk@student.org", 2003, 12, 1, "CS-22", 91.0, "38(097)10-20-300"},
    //     {"Богдан", "Ільків", "bohdan.ilkiv@student.org", 2001, 4, 5, "CS-20", 89.5, "38(093)45-67-890"}
    // };
    //
    // std::cout << "До сортування:\n";
    // for (const auto& s : students)
    //     std::cout << s.m_name << " " << s.m_surname << "\n";
    //
    auto start1 = std::chrono::high_resolution_clock::now();
    StudentBaseSort::sortBuildIn(students);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "Execution time: " << duration1.count() << " seconds\n";

    std::cout << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    StudentBaseSort::sortRadix(students);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "Execution time: " << duration2.count() << " seconds\n";

    // StudentBaseSort::sortBuildIn(students);

    // std::cout << "\nПісля сортування (спочатку ім'я, потім прізвище):\n";
    // for (const auto& s : students)
    //     std::cout << s.m_name << " " << s.m_surname << "\n";

    return 0;

    // std::vector<Student> students;
    // for (const auto* studentPtr : studentBase.getStudentsByName("Любов", "Дорошенко")) {
    //     students.push_back(*studentPtr);
    // }

    // const std::unordered_set<std::string> res1 = studentBase1.getGroupsSameStudentName();
    // const std::unordered_set<std::string> res2 = studentBase2.getGroupsSameStudentName();
    // const std::unordered_set<std::string> res3 = studentBase3.getGroupsSameStudentName();
    // std::cout << (res1 == res2) << std::endl;
    // std::cout << (res1 == res3) << std::endl;
    // std::cout << (res2 == res3) << std::endl;
    // for (const auto& str : res) {
    //     std::cout << str << std::endl;
    // }

    // studentBase.changeGroupByEmail("ivan.kravchenko@student.org", "PKN-2");

    // studentBase.saveToCSV(students, "/home/bohdan/code/algorithms/homework-1/out.csv");
}

std::vector<Student> csvToVector(const std::string& pathToCSV) {
    std::vector<Student> students;

    std::fstream file;
    file.exceptions(std::ios::badbit);
    file.open(pathToCSV);

    std::string line;
    std::getline(file, line);
    size_t i = 0;
    while (std::getline(file, line)) {

        std::string m_name;
        std::string m_surname;
        std::string m_email;
        std::string m_birth_year;
        std::string m_birth_month;
        std::string m_birth_day;
        std::string m_group;
        std::string m_rating;
        std::string m_phone_number;

        std::stringstream ss(line);

        std::getline(ss, m_name, ',');
        std::getline(ss, m_surname, ',');
        std::getline(ss, m_email, ',');
        std::getline(ss, m_birth_year, ',');
        std::getline(ss, m_birth_month, ',');
        std::getline(ss, m_birth_day, ',');
        std::getline(ss, m_group, ',');
        std::getline(ss, m_rating, ',');
        std::getline(ss, m_phone_number, ',');

        students.emplace_back(
            m_name,
            m_surname,
            m_email,
            std::stoi(m_birth_year),
            std::stoi(m_birth_month),
            std::stoi(m_birth_day),
            m_group,
            std::stof(m_rating),
            m_phone_number
        );
    }

    return students;
}