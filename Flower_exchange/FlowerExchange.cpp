
#include "OrderCSVReader.h"
#include "ExecutionReportCSVWriter.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    OrderCSVReader reader("data/order.csv");
    ExecutionReportCSVWriter writer("data/Execution_rep.csv");



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
    std::vector<std::string> fields1 = { "aaa21","ord1", "Rose", "2", "55.00", "100", "0", "_", "20230820-132823.154" };
    std::vector<std::string> fields2 = { "aaa12","ord2", "Rose", "2", "45.00", "100", "0", "_", "20230820-135325.164" };

    writer.writeExecutionRecord(fields1);
    writer.writeExecutionRecord(fields2);

    // print the order IDs
    const std::vector<std::string>& orderIDs = writer.getOrderIDs();
    for (const auto& id : orderIDs) {
		std::cout << id << std::endl;
	}

    

    return 0;
}
