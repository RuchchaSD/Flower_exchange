#include "ExecutionReportCSVWriter.h"
#include <iostream>
#include <fstream>

//make a function to include time and date

std::string ExecutionReportCSVWriter::getDateTime()
{
    //auto now = std::chrono::system_clock::now();
    //std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    //std::tm time_info;
    //localtime_s(&time_info, &now_c); // Use localtime_s on Windows, or localtime on other systems

    //char buffer[80];
    //std::strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", &time_info);

    //return buffer;

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();

    std::time_t now_c = std::chrono::duration_cast<std::chrono::seconds>(epoch).count();

    std::tm time_info;
#ifdef _WIN32
    localtime_s(&time_info, &now_c); // Use localtime_s on Windows
#else
    localtime_r(&now_c, &time_info); // Use localtime_r on non-Windows systems
#endif

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", &time_info);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(epoch) % 1000;
    sprintf_s(buffer, "%s.%03lld", buffer, ms.count());

    return buffer;
}

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

    // Write the fields to the file and add a timestamp if the last field is empty
    for (size_t i = 0; i < fields.size()-1; ++i) {
        file << fields[i];
        if (i < fields.size() - 1) {
            file << ",";
        }
    }

    if (fields[fields.size() - 1] == "") {
		file << getDateTime();
	}
    else {
		file << fields[fields.size() - 1];
	}

    file << std::endl;

    // Assuming the Order ID is the first field in the vector
    if (!fields.empty()) {
        orderIDs.push_back(fields[0]);
    }
}

//make a function to change the filename
void ExecutionReportCSVWriter::changeFilename(const std::string& newFilename) {
    file.close();
    filename = newFilename;
    file.open(filename, std::ios_base::app);
}
//make a function to get the order IDs
const std::vector<std::string>& ExecutionReportCSVWriter::getOrderIDs() const {
    return orderIDs;
}
