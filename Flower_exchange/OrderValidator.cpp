#include "OrderValidator.h"
#include <iostream>
//include libraries to get the current date and time
#include <ctime>
#include <chrono>

OrderValidator::OrderValidator(ExecutionReportCSVWriter& writer) : writer(writer) {
    // ...
}

OrderValidator::~OrderValidator() {
    // ...
}

bool OrderValidator::validateOrder(const std::vector<std::string>& order) {
    std::string reason = "";
    
    // check for required fields
    if (order.size() != 5) {
        reason = "Invalid number of fields";
    }else if (order[1] != "Rose" && order[1] != "Lavender" && order[1] != "Lotus" && order[1] != "Tulip" && order[1] != "Orchid") {// check for invalid instrument
        reason = "Invalid instrument";
    }else if (order[2] != "1" && order[2] != "2") {// check for invalid side
        reason = "Invalid side";
    }else if (stod(order[3]) <= 0) {// check for price greater than 0
        reason = "Price must be greater than 0";
    }else if (stoi(order[4]) % 10 != 0) {// check for quantity multiple of 10
        reason = "Quantity must be a multiple of 10";
    }else if (stoi(order[4]) < 10 || stoi(order[4]) > 1000) {// check for quantity in range
        reason = "Quantity must be in the range 10 to 1000";
    }else {
        return true;
    }
	recordRejectedOrder(order, reason);
	return false;
	
}

int OrderValidator::newValidator(const std::vector<std::string>& order) {
    std::string reason = "";
    // check for required fields
    if (order.size() != 5) {
        reason = "Invalid number of fields";
    }else if (order[2] != "1" && order[2] != "2") {// check for invalid side
    		reason = "Invalid side";
    	}
	else if (stod(order[3]) <= 0) {// check for price greater than 0
    		reason = "Price must be greater than 0";
    	}
	else if (stoi(order[4]) % 10 != 0) {// check for quantity multiple of 10
    		reason = "Quantity must be a multiple of 10";
    	}
	else if (stoi(order[4]) < 10 || stoi(order[4]) > 1000) {// check for quantity in range
    		reason = "Quantity must be in the range 10 to 1000";
    	}
    else {
        if (order[1] == "Rose") {
			return 1;
		}
        else if (order[1] == "Lavender") {
			return 2;
		}
        else if (order[1] == "Lotus") {
            return 3;
		}
        else if (order[1] == "Tulip") {
            return 4;
		}
        else if (order[1] == "Orchid") {
            return 5;
		}
        else {
		    reason = "Invalid instrument";
		}
	}
    recordRejectedOrder(order, reason);
    return 0;
}

void OrderValidator::recordRejectedOrder(const std::vector<std::string>& order, const std::string& reason) {
    // create a string conatining the current date and time in YYYYMMDD-HHMMSS.sss format
    //std::string currentDateTime = "20230820-132823.154";
    std::string OrderID;
    std::vector<std::string> rejectedOrder;
    incrementrejectedOrders(OrderID);
    if (order.size() == 5) {
        rejectedOrder = { order[0],OrderID,order[1],order[2],order[3],order[4],"1",reason,"" };
    }
    else{
        if (order.size() < 5){
            rejectedOrder.push_back(order[0]);
            rejectedOrder.push_back(OrderID);
            for (int i = 1; i < order.size(); i++ ) {
				rejectedOrder.push_back(order[i]);
			}
            for (int i = 0; i < 5 - order.size(); i++) {
                rejectedOrder.push_back("");
            }
            rejectedOrder.push_back("1");
            rejectedOrder.push_back(reason);
            rejectedOrder.push_back("");
        }else{
            rejectedOrder.push_back(order[0]);
            rejectedOrder.push_back(OrderID);
            for (int i = 1; i < 4; i++) {
                rejectedOrder.push_back(order[i]);
            }
            std::string txt = "";
            for (int i = 4; i < order.size(); i++) {
                txt += order[i] + " ";
            }
            rejectedOrder.push_back(txt);
            rejectedOrder.push_back("1");
            rejectedOrder.push_back(reason);
            rejectedOrder.push_back("");
        }


        
    }
    
    writer.writeExecutionRecord(rejectedOrder); // Record the rejected order
    rejectedOrders.push_back(OrderID);
    rejectedOrderIDs.push_back(order[0]); // Assuming order[0] is the Client Order ID
}

void OrderValidator::getRejectedOrderIDs(std::vector<std::string>& orderIDs) {
    orderIDs = rejectedOrderIDs;
}

void OrderValidator::getRejectedOrders(std::vector<std::string>& orders) {
	orders = rejectedOrders;
}

void OrderValidator::incrementrejectedOrders(std::string& orderID) {
	int num = std::stoi(rejectedOrders.back().substr(2));
    num++;
    orderID = "er" + std::to_string(num);
}
