
#include "OrderCSVReader.h"
#include "ExecutionReportCSVWriter.h"
#include "OrderValidator.h"
#include "OrderBook.h"
#include "OrderProcessor.h"
#include "OrderDivider.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>



int main() {
    //add code to measure time at the start of the program
    auto start = std::chrono::system_clock::now();

    OrderCSVReader reader("data/orders.csv"); // make order.csv file to orders.csv to run 100000 inputs
    ExecutionReportCSVWriter writer("data/Execution_rep.csv"); // ok
    OrderValidator validator(writer);// ok
    //OrderBook orderBook("rose");//ok
    OrderProcessor roseOrderprocessor("Rose", writer);//ok
    OrderProcessor lavenderOrderprocessor("Lavender", writer);//ok
    OrderProcessor lotusOrderprocessor("Lotus", writer);//ok
    OrderProcessor tulipOrderprocessor("Tulip", writer);//ok
    OrderProcessor orchidOrderprocessor("Orchid", writer);//ok
    //OrderDivider orderDivider(writer);//not implemented yet

    //instrument buffers
    std::vector<std::vector<std::string>> roseOrders;
    std::vector<std::vector<std::string>> lavenderOrders;
    std::vector<std::vector<std::string>> lotusOrders;
    std::vector<std::vector<std::string>> tulipOrders;
    std::vector<std::vector<std::string>> orchidOrders;

    //reader buffer
    std::vector<std::vector<std::string>> newOrders;
    //writer buffer
    std::vector<std::vector<std::string>> executionReports;

    std::mutex readerMtx;
    std::mutex roseMtx;
    std::mutex lavenderMtx;
    std::mutex lotusMtx;
    std::mutex tulipMtx;
    std::mutex orchidMtx;
    std::mutex writerMtx;

















    //read orders one line at a time and pass it to the validator
 //   std::vector<std::string> orderLine;
 //   while (reader.getNextOrderLine(orderLine)) {
 //       newOrders.push_back(orderLine);
 //       while(!newOrders.empty()) 
 //       {
 //           int status = validator.newValidator(newOrders.front());
 //           newOrders.erase(newOrders.begin());
 //           if (status == 0) {
 //               //std::cout << orderLine[1] <<": Order is rejected" << std::endl;
 //               continue;
 //           }
 //           else {
 //               if (status == 1) {
 //                   roseOrders.push_back(orderLine);
 //               }
 //               else if (status == 2) {
 //                   lavenderOrders.push_back(orderLine);
 //               }
 //               else if (status == 3) {
 //                   lotusOrders.push_back(orderLine);
 //               }
 //               else if (status == 4) {
 //                   tulipOrders.push_back(orderLine);
 //               }
 //               else if (status == 5) {
 //                   orchidOrders.push_back(orderLine);
 //               }

 //               if (!roseOrders.empty()) {
 //                   roseOrderprocessor.ProcessOrder(roseOrders.front());
 //                   roseOrders.erase(roseOrders.begin());
 //               }
 //               else if (!lavenderOrders.empty()) {
 //                   lavenderOrderprocessor.ProcessOrder(lavenderOrders.front());
 //                   lavenderOrders.erase(lavenderOrders.begin());
 //               }
 //               else if (!lotusOrders.empty()) {
 //                   lotusOrderprocessor.ProcessOrder(lotusOrders.front());
 //                   lotusOrders.erase(lotusOrders.begin());
 //               }
 //               else if (!tulipOrders.empty()) {
 //                   tulipOrderprocessor.ProcessOrder(tulipOrders.front());
 //                   tulipOrders.erase(tulipOrders.begin());
 //               }
 //               else if (!orchidOrders.empty()) {
 //                   orchidOrderprocessor.ProcessOrder(orchidOrders.front());
 //                   orchidOrders.erase(orchidOrders.begin());
 //               }
 //           }
 //       }
	//}
    //add code to measure time at the end of the program
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken to process all orders: " << elapsed_seconds.count() << "s\n";


    return 0;
}
