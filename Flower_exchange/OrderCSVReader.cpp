#include "OrderCSVReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

OrderCSVReader::OrderCSVReader(const std::string& filename, int orderId) : filename(filename) {
    this->orderId = orderId;
    file.open(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;   // Handle error, e.g., throw an exception
    }
    // Skip the header line
    string header;
    getline(file, header);
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
            orderLine.push_back("ord" + to_string(++orderId));      // Add the order ID
            while (getline(ss, field, ',')) {
                orderLine.push_back(field);
            }
            return true;
        }
    }
    return false;
}

