//OrderBook
#include "OrderBook.h"

OrderBook::OrderBook(std::string Instrument)
{
	// Set the instrument name
	this->Instrument = Instrument;

	// Instantiate the Sell Orderbook


}

OrderBook::~OrderBook()
{
}


// Sell Orderbook Functions
bool OrderBook::isSellEmpty()
{
	return sellHeap.empty();
}

double OrderBook::getSellMinVal()
{
	//get the price of the top vector in the sellHeap
	return stod(sellHeap.top()[4]);
}

std::vector<std::string> OrderBook::getSellMinVec()
{
	//get a copy of top vector in the sellHeap without popping it
	return sellHeap.top();
}

void OrderBook::popSellMinVec()
{
	//pop the top vector in the sellHeap
	sellHeap.pop();
}

void OrderBook::updateSellMinVec(const std::vector<std::string>& order)
{
	//update the top vector in the sellHeap by popping it
	sellHeap.pop();
	sellHeap.push(order);

}

void OrderBook::writeSell(const std::vector<std::string>& order)
{
	//write new order to the sellHeap
	sellHeap.push(order);

}


// Buy Orderbook Functions
bool OrderBook::isBuyEmpty()
{
	return buyHeap.empty();
}

double OrderBook::getBuyMaxVal()
{
	//get the price of the top vector in the buyHeap
	return stod(buyHeap.top()[4]);
}

std::vector<std::string> OrderBook::getBuyMaxVec()
{
	//get a copy of top vector in the buyHeap without popping it
	return buyHeap.top();
}

void OrderBook::popBuyMaxVec()
{
	//pop the top vector in the buyHeap
	buyHeap.pop();
}

void OrderBook::updateBuyMaxVec(const std::vector<std::string>& order)
{
	//update the top vector in the buyHeap by popping it
	buyHeap.pop();
	buyHeap.push(order);
}

void OrderBook::writeBuy(const std::vector<std::string>& order)
{
	//write new order to the buyHeap
	buyHeap.push(order);
}

std::string OrderBook::getInstrument()
{
	return Instrument;
}


