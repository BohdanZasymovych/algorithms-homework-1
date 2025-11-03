//
// Created by bohdan on 11/2/25.
//

#ifndef HOMEWORK_1_STUDENT_H
#define HOMEWORK_1_STUDENT_H

#include <string>


struct Student {

    std::string m_name;     // ім'я українською

    std::string m_surname;      // прізвище українською

    std::string m_email;     // [a-z.]*@student.org

    int m_birth_year;     // 1950..2010

    int m_birth_month;     // 1..12

    int m_birth_day;     // 1..Number of days in m_birth_month

    std::string m_group;        // [A-Z][A-Z][A-Z]-[0-9][0-9]

    float m_rating;     // 0..100

    std::string m_phone_number; // 38(0xx)xx-xx-xxx

    // bool operator<(const Student& other) const {
    //     return (
    //         m_name == other.m_name and
    //         m_surname == other.m_surname and
    //         m_email == other.m_email and
    //         m_birth_year == other.m_birth_year and
    //         m_birth_day == other.m_birth_day and
    //         m_birth_month == other.m_birth_month and
    //         m_group == other.m_group and
    //         m_rating == other.m_rating and
    //         m_phone_number == other.m_phone_number
    //         );
    // }
};

#endif //HOMEWORK_1_STUDENT_H