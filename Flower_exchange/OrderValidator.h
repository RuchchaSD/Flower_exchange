#pragma once
#ifndef ORDER_VALIDATOR_H
#define ORDER_VALIDATOR_H

#include <vector>
#include <string>
#include "ExecutionReportCSVWriter.h"

class OrderValidator {
private:
    ExecutionReportCSVWriter& writer;
    std::vector<std::string> rejectedOrderIDs;
    std::vector<std::string> rejectedOrders = {"er00"};
    
    void incrementrejectedOrders(std::string& orderID);
    void recordRejectedOrder(const std::vector<std::string>& order, const std::string& reason);

public:
    OrderValidator(ExecutionReportCSVWriter& writer);
    ~OrderValidator();

    bool validateOrder(const std::vector<std::string>& order);
    void getRejectedOrderIDs(std::vector<std::string>& orderIDs);
    void getRejectedOrders(std::vector<std::string>& orders);
};

#endif // ORDER_VALIDATOR_H
