#include "ExecutionReportCSVWriter.h"
#include <iostream>
#include <fstream>

ExecutionReportCSVWriter::ExecutionReportCSVWriter(const std::string& filename) : filename(filename) {
    file.open(filename, std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        // Handle error, e.g., throw an exception
    }
}

ExecutionReportCSVWriter::~ExecutionReportCSVWriter() {
    if (file.is_open()) {
        file.close();
    }
}

void ExecutionReportCSVWriter::writeExecutionRecord(const std::vector<std::string>& fields) {
    if (!file.is_open()) {
        std::cerr << "File is not open for writing: " << filename << std::endl;
        return;
    }

    // Write the fields to the file
    for (size_t i = 0; i < fields.size(); ++i) {
        file << fields[i];
        if (i < fields.size() - 1) {
            file << ",";
        }
    }
    file << std::endl;

    // Assuming the Order ID is the first field in the vector
    if (!fields.empty()) {
        orderIDs.push_back(fields[0]);
    }
}

void ExecutionReportCSVWriter::changeFilename(const std::string& newFilename) {
    file.close();
    filename = newFilename;
    file.open(filename, std::ios_base::app);
}

const std::vector<std::string>& ExecutionReportCSVWriter::getOrderIDs() const {
    return orderIDs;
}
