
#include "OrderCSVReader.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    OrderCSVReader reader("data/order.csv");

    std::vector<std::string> orderLine;
    while (reader.getNextOrderLine(orderLine)) {
        for (const auto& field : orderLine) {
            std::cout << field << " ";
        }
        std::cout << std::endl;
    }

    //reader.changeFilename("new_orders.csv"); // change the filename if needed

    return 0;
}
