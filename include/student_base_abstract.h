//
// Created by bohdan on 11/2/25.
//

#ifndef HOMEWORK_1_STUDENT_BASE_ABSTRACT_H
#define HOMEWORK_1_STUDENT_BASE_ABSTRACT_H

#include "student.h"
#include <vector>
#include <string>
#include <unordered_set>


class StudentBaseAbstract {
public:
    virtual ~StudentBaseAbstract() = default;
    virtual std::vector<Student*> getStudentsByName(const std::string& m_name, const std::string& m_surname) = 0;
    virtual std::unordered_set<std::string> getGroupsSameStudentName() = 0;
    virtual void changeGroupByEmail(const std::string& m_email, const std::string& newGroup) = 0;
    virtual void saveToCSV(const std::vector<Student>& students, const std::string& pathToSave) = 0;
};

#endif //HOMEWORK_1_STUDENT_BASE_ABSTRACT_H