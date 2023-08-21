#include "OrderCSVReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

OrderCSVReader::OrderCSVReader(const std::string& filename) : filename(filename) {
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
