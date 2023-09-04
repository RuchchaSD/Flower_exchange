//FlowerExchange

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
    OrderProcessor roseOrderprocessor("Rose", writer),
        lavenderOrderprocessor("Lavender", writer),
        lotusOrderprocessor("Lotus", writer),
        tulipOrderprocessor("Tulip", writer),
        orchidOrderprocessor("Orchid", writer);

    //reader buffer
    std::vector<std::vector<std::string>> newOrders, roseOrders, lavenderOrders, lotusOrders, tulipOrders, orchidOrders;
    //writer buffer
    std::string executionReports;

    std::mutex readerMtx, roseMtx, lotusMtx, tulipMtx, orchidMtx, writerMtx, lavenderMtx;


    bool doneReading = false;
    bool doneRose = false;
    bool doneLavender = false;
    bool doneLotus = false;
    bool doneTulip = false;
    bool doneOrchid = false;
    int doneWriting = 0;
    std::condition_variable cvReader, cvRose, cvLavender, cvLotus, cvTulip, cvOrchid, cvWriter;

    std::thread readerThread([&reader](std::vector<std::vector<std::string>>& orders, std::mutex& readerMtx, bool& doneReading, std::condition_variable& cvReader) {
        reader.getAllOrders(orders, readerMtx, doneReading, cvReader);
        }, std::ref(newOrders), std::ref(readerMtx), std::ref(doneReading), std::ref(cvReader));

    std::thread roseThread([&roseOrderprocessor](std::vector<std::vector<std::string>>& roseOrders, std::string& executionReports, std::mutex& writerMtx, std::mutex& roseMtx, bool& doneRose, int& doneWriting, std::condition_variable& cvWriter, std::condition_variable& cvInstrument) {
        roseOrderprocessor.ProcessAllOrders(roseOrders, executionReports, writerMtx, roseMtx, doneRose, doneWriting, cvWriter, cvInstrument);
        }, std::ref(roseOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(roseMtx), std::ref(doneRose), std::ref(doneWriting), std::ref(cvWriter), std::ref(cvRose));
    std::thread lavenderThread([&lavenderOrderprocessor](std::vector<std::vector<std::string>>& lavenderOrders, std::string& executionReports, std::mutex& writerMtx, std::mutex& lavenderMtx, bool& doneLavender, int& doneWriting, std::condition_variable& cvWriter, std::condition_variable& cvInstrument) {
        lavenderOrderprocessor.ProcessAllOrders(lavenderOrders, executionReports, writerMtx, lavenderMtx, doneLavender, doneWriting, cvWriter, cvInstrument);
        }, std::ref(lavenderOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(lavenderMtx), std::ref(doneLavender), std::ref(doneWriting), std::ref(cvWriter), std::ref(cvLavender));
    std::thread lotusThread([&lotusOrderprocessor](std::vector<std::vector<std::string>>& lotusOrders, std::string& executionReports, std::mutex& writerMtx, std::mutex& lotusMtx, bool& doneLotus, int& doneWriting, std::condition_variable& cvWriter, std::condition_variable& cvInstrument) {
        lotusOrderprocessor.ProcessAllOrders(lotusOrders, executionReports, writerMtx, lotusMtx, doneLotus, doneWriting, cvWriter, cvInstrument);
        }, std::ref(lotusOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(lotusMtx), std::ref(doneLotus), std::ref(doneWriting), std::ref(cvWriter), std::ref(cvLotus));
    std::thread tulipThread([&tulipOrderprocessor](std::vector<std::vector<std::string>>& tulipOrders, std::string& executionReports, std::mutex& writerMtx, std::mutex& tulipMtx, bool& doneTulip, int& doneWriting, std::condition_variable& cvWriter, std::condition_variable& cvInstrument) {
        tulipOrderprocessor.ProcessAllOrders(tulipOrders, executionReports, writerMtx, tulipMtx, doneTulip, doneWriting, cvWriter, cvInstrument);
        }, std::ref(tulipOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(tulipMtx), std::ref(doneTulip), std::ref(doneWriting), std::ref(cvWriter), std::ref(cvTulip));
    std::thread orchidThread([&orchidOrderprocessor](std::vector<std::vector<std::string>>& orchidOrders, std::string& executionReports, std::mutex& writerMtx, std::mutex& orchidMtx, bool& doneOrchid, int& doneWriting, std::condition_variable& cvWriter, std::condition_variable& cvInstrument) {
        orchidOrderprocessor.ProcessAllOrders(orchidOrders, executionReports, writerMtx, orchidMtx, doneOrchid, doneWriting, cvWriter, cvInstrument);
        }, std::ref(orchidOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(orchidMtx), std::ref(doneOrchid), std::ref(doneWriting), std::ref(cvWriter), std::ref(cvOrchid));


    std::thread writerThread([&writer](std::string& executionReports, std::mutex& writerMtx, int& doneWriting, std::condition_variable& cvWriter) {
        writer.writeAllRecords(executionReports, writerMtx, doneWriting, cvWriter);
        }, std::ref(executionReports), std::ref(writerMtx), std::ref(doneWriting), std::ref(cvWriter));





    validator.validateAllorders(std::ref(newOrders), std::ref(executionReports), std::ref(roseOrders), std::ref(lavenderOrders), std::ref(lotusOrders), std::ref(tulipOrders), std::ref(orchidOrders),
        std::ref(readerMtx), std::ref(writerMtx), std::ref(roseMtx), std::ref(lavenderMtx), std::ref(lotusMtx), std::ref(tulipMtx), std::ref(orchidMtx),
        std::ref(doneReading), std::ref(doneRose), std::ref(doneLavender), std::ref(doneLotus), std::ref(doneTulip), std::ref(doneOrchid), std::ref(doneWriting),
        std::ref(cvReader), std::ref(cvRose), std::ref(cvLavender), std::ref(cvLotus), std::ref(cvTulip), std::ref(cvOrchid), std::ref(cvWriter)
    );


    readerThread.join();
    roseThread.join();
    lavenderThread.join();
    lotusThread.join();
    tulipThread.join();
    orchidThread.join();
    writerThread.join();

    /*writer.writeExecutionRecord(executionReports);*/



    //add code to measure time at the end of the program
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken to process all orders: " << elapsed_seconds.count() << "s\n";


    return 0;
}
