#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include "../include/student.h"
#include "../include/student_base_sort.h"

std::vector<Student> readStudentsFromCSV(const std::string& csvPath) {
    std::vector<Student> students;
    std::ifstream file(csvPath);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + csvPath);

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

std::vector<std::string> getCSVFiles(const std::string& folderPath) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".csv") files.push_back(entry.path().string());
    }
    std::sort(files.begin(), files.end());
    return files;
}

// ----------------- Benchmark template -----------------
void benchmarkSorting(const std::vector<std::string>& csvFiles, const std::string& outputFolder) {
    std::ofstream csvBuildIn(outputFolder + "/sortBuildIn_results.csv");
    std::ofstream csvRadix(outputFolder + "/sortRadix_results.csv");

    csvBuildIn << "Size,TimeMs\n";
    csvRadix << "Size,TimeMs\n";

    for (const auto& csvFile : csvFiles) {
        std::vector<Student> students = readStudentsFromCSV(csvFile);

        std::string filename = std::filesystem::path(csvFile).filename().string();
        size_t underscorePos = filename.find('_');
        size_t dotPos = filename.find('.');
        std::string sizeStr = filename.substr(underscorePos + 1, dotPos - underscorePos - 1);

        // -------- sortBuildIn ----------
        std::vector<Student> studentsCopy = students;
        auto start = std::chrono::high_resolution_clock::now();
        StudentBaseSort::sortBuildIn(studentsCopy);
        auto end = std::chrono::high_resolution_clock::now();
        auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        csvBuildIn << sizeStr << "," << durationMs << "\n";
        std::cout << "File: " << filename << " sortBuildIn: " << durationMs << " ms\n";

        // -------- sortRadix ----------
        studentsCopy = students;
        start = std::chrono::high_resolution_clock::now();
        StudentBaseSort::sortRadix(studentsCopy);
        end = std::chrono::high_resolution_clock::now();
        durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        csvRadix << sizeStr << "," << durationMs << "\n";
        std::cout << "File: " << filename << " sortRadix: " << durationMs << " ms\n";
    }

    csvBuildIn.close();
    csvRadix.close();
}

int main() {
    const std::string CSV_FOLDER = "/home/bohdan/code/algorithms/homework-1/students-csv-files";
    const std::string OUTPUT_FOLDER = "/home/bohdan/code/algorithms/homework-1/benchmarks/benchmark-results/sorting";

    if (!std::filesystem::exists(OUTPUT_FOLDER)) {
        std::cout << "Output folder does not exist.\n";
        return 1;
    }

    const auto csvFiles = getCSVFiles(CSV_FOLDER);

    benchmarkSorting(csvFiles, OUTPUT_FOLDER);

    return 0;
}
