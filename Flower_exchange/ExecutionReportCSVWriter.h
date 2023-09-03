#pragma once
#ifndef EXECUTION_REPORT_CSV_WRITER_H
#define EXECUTION_REPORT_CSV_WRITER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include <mutex>

class ExecutionReportCSVWriter {
private:
    std::string filename;
    std::ofstream file;
    std::vector<std::string> orderIDs;

    std::string getDateTime();

public:
    ExecutionReportCSVWriter(const std::string& filename);
    ~ExecutionReportCSVWriter();

    void writeExecutionRecord(const std::vector<std::string>& fields);
    void changeFilename(const std::string& newFilename);
    const std::vector<std::string>& getOrderIDs() const;

    void writeAllRecords( std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx, int& doneWriting);
    void writeExecutionRecord(std::string record);
};

#endif // EXECUTION_REPORT_CSV_WRITER_H
