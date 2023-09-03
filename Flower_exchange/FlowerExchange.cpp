
#include "OrderCSVReader.h"
#include "ExecutionReportCSVWriter.h"
#include "OrderValidator.h"
#include "OrderBook.h"
#include "OrderProcessor.h"
#include "OrderDivider.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>



int main() {
    //add code to measure time at the start of the program
    auto start = std::chrono::system_clock::now();

    OrderCSVReader reader("data/orders.csv"); // make order.csv file to orders.csv to run 100000 inputs
    ExecutionReportCSVWriter writer("data/Execution_rep.csv"); // ok
    OrderValidator validator(writer);// ok
    //OrderBook orderBook("rose");//ok
    OrderProcessor roseOrderprocessor("Rose", writer);//ok
    OrderProcessor lavenderOrderprocessor("Lavender", writer);//ok
    OrderProcessor lotusOrderprocessor("Lotus", writer);//ok
    OrderProcessor tulipOrderprocessor("Tulip", writer);//ok
    OrderProcessor orchidOrderprocessor("Orchid", writer);//ok
    //OrderDivider orderDivider(writer);//not implemented yet

    //instrument buffers
    std::vector<std::vector<std::string>> roseOrders;
    std::vector<std::vector<std::string>> lavenderOrders;
    std::vector<std::vector<std::string>> lotusOrders;
    std::vector<std::vector<std::string>> tulipOrders;
    std::vector<std::vector<std::string>> orchidOrders;

    //reader buffer
    std::vector<std::vector<std::string>> newOrders;
    //writer buffer
    std::vector<std::vector<std::string>> executionReports;

    std::mutex readerMtx;
    std::mutex roseMtx;
    std::mutex lavenderMtx;
    std::mutex lotusMtx;
    std::mutex tulipMtx;
    std::mutex orchidMtx;
    std::mutex writerMtx;

    bool doneReading = false;
    bool doneRose = false;
    bool doneLavender = false;
    bool doneLotus = false;
    bool doneTulip = false;
    bool doneOrchid = false;
    int doneWriting = 0;

    std::thread readerThread([&reader](std::vector<std::vector<std::string>>& orders, std::mutex& readerMtx, bool& doneReading) { 
        reader.getAllOrders(orders, readerMtx,doneReading); 
		}, std::ref(newOrders), std::ref(readerMtx), std::ref(doneReading));

    validator.validateAllorders(std::ref(newOrders), std::ref(executionReports), std::ref(roseOrders), std::ref(lavenderOrders), std::ref(lotusOrders), std::ref(tulipOrders), std::ref(orchidOrders),
        std::ref(readerMtx), std::ref(writerMtx), std::ref(roseMtx), std::ref(lavenderMtx), std::ref(lotusMtx), std::ref(tulipMtx), std::ref(orchidMtx),
        std::ref(doneReading), std::ref(doneRose), std::ref(doneLavender), std::ref(doneLotus), std::ref(doneTulip), std::ref(doneOrchid), std::ref(doneWriting)
    );
    
    readerThread.join();

   std::thread roseThread([&roseOrderprocessor](std::vector<std::vector<std::string>>& roseOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& roseMtx, bool& doneRose, int& doneWriting) {
        roseOrderprocessor.ProcessAllOrders(roseOrders, executionReports, writerMtx, roseMtx, doneRose, doneWriting);
        }, std::ref(roseOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(roseMtx), std::ref(doneRose), std::ref(doneWriting));
    std::thread lavenderThread([&lavenderOrderprocessor](std::vector<std::vector<std::string>>& lavenderOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& lavenderMtx, bool& doneLavender, int& doneWriting) {
        lavenderOrderprocessor.ProcessAllOrders(lavenderOrders, executionReports, writerMtx, lavenderMtx, doneLavender, doneWriting);
        }, std::ref(lavenderOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(lavenderMtx), std::ref(doneLavender), std::ref(doneWriting));
    std::thread lotusThread([&lotusOrderprocessor](std::vector<std::vector<std::string>>& lotusOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& lotusMtx, bool& doneLotus, int& doneWriting) {
        lotusOrderprocessor.ProcessAllOrders(lotusOrders, executionReports, writerMtx, lotusMtx, doneLotus, doneWriting);
        }, std::ref(lotusOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(lotusMtx), std::ref(doneLotus), std::ref(doneWriting));
    std::thread tulipThread([&tulipOrderprocessor](std::vector<std::vector<std::string>>& tulipOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& tulipMtx, bool& doneTulip, int& doneWriting) {
        tulipOrderprocessor.ProcessAllOrders(tulipOrders, executionReports, writerMtx, tulipMtx, doneTulip, doneWriting);
        }, std::ref(tulipOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(tulipMtx), std::ref(doneTulip), std::ref(doneWriting));
    std::thread orchidThread([&orchidOrderprocessor](std::vector<std::vector<std::string>>& orchidOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& orchidMtx, bool& doneOrchid, int& doneWriting) {
        orchidOrderprocessor.ProcessAllOrders(orchidOrders, executionReports, writerMtx, orchidMtx, doneOrchid, doneWriting);
        }, std::ref(orchidOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(orchidMtx), std::ref(doneOrchid), std::ref(doneWriting));

    roseThread.join();
    lavenderThread.join();
    lotusThread.join();
    tulipThread.join();
    orchidThread.join();

    for(int i = 0; i < executionReports.size(); i++){
		writer.writeExecutionRecord(executionReports[i]);
	}


    //add code to measure time at the end of the program
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken to process all orders: " << elapsed_seconds.count() << "s\n";


    return 0;
}
