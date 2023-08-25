#include "OrderProcessor.h"


OrderProcessor::OrderProcessor(std::string Instrument, ExecutionReportCSVWriter& writer) : writer(writer) {

}

OrderProcessor::~OrderProcessor()
{
}

void OrderProcessor::recordOrder(const std::vector<std::string>& order, int status, int quantity)
{
}

void OrderProcessor::updateOrder(const std::vector<std::string>& order, int quantity)
{
}


void OrderProcessor::ProcessOrder(const std::vector<std::string>& order)
{
}
