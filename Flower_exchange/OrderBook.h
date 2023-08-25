#pragma once
#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <vector>
#include <string>

class OrderBook {
private:
    // Add private variables
    std::string Instrument;
    //std::vector<std::string> rejectedOrderIDs; 

    // Add private functions
    void recordOrder(const std::vector<std::string>& order, int status, int quantity);
    void updateOrder(const std::vector<std::string>& order, int quantity);

public:
    // add public functions and variables
    OrderBook(std::string Instrument);
    ~OrderBook();

    void CommonFunction(const std::vector<std::string>& order);

    //SELL
    bool SellIsEmpty();
    double SellGetMinVal();
    std::vector<std::string> SellGetMinVec();
    void SellVecMinPop();
    void SellVecMinUpdate(const std::vector<std::string>& order);
    void SellWrite(const std::vector<std::string>& order);

    //BUY
    bool BuyIsEmpty();
    double BuyGetMinVal();
    std::vector<std::string> BuyGetMinVec();
    void BuyVecMinPop();
    void BuyVecMinUpdate(const std::vector<std::string>& order);
    void BuyWrite(const std::vector<std::string>& order);


};

#endif // ORDER_VALIDATOR_H
