//processor h

#pragma once
#ifndef ORDER_PROCESSOR_H
#define ORDER_PROCESSOR_H

#include <vector>
#include <string>
#include "ExecutionReportCSVWriter.h"
#include "OrderBook.h"
#include <mutex>
#include <condition_variable>

class OrderProcessor {
private:
    // Add private variables
    ExecutionReportCSVWriter& writer;
    int nExecuted;

    OrderBook orderBook;
    //std::vector<std::string> rejectedOrderIDs; 

    // Add private functions
    void recordOrder(const std::vector<std::string>& order, int status, std::string quantity, double price);
    void updateOrder(std::vector<std::string>& order, int quantity);
    std::string getDateTime();
    void ProcessOrder(const std::vector<std::string>& ord, std::string& writerBuffer, std::mutex& writerMtx, std::condition_variable& cvWriter);
    void recordOrder(const std::vector<std::string>& order, int status, std::string quantity, double price, std::string& writerBuffer, std::mutex& writerMtx, std::condition_variable& cvWriter);


public:
    std::string Instrument;
    // add public functions and variables
    OrderProcessor(std::string Instrument, ExecutionReportCSVWriter& writer);
    ~OrderProcessor();

    void ProcessOrder(const std::vector<std::string>& order);

    void ProcessAllOrders(
        std::vector<std::vector<std::string>>& orderBuffer,
        std::string& writerBuffer,
        std::mutex& writerMtx,
        std::mutex& orderMtx,
        bool& doneOrder,
        int& doneWriting,
        std::condition_variable& cvWriter,
        std::condition_variable& cvInstrument);

};

#endif // ORDER_VALIDATOR_H