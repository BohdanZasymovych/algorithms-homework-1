//
// Created by bohdan on 11/3/25.
//

#ifndef HOMEWORK_1_STUDENT_BASE_SORT_H
#define HOMEWORK_1_STUDENT_BASE_SORT_H

#include "student.h"
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

class StudentBaseSort final {
public:
    static size_t letterToIndex(char32_t c) {
        if (c == 0) return 0;

        if (c >= U'А' && c <= U'Я') c = c - U'А' + U'а';
        else if (c == U'Є') c = U'є';
        else if (c == U'І') c = U'і';
        else if (c == U'Ї') c = U'ї';
        else if (c == U'Ґ') c = U'ґ';

        static const std::u32string alphabet = U"абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
        const auto pos = alphabet.find(c);
        if (pos != std::u32string::npos) return pos + 1;
        return 0;
    }

    static char32_t charAt(const Student& s, size_t d) {
        static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;

        const std::u32string name32 = conv.from_bytes(s.m_name);
        if (d < name32.size()) {return name32[d];}

        if (d == name32.size()) {return 0;}

        const std::u32string surname32 = conv.from_bytes(s.m_surname);
        const size_t surnameIndex = d - name32.size() - 1;
        if (surnameIndex < surname32.size()) return surname32[surnameIndex];

        return 0;
    }

    static void sort(std::vector<Student>& students, size_t left, size_t right, size_t d);
    static void sortBuildIn(std::vector<Student>& students);

    static void sortRadix(std::vector<Student>& students);

    static void saveToCSV(const std::vector<Student>& studentsToSave, const std::string& pathToSave);
};

#endif //HOMEWORK_1_STUDENT_BASE_SORT_H