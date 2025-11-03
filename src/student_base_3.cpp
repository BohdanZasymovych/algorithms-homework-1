#include "../include/student_base_3.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>


std::vector<Student*> StudentBase3::getStudentsByName(const std::string& m_name, const std::string& m_surname) {
    std::vector<Student*> studentsByName;

    for (auto& student : students) {
        if (student.m_name == m_name and student.m_surname == m_surname) {
            studentsByName.push_back(&student);
        }
    }

    return studentsByName;
}

std::unordered_set<std::string> StudentBase3::getGroupsSameStudentName() {
    using name_surname_pair = std::pair<std::string, std::string>;
    using name_surname_group_triplet = std::pair<name_surname_pair, std::string>;
    struct nameSurnameGroupTripletHash {
        size_t operator()(const name_surname_group_triplet& p) const {
            constexpr std::hash<std::string> h;
            const size_t h1 = h(p.first.first);
            const size_t h2 = h(p.first.second);
            const size_t h3 = h(p.second);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
    std::unordered_set<name_surname_group_triplet, nameSurnameGroupTripletHash> studentGroupSet; // ((name, surname), group) : count

    std::unordered_set<std::string> groups;
    for (auto& student : students) {
        const name_surname_group_triplet nsg_triplet(name_surname_pair(student.m_name, student.m_surname), student.m_group);
        if (studentGroupSet.contains(nsg_triplet)) {
            groups.insert(student.m_group);
        } else {
            studentGroupSet.insert(nsg_triplet);
        }
    }

    return groups;
}

void StudentBase3::changeGroupByEmail(const std::string& m_email, const std::string& newGroup) {
    for (auto& student : students) {
        if (student.m_email == m_email) {
            student.m_group = newGroup;
            return;
        }
    }

    throw std::out_of_range("no student with this email");
}

StudentBase3 StudentBase3::fromCSV(const std::string& pathToCSV) {
    StudentBase3 studentBase;

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
    }

    return studentBase;
}
