#ifndef ORDER_CSV_READER_H
#define ORDER_CSV_READER_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class OrderCSVReader {
private:
    string filename;
    ifstream file;
    int orderId;

public:
    OrderCSVReader(const std::string& filename, int orderId = 0);
    ~OrderCSVReader();

    bool getNextOrderLine(std::vector<std::string>& orderLine);
    void changeFilename(const std::string& newFilename);
};

#endif // ORDER_CSV_READER_H
