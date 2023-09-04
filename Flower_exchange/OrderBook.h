//book
#pragma once
#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <vector>
#include <string>
#include <iostream>
#include "BuyMaxHeap.h" //remove
#include "SellMinHeap.h" //remove
#include <queue>
#include <vector>

struct CompareSell {
    bool operator()(const std::vector<std::string>& a, const std::vector<std::string>& b) {
        double priceA = std::stod(a[4]);
        double priceB = std::stod(b[4]);

        if (priceA == priceB) {
            // Consider time priority logic
            // For example: Compare based on the Client Order ID or other timestamp


            return std::stoi(a[0].substr(3)) > std::stoi(b[0].substr(3)); // Lower Client Order ID has higher priority
        }

        return priceA > priceB; // Smaller price has higher priority
    }
};

struct CompareBuy {
    bool operator()(const std::vector<std::string>& a, const std::vector<std::string>& b) {
        double priceA = std::stod(a[4]);
        double priceB = std::stod(b[4]);

        if (priceA == priceB) {
            // Consider time priority logic
            // For example: Compare based on the Client Order ID or other timestamp
            return std::stoi(a[0].substr(3)) > std::stoi(b[0].substr(3)); // Lower Client Order ID has higher priority
        }

        return priceA < priceB; // Larger price has higher priority
    }
};





class OrderBook {
private:
    // Add private variables
    std::string Instrument;
    std::priority_queue<std::vector<std::string>, std::vector<std::vector<std::string>>, CompareBuy> buyHeap;
    std::priority_queue<std::vector<std::string>, std::vector<std::vector<std::string>>, CompareSell> sellHeap;

    //std::vector<std::string> rejectedOrderIDs; 

    // Add private functions

public:
    // add public functions and variables
    OrderBook(std::string Instrument);
    ~OrderBook();


    //SELL
    bool isSellEmpty();
    double getSellMinVal();
    std::vector<std::string> getSellMinVec();
    void popSellMinVec();
    void updateSellMinVec(const std::vector<std::string>& order);
    void writeSell(const std::vector<std::string>& order);

    //BUY
    bool isBuyEmpty();
    double getBuyMaxVal();
    std::vector<std::string> getBuyMaxVec();
    void popBuyMaxVec();
    void updateBuyMaxVec(const std::vector<std::string>& order);
    void writeBuy(const std::vector<std::string>& order);

    std::string getInstrument();
};

#endif // ORDER_VALIDATOR_H
