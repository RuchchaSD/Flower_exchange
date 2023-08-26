
#include "OrderCSVReader.h"
#include "ExecutionReportCSVWriter.h"
#include "OrderValidator.h"
#include "OrderBook.h"
#include "OrderProcessor.h"
//#include "OrderDivider.h"
#include <iostream>
#include <vector>
#include <string>


int main() {
    //OrderCSVReader reader("data/order.csv"); // ok
    ExecutionReportCSVWriter writer("data/Execution_rep.csv"); // ok
    //OrderValidator validator(writer);// ok
    //OrderBook orderBook("rose");//ok
    //OrderProcessor processor("rose", writer);//ok
    

    //OrderDivider orderDivider(writer);




















    //Give Valid orders to order processor and check if it is working
    //implement a vector that have orders and pass it to the order processor
    //std::vector<std::vector<std::string>> testfields = {
				//						{ "ord1","aaa1", "Rose", "1", "50.00", "100" },
				//						{ "ord2","aaa2", "Rose", "1", "40.00", "100" },
				//						{ "ord3","aaa3", "Rose", "1", "30.00", "100" },
				//						{ "ord4","aaa4", "Rose", "2", "30.00", "150" },
				//						{ "ord5","aaa5", "Rose", "2", "35.00", "50" } };
    //for (auto field : testfields) {
    //    processor.ProcessOrder(field);
    //}
    ////pass some valid sell and buy orders to the order book to check it's functionality
    //std::vector<std::string> fields1 = { "aaa1", "Rose", "2", "55.00", "100" };
    //std::vector<std::vector<std::string>> testfields = { 
    //                                    { "ord3","aaa3", "Rose", "2", "50.00", "100" },
    //                                    { "ord1","aaa1", "Rose", "2", "10.00", "100" },
    //                                    { "ord2","aaa2", "Rose", "2", "40.00", "100" },
    //                                    { "ord4","aaa4", "Rose", "2", "90.00", "100" },
    //                                    { "ord0","aaa4", "Rose", "2", "90.00", "100" } };
    //
    //for (auto field : testfields) {
    //    orderBook.writeSell(field);
    //    orderBook.writeBuy(field);
    //}
 //   orderBook.updateBuyMaxVec({ "aaa4", "Rose", "2", "50.00", "10" });
 //   while(orderBook.isSellEmpty() == false)
	//{
	//	std::cout << orderBook.getSellMinVec()[0] << std::endl;
	//	orderBook.popSellMinVec();
	//}
  //  orderBook.updateSellMinVec({ "ord1", "aaa1", "Rose", "2", "10.00", "10" });
  //  while (orderBook.isSellEmpty() == false)
  //  {
  //      
  //      std::cout << orderBook.getSellMinVal() << std::endl;
		//orderBook.popSellMinVec();
	//}
    //while (orderBook.isBuyEmpty() == false)
    //{
    //    //       orderBook.updateBuyMaxVec({ "aaa4", "Rose", "2", "50.00", "10" });
    //    std::cout << orderBook.getBuyMaxVec()[0] << std::endl;
    //    orderBook.popBuyMaxVec();
    //}
     //Read the Order CSV file one line at a time and store the fields in a vector
    //std::vector<std::string> orderLine;
    //while (reader.getNextOrderLine(orderLine)) {
    //    for (const auto& field : orderLine) {
    //        std::cout << field << " ";
    //    }
    //    std::cout << std::endl;
    //    // pass the order line to a function that processes the order
    //}
    //Write lines to the Execution Report CSV file
    //std::vector<std::string> fields1 = { "ord1", "aaa21", "Rose", "2", "100", "55.00", "0", "_", ""};
    //std::vector<std::string> fields2 = { "ord2", "aaa12", "Rose", "2", "100", "45.00", "0", "_", ""};
    //std::vector<std::string> fields3 = { "ord3", "aaa13", "Rose", "2", "100", "45.00", "0", "_", "" };
    //writer.writeExecutionRecord(fields1);
    //writer.writeExecutionRecord(fields2);
   //   // print the order IDs
 //   const std::vector<std::string>& orderIDs = writer.getOrderIDs();
 //   for (const auto& id : orderIDs) {
	//	std::cout << id << std::endl;
	//}
   //pass some order vectors to OrderValidator to check it's functionality
 //   std::vector<std::vector<std::string>> testfields = { { "ord20","aaa1", "Rose", "2", "55.00", "100"},
 //                                           { "ord21","aaa2", "Lotus", "2", "45.00", "100" },
       //wrong ones
 //                                           { "ord22","aaa3", "Rose", "2", "55.00", "100","23" },
 //                                           { "ord23","aaa4", "Rose", "2", "45.00" },
 //                                           { "ord24","aaa5", "Roses", "2", "55.00", "100" },
 //                                           { "ord25","aaa6", "Rose", "22", "45.00", "100" },
 //                                           { "ord26","aaa7", "Rose", "2", "-55.00", "100" },
 //                                           { "ord27","aaa8", "Rose", "2", "45.00", "103" },
 //                                           { "ord28","aaa9", "Rose", "2", "45.00", "1020" } };
 ////   cout << "Order ID : Validity" << endl;
 //   for (auto field : testfields)
 //   {
	//	cout<< field[0]<< " : "  << to_string(validator.newValidator(field)) << endl;
 //       //cout << field[0] << " : " << field[1] << endl;
	//}
    //cout << testfields[0][0] << " : " << validator.validateOrder(testfields[3]) << endl;

    return 0;
}
