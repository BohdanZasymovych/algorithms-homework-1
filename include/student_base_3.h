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
private:
    std::vector<Student> students;

public:
    std::vector<Student*> getStudentsByName(const std::string& m_name, const std::string& m_surname) override;
    std::unordered_set<std::string> getGroupsSameStudentName() override;
    void changeGroupByEmail(const std::string& m_email, const std::string& newGroup) override;
    void saveToCSV(const std::vector<Student>& studentsToSave, const std::string& pathToSave) override;
    static StudentBase3 fromCSV(const std::string& pathToCSV);
};

#endif //HOMEWORK_1_STUDENT_BASE_3_H