
#include "OrderCSVReader.h"
#include "ExecutionReportCSVWriter.h"
#include "OrderValidator.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    OrderCSVReader reader("data/order.csv");
    ExecutionReportCSVWriter writer("data/Execution_rep.csv");
    OrderValidator validator(writer);



    // Read the Order CSV file one line at a time and store the fields in a vector
    //std::vector<std::string> orderLine;
    //while (reader.getNextOrderLine(orderLine)) {
    //    for (const auto& field : orderLine) {
    //        std::cout << field << " ";
    //    }
    //    std::cout << std::endl;
    //    // pass the order line to a function that processes the order
    //}


    //Write lines to the Execution Report CSV file
    //std::vector<std::string> fields1 = { "aaa21","ord1", "Rose", "2", "55.00", "100", "0", "_", "" };
    //std::vector<std::string> fields2 = { "aaa12","ord2", "Rose", "2", "45.00", "100", "0", "_", ""};
    //writer.writeExecutionRecord(fields1);
    //writer.writeExecutionRecord(fields2);



   //   // print the order IDs
 //   const std::vector<std::string>& orderIDs = writer.getOrderIDs();
 //   for (const auto& id : orderIDs) {
	//	std::cout << id << std::endl;
	//}

   //pass some order vectors to OrderValidator to check it's functionality
 //   std::vector<std::vector<std::string>> testfields = { { "aaa1", "Rose", "2", "55.00", "100" },
 //                                           { "aaa2", "Rose", "2", "45.00", "100" },

 //       //wrong ones
 //                                           { "aaa3", "Rose", "2", "55.00", "100","23" },
 //                                           { "aaa4", "Rose", "2", "45.00" },
 //                                           { "aaa5", "Roses", "2", "55.00", "100" },
 //                                           { "aaa6", "Rose", "22", "45.00", "100" },
 //                                           { "aaa7", "Rose", "2", "-55.00", "100" },
 //                                           { "aaa8", "Rose", "2", "45.00", "103" },
 //                                           { "aaa9", "Rose", "2", "45.00", "1020" } };
 //   cout << "Order ID : Validity" << endl;
 //   for (auto field : testfields)
 //   {
	//	cout<< field[0]<< " : "  << bool(validator.validateOrder(field)) << endl;
 //       //cout << field[0] << " : " << field[1] << endl;
	//}
    //cout << testfields[0][0] << " : " << validator.validateOrder(testfields[3]) << endl;

    return 0;
}
