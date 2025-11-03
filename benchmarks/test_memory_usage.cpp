#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "../include/student.h"
#include "../include/student_base_1.h"
#include "../include/student_base_2.h"
#include "../include/student_base_3.h"

// ----------------- Estimate memory of a single Student -----------------
size_t getStudentMemory(const Student& s) {
    size_t mem = sizeof(Student);
    mem += s.m_name.capacity();
    mem += s.m_surname.capacity();
    mem += s.m_email.capacity();
    mem += s.m_group.capacity();
    mem += s.m_phone_number.capacity();
    return mem;
}

// ----------------- Estimate memory of StudentBase1 -----------------
size_t estimateMemory(const StudentBase1& db) {
    size_t mem = sizeof(db);

    // Students list
    mem += db.students.size() * sizeof(Student);
    for (const auto& s : db.students) mem += getStudentMemory(s);

    // nameSurnameStudentMap
    mem += db.nameSurnameStudentMap.size() * (sizeof(std::pair<StudentBase1::name_surname_pair, std::vector<Student*>>));
    for (const auto& [key, vec] : db.nameSurnameStudentMap) {
        mem += key.first.capacity() + key.second.capacity(); // strings
        mem += vec.capacity() * sizeof(Student*);
    }

    // studentGroupCountMap
    mem += db.studentGroupCountMap.size() * sizeof(std::pair<StudentBase1::name_surname_group_triplet, size_t>);

    // emailStudentMap
    mem += db.emailStudentMap.size() * sizeof(std::pair<std::string, Student*>);
    for (const auto& [email, ptr] : db.emailStudentMap) mem += email.capacity();

    return mem;
}

// ----------------- Estimate memory of StudentBase2 -----------------
size_t estimateMemory(const StudentBase2& db) {
    size_t mem = sizeof(db);

    // Students list
    mem += db.students.size() * sizeof(Student);
    for (const auto& s : db.students) mem += getStudentMemory(s);

    // nameSurnameStudentMap
    mem += db.nameSurnameStudentMap.size() * sizeof(std::pair<StudentBase2::name_surname_pair, std::vector<Student*>>);
    for (const auto& [key, vec] : db.nameSurnameStudentMap) {
        mem += key.first.capacity() + key.second.capacity();
        mem += vec.capacity() * sizeof(Student*);
    }

    // studentGroupCountMap
    mem += db.studentGroupCountMap.size() * sizeof(std::pair<StudentBase2::name_surname_group_triplet, size_t>);

    // emailStudentMap
    mem += db.emailStudentMap.size() * sizeof(std::pair<std::string, Student*>);
    for (const auto& [email, ptr] : db.emailStudentMap) mem += email.capacity();

    return mem;
}

// ----------------- Estimate memory of StudentBase3 -----------------
size_t estimateMemory(const StudentBase3& db) {
    size_t mem = sizeof(db);

    // Students vector
    mem += db.students.capacity() * sizeof(Student);
    for (const auto& s : db.students) mem += getStudentMemory(s);

    return mem;
}

// ----------------- Utility to get CSV files -----------------
std::vector<std::string> getCSVFiles(const std::string& folderPath) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".csv") files.push_back(entry.path().string());
    }
    std::sort(files.begin(), files.end());
    return files;
}

// ----------------- Template memory benchmark -----------------
template<typename T>
void testMemory(const std::vector<std::string>& csvFiles, const std::string& outputFolder) {
    std::ofstream resultCSV(outputFolder + "/" + typeid(T).name() + "_memory.csv");
    resultCSV << "Size,MemoryBytes\n";

    for (const auto& csvFile : csvFiles) {
        T db = T::fromCSV(csvFile);

        size_t memUsed = 0;
        if constexpr (std::is_same_v<T, StudentBase1>) memUsed = estimateMemory(db);
        else if constexpr (std::is_same_v<T, StudentBase2>) memUsed = estimateMemory(db);
        else if constexpr (std::is_same_v<T, StudentBase3>) memUsed = estimateMemory(db);

        // Extract size from filename: "sample_10000.csv" -> "10000"
        std::string filename = std::filesystem::path(csvFile).filename().string();
        size_t underscorePos = filename.find('_');
        size_t dotPos = filename.find('.');
        std::string sizeStr = filename.substr(underscorePos + 1, dotPos - underscorePos - 1);

        std::cout << "File: " << filename << " -> Memory: " << memUsed << " bytes\n";
        resultCSV << sizeStr << "," << memUsed << "\n";
    }

    resultCSV.close();
}

// ----------------- Main -----------------
int main() {
    const std::string CSV_FOLDER = "/home/bohdan/code/algorithms/homework-1/students-csv-files";
    const std::string OUTPUT_FOLDER = "/home/bohdan/code/algorithms/homework-1/benchmarks/benchmark-results/memory";

    if (!std::filesystem::exists(OUTPUT_FOLDER)) {
        std::cout << "Output folder does not exist.\n";
        return 1;
    }

    const auto csvFiles = getCSVFiles(CSV_FOLDER);

    testMemory<StudentBase1>(csvFiles, OUTPUT_FOLDER);
    testMemory<StudentBase2>(csvFiles, OUTPUT_FOLDER);
    testMemory<StudentBase3>(csvFiles, OUTPUT_FOLDER);

    return 0;
}
