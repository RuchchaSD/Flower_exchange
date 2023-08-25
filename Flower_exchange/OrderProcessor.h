#pragma once
#ifndef ORDER_PROCESSOR_H
#define ORDER_PROCESSOR_H

#include <vector>
#include <string>
#include "ExecutionReportCSVWriter.h"

class OrderProcessor {
private:
    // Add private variables
    ExecutionReportCSVWriter& writer;
    std::string Instrument;
    //std::vector<std::string> rejectedOrderIDs; 

    // Add private functions
    void recordOrder(const std::vector<std::string>& order, int status, int quantity);
    void updateOrder(const std::vector<std::string>& order, int quantity);

public:
    // add public functions and variables
    OrderProcessor(std::string Instrument, ExecutionReportCSVWriter& writer);
    ~OrderProcessor();

    void ProcessOrder(const std::vector<std::string>& order);
};

#endif // ORDER_VALIDATOR_H
