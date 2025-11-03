//
// Created by bohdan on 11/2/25.
//

#ifndef HOMEWORK_1_STUDENT_BASE_1_H
#define HOMEWORK_1_STUDENT_BASE_1_H

#include "student.h"
#include "student_base_abstract.h"
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>

class StudentBase1 final : public StudentBaseAbstract {
private:
    using name_surname_pair = std::pair<std::string, std::string>;
    using name_surname_group_triplet = std::pair<name_surname_pair, std::string>;

    struct nameSurnamePairHash {
        size_t operator()(const name_surname_pair& p) const {
            constexpr std::hash<std::string> h;
            const size_t h1 = h(p.first);
            const size_t h2 = h(p.second);
            return h1 ^ (h2 << 1);
        }
    };

    struct nameSurnameGroupTripletHash {
        size_t operator()(const name_surname_group_triplet& p) const {
            constexpr std::hash<std::string> h;
            const size_t h1 = h(p.first.first);
            const size_t h2 = h(p.first.second);
            const size_t h3 = h(p.second);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    std::list<Student> students;
    std::unordered_map<name_surname_pair, std::vector<Student*>, nameSurnamePairHash> nameSurnameStudentMap; // (name, surname) : vector(student_ptr)
    std::unordered_map<name_surname_group_triplet, size_t, nameSurnameGroupTripletHash> studentGroupCountMap; // ((name, surname), group) : count
    std::unordered_map<std::string, Student*> emailStudentMap; // email : student_ptr

public:
    std::vector<Student*> getStudentsByName(const std::string& m_name, const std::string& m_surname) override;
    std::unordered_set<std::string> getGroupsSameStudentName() override;
    void changeGroupByEmail(const std::string& m_email, const std::string& newGroup) override;
    void saveToCSV(const std::vector<Student>& studentsToSave, const std::string& pathToSave) override;
    static StudentBase1 fromCSV(const std::string& pathToCSV);
};

#endif //HOMEWORK_1_STUDENT_BASE_1_H