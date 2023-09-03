#include "OrderProcessor.h"

//
OrderProcessor::OrderProcessor(std::string Instrument, ExecutionReportCSVWriter& writer) : writer(writer), orderBook(Instrument) {
}

OrderProcessor::~OrderProcessor()
{
}

void OrderProcessor::recordOrder(const std::vector<std::string>& order, int status, std::string quantity, double price)
{
	//print vec + status + quantity + price
	std::vector<std::string> orderDetails = { order[0], order[1], order[2], order[3],std::to_string(price),quantity, std::to_string(status),"_",getDateTime()};
	//OrderId, C_Id, Instrument, Side, Price,  Quantity,  Status,Reason, TimeStamp

	// Write order details to execution report writer
	writer.writeExecutionRecord(orderDetails);
}

void OrderProcessor::updateOrder(std::vector<std::string>& order, int quantity)
{
	// Update the order's quantity
	order[5] = std::to_string(quantity);
	//return order;
}




void OrderProcessor::ProcessOrder(const std::vector<std::string>& ord)
{
	std::vector<std::string> order = ord;

	//For buy orders
	if (order[3] == "1") {
		bool temp = true;

		while (temp) {
			//check the Sell Order Book is empty
			if (!orderBook.isSellEmpty()) {
				//check minimum price in sell order book
				if (orderBook.getSellMinVal() <= stod(order[4])) { // SellMinVal <= BuyPrice
					std::vector<std::string> SellVec;
					SellVec = orderBook.getSellMinVec();
					//compare quantity
					if (stoi(SellVec[5]) == stoi(order[5])) {	//SellQuantity == BuyQuantity
						recordOrder(order, 2, SellVec[5], orderBook.getSellMinVal());	//record buyorder in execution table 
						recordOrder(SellVec, 2, SellVec[5], orderBook.getSellMinVal());	//record sellorder in execution table
						orderBook.popSellMinVec();		//delete sellorder from sellorder book
						temp = false;
					}
					else if (stoi(SellVec[5]) > stoi(order[5])) {	//SellQuantity > BuyQuantity
						recordOrder(order, 2, order[5], orderBook.getSellMinVal());	//record buyorder in execution table 
						recordOrder(SellVec, 3, order[5], orderBook.getSellMinVal());	//record sellorder in execution table
						updateOrder(SellVec, stoi(SellVec[5]) - stoi(order[5]));
						orderBook.updateSellMinVec(SellVec);		//Update Sell order book
						temp = false;
					}
					
					else {//SellQuantity < BuyQuantity
						recordOrder(order, 3, SellVec[5], orderBook.getSellMinVal());
						recordOrder(SellVec, 2, SellVec[5], orderBook.getSellMinVal());
						updateOrder(order, stoi(order[5]) - stoi(SellVec[5]));	//update selected buy order
						orderBook.popSellMinVec();
					}
				}
				else {
					orderBook.writeBuy(order);
					recordOrder(order, 0, order[5], stod(order[4]));
					temp = false;
				}
			}
			else {
				orderBook.writeBuy(order);
				recordOrder(order, 0, order[5], stod(order[4]));
				temp = false;
			}
		}
	}
	//For sell orders
	else if (order[3] == "2") {
		bool temp = true;
		while (temp) {
			//check the Buy Order Book is empty
			if (!orderBook.isBuyEmpty()) {
				//check maximum price in buy order book
				if (orderBook.getBuyMaxVal() >= stod(order[4])) {
					std::vector<std::string> BuyVec;
					BuyVec = orderBook.getBuyMaxVec();
					//compare quantity
					if (stoi(BuyVec[5]) == stoi(order[5])) {	//SellQuantity == BuyQuantity
						recordOrder(order, 2, BuyVec[5], orderBook.getBuyMaxVal());	//record sellorder in execution table 
						recordOrder(BuyVec, 2, BuyVec[5], orderBook.getBuyMaxVal());	//record buyorder in execution table
						orderBook.popBuyMaxVec();		//delete buyorder from buyorder book
						temp = false;
					}
					else if (stoi(BuyVec[5]) > stoi(order[5])) {	//BuyQuantity > SellQuantity
						recordOrder(order, 2, order[5], orderBook.getBuyMaxVal());	//record sellorder in execution table 
						recordOrder(BuyVec, 3, order[5], orderBook.getBuyMaxVal());	//record buyorder in execution table
						updateOrder(BuyVec, stoi(BuyVec[5]) - stoi(order[5]));	//update buy vector
						orderBook.updateBuyMaxVec(BuyVec);		//update buy order book
						temp = false;
					}
					
					else {//SellQuantity > BuyQuantity
						recordOrder(order, 3, BuyVec[5], orderBook.getBuyMaxVal());
						recordOrder(BuyVec, 2, BuyVec[5], orderBook.getBuyMaxVal());
						updateOrder(order, stoi(order[5]) - stoi(BuyVec[5]));	//update selected sell order
						orderBook.popBuyMaxVec();
					}
				}
				else {
					orderBook.writeSell(order);
					recordOrder(order, 0, order[5], stod(order[4]));
					temp = false;
				}
			}
			else {
				orderBook.writeSell(order);
				recordOrder(order, 0, order[5], stod(order[4]));
				temp = false;
			}
		}
	}
}

void OrderProcessor::ProcessAllOrders(std::vector<std::vector<std::string>>& orderBuffer, std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx, std::mutex& orderMtx, bool& doneOrder, int& doneWriting)
{
	int countOut = 0;
	int count = 0;
	bool flag = false;
	bool emt = false;
	std::vector<std::string> order;
	while (true) {
		{
			emt = orderBuffer.size() > 20;
			countOut++;
			if (emt) {
				std::unique_lock<std::mutex> lock(orderMtx);
				flag = true;
				order = orderBuffer[0];
				orderBuffer.erase(orderBuffer.begin());
				count++;
			}else if (doneOrder) {
				//std::unique_lock<std::mutex> lock(orderMtx);
				if (orderBuffer.empty()) {
					std::cout << "Count : " << count << " CountOut : " << countOut << std::endl;
					break;
				}
				else {
					flag = true;
					order = orderBuffer[0];
					orderBuffer.erase(orderBuffer.begin());
					count++;
				}

			}
		}
		if (flag) {
			flag = false;
			ProcessOrder(order, writerBuffer, writerMtx);
		}
	}
	{
		std::unique_lock<std::mutex> lock6(writerMtx);
		doneWriting++;
	}
}


std::string OrderProcessor::getDateTime()
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

void OrderProcessor::ProcessOrder(const std::vector<std::string>& ord, std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx)
{
	std::vector<std::string> order = ord;

	//For buy orders
	if (order[3] == "1") {
		bool temp = true;

		while (temp) {
			//check the Sell Order Book is empty
			if (!orderBook.isSellEmpty()) {
				//check minimum price in sell order book
				if (orderBook.getSellMinVal() <= stod(order[4])) { // SellMinVal <= BuyPrice
					std::vector<std::string> SellVec;
					SellVec = orderBook.getSellMinVec();
					//compare quantity
					if (stoi(SellVec[5]) == stoi(order[5])) {	//SellQuantity == BuyQuantity
						recordOrder(order, 2, SellVec[5], orderBook.getSellMinVal(),std::ref(writerBuffer),std::ref(writerMtx));	//record buyorder in execution table 
						recordOrder(SellVec, 2, SellVec[5], orderBook.getSellMinVal(), std::ref(writerBuffer), std::ref(writerMtx));	//record sellorder in execution table
						orderBook.popSellMinVec();		//delete sellorder from sellorder book
						temp = false;
					}
					else if (stoi(SellVec[5]) > stoi(order[5])) {	//SellQuantity > BuyQuantity
						recordOrder(order, 2, order[5], orderBook.getSellMinVal(), std::ref(writerBuffer), std::ref(writerMtx));	//record buyorder in execution table 
						recordOrder(SellVec, 3, order[5], orderBook.getSellMinVal(), std::ref(writerBuffer), std::ref(writerMtx));	//record sellorder in execution table
						updateOrder(SellVec, stoi(SellVec[5]) - stoi(order[5]));
						orderBook.updateSellMinVec(SellVec);		//Update Sell order book
						temp = false;
					}

					else {//SellQuantity < BuyQuantity
						recordOrder(order, 3, SellVec[5], orderBook.getSellMinVal(), std::ref(writerBuffer), std::ref(writerMtx));
						recordOrder(SellVec, 2, SellVec[5], orderBook.getSellMinVal(), std::ref(writerBuffer), std::ref(writerMtx));
						updateOrder(order, stoi(order[5]) - stoi(SellVec[5]));	//update selected buy order
						orderBook.popSellMinVec();
					}
				}
				else {
					orderBook.writeBuy(order);
					recordOrder(order, 0, order[5], stod(order[4]), std::ref(writerBuffer), std::ref(writerMtx));
					temp = false;
				}
			}
			else {
				orderBook.writeBuy(order);
				recordOrder(order, 0, order[5], stod(order[4]), std::ref(writerBuffer), std::ref(writerMtx));
				temp = false;
			}
		}
	}
	//For sell orders
	else if (order[3] == "2") {
		bool temp = true;
		while (temp) {
			//check the Buy Order Book is empty
			if (!orderBook.isBuyEmpty()) {
				//check maximum price in buy order book
				if (orderBook.getBuyMaxVal() >= stod(order[4])) {
					std::vector<std::string> BuyVec;
					BuyVec = orderBook.getBuyMaxVec();
					//compare quantity
					if (stoi(BuyVec[5]) == stoi(order[5])) {	//SellQuantity == BuyQuantity
						recordOrder(order, 2, BuyVec[5], orderBook.getBuyMaxVal(), std::ref(writerBuffer), std::ref(writerMtx));	//record sellorder in execution table 
						recordOrder(BuyVec, 2, BuyVec[5], orderBook.getBuyMaxVal(), std::ref(writerBuffer), std::ref(writerMtx));	//record buyorder in execution table
						orderBook.popBuyMaxVec();		//delete buyorder from buyorder book
						temp = false;
					}
					else if (stoi(BuyVec[5]) > stoi(order[5])) {	//BuyQuantity > SellQuantity
						recordOrder(order, 2, order[5], orderBook.getBuyMaxVal(), std::ref(writerBuffer), std::ref(writerMtx));	//record sellorder in execution table 
						recordOrder(BuyVec, 3, order[5], orderBook.getBuyMaxVal(), std::ref(writerBuffer), std::ref(writerMtx));	//record buyorder in execution table
						updateOrder(BuyVec, stoi(BuyVec[5]) - stoi(order[5]));	//update buy vector
						orderBook.updateBuyMaxVec(BuyVec);		//update buy order book
						temp = false;
					}

					else {//SellQuantity > BuyQuantity
						recordOrder(order, 3, BuyVec[5], orderBook.getBuyMaxVal(), std::ref(writerBuffer), std::ref(writerMtx));
						recordOrder(BuyVec, 2, BuyVec[5], orderBook.getBuyMaxVal(), std::ref(writerBuffer), std::ref(writerMtx));
						updateOrder(order, stoi(order[5]) - stoi(BuyVec[5]));	//update selected sell order
						orderBook.popBuyMaxVec();
					}
				}
				else {
					orderBook.writeSell(order);
					recordOrder(order, 0, order[5], stod(order[4]), std::ref(writerBuffer), std::ref(writerMtx));
					temp = false;
				}
			}
			else {
				orderBook.writeSell(order);
				recordOrder(order, 0, order[5], stod(order[4]), std::ref(writerBuffer), std::ref(writerMtx));
				temp = false;
			}
		}
	}

}

void OrderProcessor::recordOrder(const std::vector<std::string>& order, int status, std::string quantity, double price, std::vector<std::vector<std::string>>& writerBuffer, std::mutex& writerMtx)
{
	//print vec + status + quantity + price
	std::vector<std::string> orderDetails = { order[0], order[1], order[2], order[3],std::to_string(price),quantity, std::to_string(status),"_",getDateTime() }; 
	//OrderId, C_Id, Instrument, Side, Price,  Quantity,  Status,Reason, TimeStamp
	// Write order details to writerBuffer
	{
		std::unique_lock<std::mutex> lock(writerMtx);
		writerBuffer.push_back(orderDetails);
	}

}
