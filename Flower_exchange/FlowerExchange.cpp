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


    //instrument buffers
    std::vector<std::vector<std::string>> roseOrders;
    std::vector<std::vector<std::string>> lavenderOrders;
    std::vector<std::vector<std::string>> lotusOrders;
    std::vector<std::vector<std::string>> tulipOrders;
    std::vector<std::vector<std::string>> orchidOrders;


    //reader buffer
    std::vector<std::vector<std::string>> newOrders;

    //read orders one line at a time and pass it to the validator
    std::vector<std::string> orderLine;

    //read the first line of the CSV file
    while (reader.getNextOrderLine(orderLine)) {
        newOrders.push_back(orderLine);

        while (!newOrders.empty())
        {
            //validate the order
            int status = validator.newValidator(newOrders.front());
            newOrders.erase(newOrders.begin());

            if (status == 0) {//order is rejected
                //std::cout << orderLine[1] << ": Order is rejected" << std::endl;
                continue;
            }
            else {
                //order is accepted
                if (status == 1) {
                    roseOrders.push_back(orderLine);
                }
                else if (status == 2) {
                    lavenderOrders.push_back(orderLine);
                }
                else if (status == 3) {
                    lotusOrders.push_back(orderLine);
                }
                else if (status == 4) {
                    tulipOrders.push_back(orderLine);
                }
                else if (status == 5) {
                    orchidOrders.push_back(orderLine);
                }

                //process the orders
                while (!roseOrders.empty()) {
                    roseOrderprocessor.ProcessOrder(roseOrders.front());
                    roseOrders.erase(roseOrders.begin());
                }
                while (!lavenderOrders.empty()) {
                    lavenderOrderprocessor.ProcessOrder(lavenderOrders.front());
                    lavenderOrders.erase(lavenderOrders.begin());
                }
                while (!lotusOrders.empty()) {
                    lotusOrderprocessor.ProcessOrder(lotusOrders.front());
                    lotusOrders.erase(lotusOrders.begin());
                }
                while (!tulipOrders.empty()) {
                    tulipOrderprocessor.ProcessOrder(tulipOrders.front());
                    tulipOrders.erase(tulipOrders.begin());
                }
                while (!orchidOrders.empty()) {
                    orchidOrderprocessor.ProcessOrder(orchidOrders.front());
                    orchidOrders.erase(orchidOrders.begin());
                }
            }
        }
    }

    //add code to measure time at the end of the program
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken to process all orders: " << elapsed_seconds.count() << "s\n";


    return 0;
}