#include "OrderCSVReader.h"
#include "ExecutionReportCSVWriter.h"
#include "OrderValidator.h"
#include "OrderBook.h"
#include "OrderProcessor.h"
#include "OrderDivider.h"
#include <iostream>
#include <vector>
#include <string>
//include libraries for measuring time
#include <ctime>
#include <chrono>



int main() {
    //add code to measure time at the start of the program
    auto start = std::chrono::system_clock::now();

    //read the Order CSV file
    OrderCSVReader reader("data/orders.csv");
    //write the Execution Report CSV file
    ExecutionReportCSVWriter writer("data/Execution_rep.csv");
    //create an OrderValidator object
    OrderValidator validator(writer);

    //create OrderProcessor objects for each instrument
    OrderProcessor roseOrderprocessor("Rose", writer);
    OrderProcessor lavenderOrderprocessor("Lavender", writer);
    OrderProcessor lotusOrderprocessor("Lotus", writer);
    OrderProcessor tulipOrderprocessor("Tulip", writer);
    OrderProcessor orchidOrderprocessor("Orchid", writer);

    int orderCount = 0;
    int rejectedOrderCount = 0;
    int roseOrderCount = 0;
    int lavenderOrderCount = 0;
    int lotusOrderCount = 0;
    int tulipOrderCount = 0;
    int orchidOrderCount = 0;
    //read orders one line at a time and pass it to the validator
    std::vector<std::string> orderLine;

    //read the first line of the CSV file
    while (reader.getNextOrderLine(orderLine)) {
        orderCount++;
        int status = validator.newValidator(orderLine);
        if (status == 0) {//order is rejected
            rejectedOrderCount++;
            continue;
        }
        else if (status == 1) {
            roseOrderCount++;
            roseOrderprocessor.ProcessOrder(orderLine);
        }
        else if (status == 2) {
            lavenderOrderCount++;
            lavenderOrderprocessor.ProcessOrder(orderLine);
        }
        else if (status == 3) {
            lotusOrderCount++;
            lotusOrderprocessor.ProcessOrder(orderLine);
        }
        else if (status == 4) {
            tulipOrderCount++;
            tulipOrderprocessor.ProcessOrder(orderLine);
        }
        else if (status == 5) {
            orchidOrderCount++;
            orchidOrderprocessor.ProcessOrder(orderLine);
        }
    }





    //add code to measure time at the end of the program
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    cout << "NonConcurrent Approach: \n";
    cout << "Total number of orders: " << orderCount << "\n";
    cout << "Total number of rejected orders: " << rejectedOrderCount << "\n";
    cout << "Total number of Rose orders: " << roseOrderCount << "\n";
    cout << "Total number of Lavender orders: " << lavenderOrderCount << "\n";
    cout << "Total number of Lotus orders: " << lotusOrderCount << "\n";
    cout << "Total number of Tulip orders: " << tulipOrderCount << "\n";
    cout << "Total number of Orchid orders: " << orchidOrderCount << "\n";
    std::cout << "Time taken to process "<<orderCount<<" orders: " << elapsed_seconds.count() << "s"<<endl;


    return 0;
}