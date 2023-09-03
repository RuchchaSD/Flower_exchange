#include "OrderValidator.h"


OrderValidator::OrderValidator(ExecutionReportCSVWriter& writer) : writer(writer) {
    // ...
}

OrderValidator::~OrderValidator() {
    // ...
}

bool OrderValidator::validateOrder(const std::vector<std::string>& order) {
    std::string reason = "";
    
    // check for required fields
    if (order.size() != 6) {
        reason = "Invalid number of fields";
    }else if (order[2] != "Rose" && order[2] != "Lavender" && order[2] != "Lotus" && order[2] != "Tulip" && order[2] != "Orchid") {// check for invalid instrument
        reason = "Invalid instrument";
    }else if (order[3] != "1" && order[3] != "2") {// check for invalid side
        reason = "Invalid side";
    }else if (stod(order[4]) <= 0) {// check for price greater than 0
        reason = "Price must be greater than 0";
    }else if (stoi(order[5]) % 10 != 0) {// check for quantity multiple of 10
        reason = "Quantity must be a multiple of 10";
    }else if (stoi(order[5]) < 10 || stoi(order[5]) > 1000) {// check for quantity in range
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
    if (order.size() != 6) {
        reason = "Invalid number of fields";
    }else if (order[3] != "1" && order[3] != "2") {// check for invalid side
    		reason = "Invalid side";
    	}
	else if (stod(order[4]) <= 0) {// check for price greater than 0
    		reason = "Price must be greater than 0";
    	}
	else if (stoi(order[5]) % 10 != 0) {// check for quantity multiple of 10
    		reason = "Quantity must be a multiple of 10";
    	}
	else if (stoi(order[5]) < 10 || stoi(order[5]) > 1000) {// check for quantity in range
    		reason = "Quantity must be in the range 10 to 1000";
    	}
    else {
        if (order[2] == "Rose") {
			return 1;
		}
        else if (order[2] == "Lavender") {
			return 2;
		}
        else if (order[2] == "Lotus") {
            return 3;
		}
        else if (order[2] == "Tulip") {
            return 4;
		}
        else if (order[2] == "Orchid") {
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
    //std::string OrderID;
    std::vector<std::string> rejectedOrder;
    //incrementrejectedOrders(OrderID);
    if (order.size() == 6) {
        rejectedOrder = { order[0],order[1],order[2],order[3],order[4],order[5],"1",reason,getDateTime()};
    }
    else{
        if (order.size() < 6){
            for (int i = 0; i < order.size(); i++ ) {
				rejectedOrder.push_back(order[i]);
			}
            for (int i = 0; i < 6 - order.size(); i++) {
                rejectedOrder.push_back("");
            }
            rejectedOrder.push_back("1");
            rejectedOrder.push_back(reason);
            rejectedOrder.push_back(getDateTime());
        }else{
            for (int i = 0; i < 5; i++) {
                rejectedOrder.push_back(order[i]);
            }
            std::string txt = "";
            for (int i = 5; i < order.size(); i++) {
                txt += order[i] + " ";
            }
            rejectedOrder.push_back(txt);
            rejectedOrder.push_back("1");
            rejectedOrder.push_back(reason);
            rejectedOrder.push_back(getDateTime());
        }


        
    }
    
    writer.writeExecutionRecord(rejectedOrder); // Record the rejected order
    /*rejectedOrders.push_back(order[0]);*/
    rejectedOrderIDs.push_back(order[0]); // Assuming order[0] is the Client Order ID
}

std::vector<std::string> OrderValidator::getRejectedReport(const std::vector<std::string>& order, const std::string& reason)
{
    std::vector<std::string> rejectedOrder;
    if (order.size() == 6) {
        rejectedOrder = { order[0],order[1],order[2],order[3],order[4],order[5],"1",reason,getDateTime() };
    }
    else {
        if (order.size() < 6) {
            for (int i = 0; i < order.size(); i++) {
                rejectedOrder.push_back(order[i]);
            }
            for (int i = 0; i < 6 - order.size(); i++) {
                rejectedOrder.push_back("");
            }
            rejectedOrder.push_back("1");
            rejectedOrder.push_back(reason);
            rejectedOrder.push_back(getDateTime());
        }
        else {
            for (int i = 0; i < 5; i++) {
                rejectedOrder.push_back(order[i]);
            }
            std::string txt = "";
            for (int i = 5; i < order.size(); i++) {
                txt += order[i] + " ";
            }
            rejectedOrder.push_back(txt);
            rejectedOrder.push_back("1");
            rejectedOrder.push_back(reason);
            rejectedOrder.push_back(getDateTime());
        }



    }
    return rejectedOrder;
}



void OrderValidator::getRejectedOrderIDs(std::vector<std::string>& orderIDs) {
    orderIDs = rejectedOrderIDs;
}

void OrderValidator::validateAllorders(
    std::vector<std::vector<std::string>>& readerBuffer,
    std::vector<std::vector<std::string>>& writerBuffer,
    std::vector<std::vector<std::string>>& roseOrders,
    std::vector<std::vector<std::string>>& lavenderOrders,
    std::vector<std::vector<std::string>>& lotusOrders,
    std::vector<std::vector<std::string>>& tulipOrders,
    std::vector<std::vector<std::string>>& orchidOrders,
    std::mutex& readerMtx, std::mutex& writerMtx,
    std::mutex& roseMtx, std::mutex& lavenderMtx,
    std::mutex& lotusMtx, std::mutex& tulipMtx,
    std::mutex& orchidMtx, bool& doneReading,
    bool& doneRose, bool& doneLavender, bool& doneLotus, bool& doneTulip, bool& doneOrchid, int& doneWriting)
{
    int countOut = 0;
    int count = 0;
    bool flag = false;
    std::vector<std::string> order;
    bool emt = false;
    //std::this_thread::sleep_for(std::chrono::milliseconds(2));
    while (true) {   
        {
            emt = readerBuffer.size() > 20;
            countOut++;
            
            if (emt) {
                std::unique_lock<std::mutex> lock(readerMtx);
                count++;
                flag = true;
                order = readerBuffer.front();
                readerBuffer.erase(readerBuffer.begin());
                
            }
            else if (doneReading) {
                
                if (readerBuffer.empty()) {
                    std::cout << "CountOut : " << countOut << " Count : " << count << std::endl;
                    break;
                }else {
					/*std::unique_lock<std::mutex> lock(readerMtx);*/
					count++;
					flag = true;
					order = readerBuffer[0];
					readerBuffer.erase(readerBuffer.begin());
				}
            }
        }
        if (flag) {
            flag = false;
            int status = threadValidator(order, writerBuffer, writerMtx);
            if (status == 1) {
                std::lock_guard<std::mutex> lock(roseMtx);
                roseOrders.push_back(order);
            }
            else if (status == 2) {
                std::lock_guard<std::mutex> lock(lavenderMtx);
                lavenderOrders.push_back(order);
            }
            else if (status == 3) {
                std::lock_guard<std::mutex> lock(lotusMtx);
                lotusOrders.push_back(order);
            }
            else if (status == 4) {
                std::lock_guard<std::mutex> lock(tulipMtx);
                tulipOrders.push_back(order);
            }
            else if (status == 5) {
                std::lock_guard<std::mutex> lock(orchidMtx);
                orchidOrders.push_back(order);
            }
        }
    }
    {
        std::unique_lock<std::mutex>
            lock1(roseMtx),
            lock2(lavenderMtx),
            lock3(lotusMtx),
            lock4(tulipMtx),
            lock5(orchidMtx),
            lock6(writerMtx);
        doneRose = doneLavender = doneLotus = doneTulip = doneOrchid = true;
        doneWriting++;
    }
}

int OrderValidator::threadValidator(const std::vector<std::string>& order, std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx)
{
    std::string reason = "";
    // check for required fields
    if (order.size() != 6) {
        reason = "Invalid number of fields";
    }
    else if (order[3] != "1" && order[3] != "2") {// check for invalid side
        reason = "Invalid side";
    }
    else if (stod(order[4]) <= 0) {// check for price greater than 0
        reason = "Price must be greater than 0";
    }
    else if (stoi(order[5]) % 10 != 0) {// check for quantity multiple of 10
        reason = "Quantity must be a multiple of 10";
    }
    else if (stoi(order[5]) < 10 || stoi(order[5]) > 1000) {// check for quantity in range
        reason = "Quantity must be in the range 10 to 1000";
    }
    else {
        if (order[2] == "Rose") {
            return 1;
        }
        else if (order[2] == "Lavender") {
            return 2;
        }
        else if (order[2] == "Lotus") {
            return 3;
        }
        else if (order[2] == "Tulip") {
            return 4;
        }
        else if (order[2] == "Orchid") {
            return 5;
        }
        else {
            reason = "Invalid instrument";
        }
    }
    std::vector<std::string> rejectedOrder = getRejectedReport(order, reason);
    //std::string rejectedLine = getRejectedOrderLine(order, reason);
    {
        std::unique_lock<std::mutex> lock(writerMtx);
        //writerBuffer += rejectedLine;
        writerBuffer.push_back(rejectedOrder);
    }
    return 0;
}

std::string OrderValidator::getRejectedOrderLine(const std::vector<std::string>& order, const std::string& reason)
{
    std::string line = "";
    if (order.size() == 6) {
        line = order[0] + "," + order[1] + "," + order[2] + "," + order[3] + "," + order[4] + "," + order[5] + ",1," + reason + "," + getDateTime();
    }
    else {
        if (order.size() < 6) {
            for (int i = 0; i < order.size(); i++) {
                line += order[i] + ",";
            }
            for (int i = 0; i < 6 - order.size(); i++) {
                line += ",";
            }
            line += "1," + reason + "," + getDateTime();
        }
        else {
            for (int i = 0; i < 5; i++) {
                line += order[i] + ",";
            }
            std::string txt = "";
            for (int i = 5; i < order.size(); i++) {
                txt += order[i] + " ";

            }
            line += txt + "," + "1," + reason + "," + getDateTime();
        }



    }
    return line;
}

//void OrderValidator::getRejectedOrders(std::vector<std::string>& orders) {
//	orders = rejectedOrders;
//}

//void OrderValidator::incrementrejectedOrders(std::string& orderID) {
//	int num = std::stoi(rejectedOrders.back().substr(2));
//    num++;
//    orderID = "er" + std::to_string(num);
//}

std::string OrderValidator::getDateTime()
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();

    std::time_t now_c = std::chrono::duration_cast<std::chrono::seconds>(epoch).count();

    std::tm time_info;
#ifdef _WIN32
    localtime_s(&time_info, &now_c); // Use localtime_s on Windows
#else
    localtime_r(&now_c, &time_info); // Use localtime_r on non-Windows systems
#endif

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", &time_info);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(epoch) % 1000;
    sprintf_s(buffer, "%s.%03lld", buffer, ms.count());

    return buffer;
}