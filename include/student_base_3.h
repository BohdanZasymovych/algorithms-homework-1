//
// Created by bohdan on 11/2/25.
//

#ifndef HOMEWORK_1_STUDENT_BASE_3_H
#define HOMEWORK_1_STUDENT_BASE_3_H

#include "student.h"
#include "student_base_abstract.h"
#include <vector>
#include <string>
#include <unordered_set>

class StudentBase3 final : public StudentBaseAbstract {
public:
    std::vector<Student> students;

    std::vector<Student*> getStudentsByName(const std::string& m_name, const std::string& m_surname) override;
    std::unordered_set<std::string> getGroupsSameStudentName() override;
    void changeGroupByEmail(const std::string& m_email, const std::string& newGroup) override;
    static StudentBase3 fromCSV(const std::string& pathToCSV);
};

#endif //HOMEWORK_1_STUDENT_BASE_3_H