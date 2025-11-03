#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <filesystem>
#include <algorithm>
#include "../include/student.h"
#include "../include/student_base_1.h"
#include "../include/student_base_2.h"
#include "../include/student_base_3.h"


// ----------------- Read CSV and return Student objects -----------------
std::vector<Student> readStudentsFromCSV(const std::string& csvPath) {
    std::vector<Student> students;
    std::ifstream file(csvPath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + csvPath);
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string m_name, m_surname, m_email;
        std::string m_birth_year, m_birth_month, m_birth_day;
        std::string m_group, m_rating, m_phone_number;

        std::getline(ss, m_name, ',');
        std::getline(ss, m_surname, ',');
        std::getline(ss, m_email, ',');
        std::getline(ss, m_birth_year, ',');
        std::getline(ss, m_birth_month, ',');
        std::getline(ss, m_birth_day, ',');
        std::getline(ss, m_group, ',');
        std::getline(ss, m_rating, ',');
        std::getline(ss, m_phone_number, ',');

        students.push_back({
            m_name,
            m_surname,
            m_email,
            std::stoi(m_birth_year),
            std::stoi(m_birth_month),
            std::stoi(m_birth_day),
            m_group,
            std::stof(m_rating),
            m_phone_number
        });
    }

    return students;
}

std::vector<Student*> getStudentPointers(std::vector<Student>& students) {
    std::vector<Student*> ptrs;
    ptrs.reserve(students.size());
    for (auto& s : students) ptrs.push_back(&s);
    return ptrs;
}

std::vector<std::string> getCSVFiles(const std::string& folderPath) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".csv") {
            files.push_back(entry.path().string());
        }
    }
    std::sort(files.begin(), files.end());
    return files;
}

// ----------------- Template performance test -----------------
template<typename T>
void testPerformance(const std::vector<std::string>& csvFiles, const std::string& outputFolder) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::ofstream resultCSV(outputFolder + "/" + typeid(T).name() + "_results.csv");
    resultCSV << "Size,OperationsPer10Sec\n";

    for (const auto& csvFile : csvFiles) {
        T db = T::fromCSV(csvFile);

        std::vector<Student> allStudentsVec = readStudentsFromCSV(csvFile);
        std::vector<Student*> allStudents = getStudentPointers(allStudentsVec);

        size_t operationsCount = 0;
        auto startTime = std::chrono::steady_clock::now();

        std::uniform_int_distribution<size_t> dist(0, allStudents.size() - 1);
        std::vector<int> opsWeights = {1, 5, 1};
        std::discrete_distribution<int> opDist(opsWeights.begin(), opsWeights.end());

        while (true) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
            if (elapsed >= 10) break;

            int op = opDist(gen);

            if (op == 0) {
                auto s = allStudents[dist(gen)];
                db.getStudentsByName(s->m_name, s->m_surname);
            } else if (op == 1) {
                db.getGroupsSameStudentName();
            } else if (op == 2) {
                auto s = allStudents[dist(gen)];
                db.changeGroupByEmail(s->m_email, "TEST_GROUP");
            }

            ++operationsCount;
        }

        std::string filename = std::filesystem::path(csvFile).filename().string();
        size_t underscorePos = filename.find('_');
        size_t dotPos = filename.find('.');
        std::string sizeStr = filename.substr(underscorePos + 1, dotPos - underscorePos - 1);

        std::cout << "File: " << csvFile << " -> Operations: " << operationsCount << "\n";
        resultCSV << sizeStr << "," << operationsCount << "\n";
    }

    resultCSV.close();
}

int main() {
    const std::string CSV_FOLDER = "/home/bohdan/code/algorithms/homework-1/students-csv-files";
    const std::string OUTPUT_FOLDER = "/home/bohdan/code/algorithms/homework-1/benchmarks/benchmark-results/operations";

    if (!std::filesystem::exists(OUTPUT_FOLDER)) {
        std::cout << "Output folder does not exist.\n";
        return 1;
    }

    const auto csvFiles = getCSVFiles(CSV_FOLDER);

    testPerformance<StudentBase1>(csvFiles, OUTPUT_FOLDER);
    testPerformance<StudentBase2>(csvFiles, OUTPUT_FOLDER);
    testPerformance<StudentBase3>(csvFiles, OUTPUT_FOLDER);

    return 0;
}
