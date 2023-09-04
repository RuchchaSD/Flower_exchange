# Flower Exchange - C++ Trading System

## Overview

This repository is a part of the C++ Workshop Series conducted by LSEG (London Stock Exchange Group). It involves the implementation of a C++ program for a Flower Exchange system that supports basic trading operations. The system comprises two main components:

1. **Trader Application**: Traders can submit buy or sell orders for flowers via the Trader Application.

2. **Exchange Application**: This application processes incoming orders against existing orders in the order container, known as the Order Book. It can perform full or partial order execution.

Every submitted order receives an Execution Report from the Exchange Application, indicating the status of the order. Some orders may be rejected due to quantity limitations, invalid flower types, or other reasons.

## Project Structure

The project is structured as follows:

- **FlowerExchange**: The main file of the program.
- **ExecutionReportCSVWriter**: A utility class used to write Execution Reports to a CSV file.
- **OrderValidator**: This class contains six validation options for orders. An order will be rejected if it:
    - Does not contain a required field.
    - Is for an invalid instrument.
    - Contains an invalid side.
    - Has a price less than or equal to 0.
    - Has a quantity that is not a multiple of 10.
    - Has a quantity outside the range (minimum = 10, maximum = 1000).

- **OrderCSVReader**: Responsible for reading the Order CSV file and extracting orders line by line.
- **OrderBook**: This class includes functions like `isSellEmpty()`, `getSellMinVal()`, `getSellMinVec()`, `popSellMinVec()`, and `updateSellMinVec()`, along with corresponding functions for Buy orders. These functions are used for processing orders in the OrderProcessor.
- **OrderProcessor**: This function processes orders according to the specified functionality.
- **BuyMaxHeap** and **SellMinHeap**: These classes are used for managing buy and sell orders efficiently.

## Branches

- The non-concurrent approach can be found in the '2.nonconcurrent' branch of this repository
    - Average time taken for execution is 4.05783s
<p align="center">
  <img src="https://github.com/RuchchaSD/Flower_exchange/assets/129428203/46775df9-5851-4e43-9c5e-0d340882f826.png" width="400" height="150">
</p>

- The concurrent approach can be found in the 'master' branch of this repository.
    - Average time taken for execution is 0.506107s
<p align="center">
  <img src="https://github.com/RuchchaSD/Flower_exchange/assets/129428203/10c231d0-ae5c-4551-a526-296b95bc03f4.png" width="600" height="150">
</p>      

Feel free to explore and use the branch that best suits your needs.

## Usage

To use this Flower Exchange system:

1. Clone this repository to your local machine

2. Build and compile the project using your preferred C++ compiler.

3. Run the program to process orders and generate Execution Reports.


(Please note that there were some issues with connecting GitHub to Visual Studio, which led to separate coding efforts and required pushing from one GitHub account.)
