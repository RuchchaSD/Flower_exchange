#pragma once
#ifndef ORDER_PROCESSOR_H
#define ORDER_PROCESSOR_H

#include <vector>
#include <string>
#include "ExecutionReportCSVWriter.h"
#include "OrderBook.h"
#include <mutex>

class OrderProcessor {
private:
    // Add private variables
    ExecutionReportCSVWriter& writer;
    std::string Instrument;
    OrderBook orderBook;
    //std::vector<std::string> rejectedOrderIDs; 

    // Add private functions
    void recordOrder(const std::vector<std::string>& order, int status, std::string quantity, double price);
    void updateOrder(std::vector<std::string>& order, int quantity);
    std::string getDateTime();
    void ProcessOrder(const std::vector<std::string>& ord, std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx);
    void recordOrder(const std::vector<std::string>& order, int status, std::string quantity, double price, std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx);


public:
    // add public functions and variables
    OrderProcessor(std::string Instrument, ExecutionReportCSVWriter& writer);
    ~OrderProcessor();

    void ProcessOrder(const std::vector<std::string>& order);

    void ProcessAllOrders(
        std::vector<std::vector<std::string>>& orderBuffer,
        std::vector<std::vector<std::string>>& writerBuffer,
        std::mutex& writerMtx,
        std::mutex& orderMtx,
        bool& doneOrder,
        int& doneWriting);

};

#endif // ORDER_VALIDATOR_H