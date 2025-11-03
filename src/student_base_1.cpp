#include "../include/student_base_1.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <unordered_set>


std::vector<Student*> StudentBase1::getStudentsByName(const std::string& m_name, const std::string& m_surname) {
    const auto it = nameSurnameStudentMap.find(std::pair(m_name, m_surname));
    if (it == nameSurnameStudentMap.end()) {
        return {};
    }
    return it->second;
}

std::unordered_set<std::string> StudentBase1::getGroupsSameStudentName() {
    std::unordered_set<std::string> groups;
    for (auto& [key, val] : studentGroupCountMap) {
        if (val > 1) {
            groups.insert(key.second);
        }
    }

    return groups;
}

void StudentBase1::changeGroupByEmail(const std::string& m_email, const std::string& newGroup) {
    Student* student = emailStudentMap.at(m_email);
    std::string name = student->m_name;
    std::string surname = student->m_surname;
    std::string prevGroup = student->m_group;

    student->m_group = newGroup;
    if (studentGroupCountMap[std::pair(std::pair(name, surname), prevGroup)] > 1) {
        --studentGroupCountMap[std::pair(std::pair(name, surname), prevGroup)];
    } else {
        studentGroupCountMap.erase(std::pair(std::pair(name, surname), prevGroup));
    }
    ++studentGroupCountMap[std::pair(std::pair(name, surname), newGroup)];
}

StudentBase1 StudentBase1::fromCSV(const std::string& pathToCSV) {
    StudentBase1 studentBase;

    std::fstream file;
    file.exceptions(std::ios::badbit);
    file.open(pathToCSV);

    std::string line;
    std::getline(file, line);
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

        studentBase.students.emplace_back(
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

        Student* studentPtr = &studentBase.students.back();
        name_surname_pair ns_pair{m_name, m_surname};
        studentBase.nameSurnameStudentMap[ns_pair].push_back(studentPtr);

        name_surname_group_triplet nsg_triplet{{m_name, m_surname}, m_group};
        ++studentBase.studentGroupCountMap[nsg_triplet];

        studentBase.emailStudentMap.insert({m_email, studentPtr});
    }

    return studentBase;
}
