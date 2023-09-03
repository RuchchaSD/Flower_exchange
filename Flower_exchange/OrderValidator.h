#pragma once
#ifndef ORDER_VALIDATOR_H
#define ORDER_VALIDATOR_H

#include "ExecutionReportCSVWriter.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <mutex>

class OrderValidator {
private:
    ExecutionReportCSVWriter& writer;
    std::vector<std::string> rejectedOrderIDs;
    //std::vector<std::string> rejectedOrders = {"er00"};
    
    void incrementrejectedOrders(std::string& orderID);
    void recordRejectedOrder(const std::vector<std::string>& order, const std::string& reason);
    std::vector<std::string> getRejectedReport(const std::vector<std::string>& order, const std::string& reason);
    std::string getDateTime();

public:
    OrderValidator(ExecutionReportCSVWriter& writer);
    ~OrderValidator();

    bool validateOrder(const std::vector<std::string>& order);
    int newValidator(const std::vector<std::string>& order);
    void getRejectedOrderIDs(std::vector<std::string>& orderIDs);
    void getRejectedOrders(std::vector<std::string>& orders);

    void validateAllorders(
        std::vector<std::vector<std::string>>& readerBuffer,
        std::vector<std::vector<std::string>>& writerBuffer,
        std::vector<std::vector<std::string>>& roseOrders,
        std::vector<std::vector<std::string>>& lavenderOrders,
        std::vector<std::vector<std::string>>& lotusOrders,
        std::vector<std::vector<std::string>>& tulipOrders,
        std::vector<std::vector<std::string>>& orchidOrders,
        std::mutex& readerMtx,
        std::mutex& writerMtx,
        std::mutex& roseMtx,
        std::mutex& lavenderMtx,
        std::mutex& lotusMtx,
        std::mutex& tulipMtx,
        std::mutex& orchidMtx,
        bool& doneReading,
        bool& doneRose,
        bool& doneLavender,
        bool& doneLotus,
        bool& doneTulip,
        bool& doneOrchid,
        int& doneWriting);

        int threadValidator(const std::vector<std::string>& order, std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx);
        std::string getRejectedOrderLine(const std::vector<std::string>& order, const std::string& reason);

};

#endif // ORDER_VALIDATOR_H
