//
// Created by bohdan on 11/2/25.
//

#ifndef HOMEWORK_1_STUDENT_BASE_2_H
#define HOMEWORK_1_STUDENT_BASE_2_H

#include "student.h"
#include "student_base_abstract.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include <utility>
#include <unordered_set>

class StudentBase2 final : public StudentBaseAbstract {
private:
    using name_surname_pair = std::pair<std::string, std::string>;
    using name_surname_group_triplet = std::pair<name_surname_pair, std::string>;

    std::list<Student> students;
    std::map<name_surname_pair, std::vector<Student*>> nameSurnameStudentMap; // (name, surname) : vector(student_ptr)
    std::map<name_surname_group_triplet, size_t> studentGroupCountMap; // ((name, surname), group) : count
    std::map<std::string, Student*> emailStudentMap; // email : student_ptr

public:
    std::vector<Student*> getStudentsByName(const std::string& m_name, const std::string& m_surname) override;
    std::unordered_set<std::string> getGroupsSameStudentName() override;
    void changeGroupByEmail(const std::string& m_email, const std::string& newGroup) override;
    void saveToCSV(const std::vector<Student>& studentsToSave, const std::string& pathToSave) override;
    static StudentBase2 fromCSV(const std::string& pathToCSV);
};

#endif //HOMEWORK_1_STUDENT_BASE_2_H