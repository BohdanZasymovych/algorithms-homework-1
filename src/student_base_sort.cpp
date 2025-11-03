//
// Created by bohdan on 11/3/25.
//

#include "../include/student_base_sort.h"
#include <algorithm>
#include <locale>
#include <sstream>
#include <fstream>


void StudentBaseSort::sortBuildIn(std::vector<Student>& students) {
    const std::locale loc("uk_UA.UTF-8");
    const auto& coll = std::use_facet<std::collate<char>>(loc);

    std::ranges::sort(students, [&](const Student& s1, const Student& s2) {
        const int cmpName = coll.compare(
            s1.m_name.data(), s1.m_name.data() + s1.m_name.size(),
            s2.m_name.data(), s2.m_name.data() + s2.m_name.size()
        );
        if (cmpName != 0)
            return cmpName < 0;

        const int cmpSurname = coll.compare(
            s1.m_surname.data(), s1.m_surname.data() + s1.m_surname.size(),
            s2.m_surname.data(), s2.m_surname.data() + s2.m_surname.size()
        );
        return cmpSurname < 0;
    });
}

void StudentBaseSort::sort(std::vector<Student>& students, size_t left, size_t right, size_t d) {
    if (right - left <= 1) {return;}

    constexpr size_t R = 34;
    std::vector<std::vector<Student>> buckets(R);

    for (size_t i=left; i<right; ++i) {
        const char32_t c = charAt(students[i], d);
        buckets[letterToIndex(c)].push_back(students[i]);
    }

    size_t index = left;
    for (size_t r=0; r<R; ++r) {
        if (!buckets[r].empty()) {
            const size_t bucketSize = buckets[r].size();
            for (size_t i=0; i<bucketSize; ++i) {
                students[index+i] = buckets[r][i];
            }
            if (r != 0) {
                sort(students, index, index+bucketSize, d+1);
            }
            index += bucketSize;
        }
    }
}


void StudentBaseSort::sortRadix(std::vector<Student> &students) {
    sort(students, 0, students.size(), 0);
}


void StudentBaseSort::saveToCSV(const std::vector<Student>& studentsToSave, const std::string& pathToSave) {
    std::ofstream outputFile;
    outputFile.exceptions(std::ios::badbit);
    outputFile.open(pathToSave);

    outputFile << "m_name,m_surname,m_email,m_birth_year,m_birth_month,m_birth_day,m_group,m_rating,m_phone_number\n";
    for (const auto& student : studentsToSave) {
        outputFile << student.m_name << ',';
        outputFile << student.m_surname << ',';
        outputFile << student.m_email << ',';
        outputFile << student.m_birth_year << ',';
        outputFile << student.m_birth_month << ',';
        outputFile << student.m_birth_day << ',';
        outputFile << student.m_group << ',';
        outputFile << student.m_rating << ',';
        outputFile << student.m_phone_number << '\n';
    }
}

