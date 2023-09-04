//Writer
#include "ExecutionReportCSVWriter.h"

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
    // expected order of the vector is:ordId, cliId, side,price,qty,status,Reason,"" or timestamp
    if (!file.is_open()) {
        std::cerr << "File is not open for writing: " << filename << std::endl;
        return;
    }
    //std::string  line = fields[0] + "," + fields[1] + "," + fields[2] + "," + fields[3] + "," + fields[4] + "," + fields[5] + "," + fields[6] + "," + fields[7] + "," + getDateTime();
    // Write the fields to the file
    for (size_t i = 0; i < fields.size(); ++i) {
        file << fields[i];
        if (i < fields.size() - 1) {
            file << ",";
        }
    }
    //file << line;
    file << "\n";
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

void ExecutionReportCSVWriter::writeAllRecords(std::string& writerBuffer, std::mutex& writerMtx, int& doneWriting, std::condition_variable& cvWriter)
{
    /* int countOut = 0;
     int count = 0;*/
    int orderCount = 0;
    bool finishedWriting = false;
    std::vector<std::string> order;
    while (true) {
        {

            std::unique_lock<std::mutex> lock(writerMtx);
            finishedWriting = doneWriting > 5;
            //std::cout << "orderCount:" << orderCount << " Buffer size: " << writerBuffer.size() << "  Writers Finished : " << doneWriting << std::endl;
            cvWriter.wait(lock, [&] {return (writerBuffer.size() > 16000) || finishedWriting; });

            if ((finishedWriting) && writerBuffer.empty()) {
                break;
            }
            std::string lines = std::move(writerBuffer);
            lock.unlock();
            orderCount++;
            writeExecutionRecord(lines);
        }
    }
    //std::cout << "Writer            || Finished writing" << std::endl;
}

void ExecutionReportCSVWriter::writeExecutionRecord(std::string record)
{
    if (!file.is_open()) {
        std::cerr << "File is not open for writing: " << filename << std::endl;
        return;
    }
    //check whether the last character is a new line
    if (record.back() != '\n') {
        record += '\n';
    }
    file << record;
}
