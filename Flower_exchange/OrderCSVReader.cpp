//reader
#include "OrderCSVReader.h"

using namespace std;

OrderCSVReader::OrderCSVReader(const std::string& filename, int orderId) : filename(filename) {
    this->orderId = orderId;
    file.open(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        // Handle error, e.g., throw an exception
    }
    // Skip the header line
    string header;
    getline(file, header);
    //cout << "header: " << header << endl;
}

OrderCSVReader::~OrderCSVReader() {
    if (file.is_open()) {
        file.close();
    }
}

bool OrderCSVReader::getNextOrderLine(std::vector<std::string>& orderLine) {
    if (!file.eof()) {
        string line;
        if (getline(file, line)) {

            stringstream ss(line);
            string field;
            orderLine.clear();
            orderLine.push_back("ord" + to_string(++orderId));
            while (getline(ss, field, ',')) {
                orderLine.push_back(field);
            }
            return true;
        }
    }
    return false;
}

void OrderCSVReader::changeFilename(const std::string& newFilename) {
    file.close();
    filename = newFilename;
    file.open(filename);
}

void OrderCSVReader::getAllOrders(std::vector<std::vector<std::string>>& orders, std::mutex& readerMtx, bool& doneReading, std::condition_variable& cvReader) {
    std::vector<std::string> orderLine;
    while (getNextOrderLine(orderLine)) {
        {

            std::unique_lock<std::mutex> lock(readerMtx);
            orders.push_back(orderLine);
            cvReader.notify_one();
        }
    }
    {
        std::lock_guard<std::mutex> lock(readerMtx);
        doneReading = true;
        cvReader.notify_one();
        //cout << "Reader           || Finished reading orders" << endl;
    }
}