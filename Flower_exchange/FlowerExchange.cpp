
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









    //std::thread validatorThread([&validator](//validator thread if needed
    //    std::vector<std::vector<std::string>>& readerBuffer,
    //    std::vector<std::vector<std::string>>& writerBuffer,
    //    std::vector<std::vector<std::string>>& roseOrders,
    //    std::vector<std::vector<std::string>>& lavenderOrders,
    //    std::vector<std::vector<std::string>>& lotusOrders,
    //    std::vector<std::vector<std::string>>& tulipOrders,
    //    std::vector<std::vector<std::string>>& orchidOrders,
    //    std::mutex& readerMtx,
    //    std::mutex& writerMtx,
    //    std::mutex& roseMtx,
    //    std::mutex& lavenderMtx,
    //    std::mutex& lotusMtx,
    //    std::mutex& tulipMtx,
    //    std::mutex& orchidMtx,
    //    bool& doneReading,
    //    bool& doneRose,
    //    bool& doneLavender,
    //    bool& doneLotus,
    //    bool& doneTulip,
    //    bool& doneOrchid,
    //    int& doneWriting) {
    //    validator.validateAllorders(
    //        readerBuffer, writerBuffer, roseOrders, lavenderOrders, lotusOrders, tulipOrders, orchidOrders,
    //        readerMtx, writerMtx, roseMtx, lavenderMtx, lotusMtx, tulipMtx, orchidMtx,
    //        doneReading, doneRose, doneLavender, doneLotus, doneTulip, doneOrchid, doneWriting);
    //    },
    //    std::ref(newOrders), std::ref(executionReports), std::ref(roseOrders), std::ref(lavenderOrders), std::ref(lotusOrders), std::ref(tulipOrders), std::ref(orchidOrders),
    //    std::ref(readerMtx), std::ref(writerMtx), std::ref(roseMtx), std::ref(lavenderMtx), std::ref(lotusMtx), std::ref(tulipMtx), std::ref(orchidMtx),
    //    std::ref(doneReading), std::ref(doneRose), std::ref(doneLavender), std::ref(doneLotus), std::ref(doneTulip), std::ref(doneOrchid), std::ref(doneWriting));
    validator.validateAllorders(std::ref(newOrders), std::ref(executionReports), std::ref(roseOrders), std::ref(lavenderOrders), std::ref(lotusOrders), std::ref(tulipOrders), std::ref(orchidOrders),
        std::ref(readerMtx), std::ref(writerMtx), std::ref(roseMtx), std::ref(lavenderMtx), std::ref(lotusMtx), std::ref(tulipMtx), std::ref(orchidMtx),
        std::ref(doneReading), std::ref(doneRose), std::ref(doneLavender), std::ref(doneLotus), std::ref(doneTulip), std::ref(doneOrchid), std::ref(doneWriting)
    );
    //
    readerThread.join();
    //validatorThread.join();
  //  std::cout << "newOrders : " << newOrders.size() << endl;
  //  std::cout << "roseOrders : " << roseOrders.size() << endl;
  //  std::cout << "lavenderOrders : " << lavenderOrders.size() << endl;
  //  std::cout << "lotusOrders : " << lotusOrders.size() << endl;
  //  std::cout << "tulipOrders : " << tulipOrders.size() << endl;
  //  std::cout << "orchidOrders : " << orchidOrders.size() << endl;
  //  std::cout << "writerBuffer : " << executionReports.size() << endl;
  //  int total = roseOrders.size() + lavenderOrders.size() + lotusOrders.size() + tulipOrders.size() + orchidOrders.size() + executionReports.size(); 
  //  std::cout << "total : " << total << endl;

 /*   int newOrderCount = 0;
    int roseOrderCount = 0;
    int lavenderOrderCount = 0;
    int lotusOrderCount = 0;
    int tulipOrderCount = 0;
    int orchidOrderCount = 0;
    int invalidOrderCount = 0;*/
    //read orders one line at a time and pass it to the validator
 //   std::vector<std::string> orderLine;
 //   while (reader.getNextOrderLine(orderLine)) {
 //       int status = validator.newValidator(orderLine);
 //       if (status == 0) {
 //           continue;
 //       }else if (status == 1) {
 //           roseOrders.push_back(orderLine);
 //       }else if (status == 2) {
 //           lavenderOrders.push_back(orderLine);
 //       }else if (status == 3) {
 //           lotusOrders.push_back(orderLine);
 //       }else if (status == 4) {
 //           tulipOrders.push_back(orderLine);
 //       }else if (status == 5) {
 //           orchidOrders.push_back(orderLine);
 //       }
 //               /*if (!roseOrders.empty()) {
 //                   roseOrderprocessor.ProcessOrder(roseOrders.front());
 //                   roseOrders.erase(roseOrders.begin());
 //               }
 //               else if (!lavenderOrders.empty()) {
 //                   lavenderOrderprocessor.ProcessOrder(lavenderOrders.front());
 //                   lavenderOrders.erase(lavenderOrders.begin());
 //               }
 //               else if (!lotusOrders.empty()) {
 //                   lotusOrderprocessor.ProcessOrder(lotusOrders.front());
 //                   lotusOrders.erase(lotusOrders.begin());
 //               }
 //               else if (!tulipOrders.empty()) {
 //                   tulipOrderprocessor.ProcessOrder(tulipOrders.front());
 //                   tulipOrders.erase(tulipOrders.begin());
 //               }
 //               else if (!orchidOrders.empty()) {
 //                   orchidOrderprocessor.ProcessOrder(orchidOrders.front());
 //                   orchidOrders.erase(orchidOrders.begin());
 //               }*/
 //             
	//}



    //std::vector<std::string> orderLine;
    //while (reader.getNextOrderLine(orderLine)) {
    //    int status = validator.threadValidator(orderLine,executionReports,writerMtx);
    //    if (status == 1) {
    //        roseOrders.push_back(orderLine);
    //    }
    //    else if (status == 2) {
    //        lavenderOrders.push_back(orderLine);
    //    }
    //    else if (status == 3) {
    //        lotusOrders.push_back(orderLine);
    //    }
    //    else if (status == 4) {
    //        tulipOrders.push_back(orderLine);
    //    }
    //    else if (status == 5) {
    //        orchidOrders.push_back(orderLine);
    //    }
    //}
    //doneRose = doneLavender = doneLotus = doneTulip = doneOrchid = true;
    ////cout << "next phase" << endl;

    /*cout << "rose orders : " << roseOrders.size() << endl;
    cout << "lavender orders : " << lavenderOrders.size() << endl;  
    cout << "lotus orders : " << lotusOrders.size() << endl;
    cout << "tulip orders : " << tulipOrders.size() << endl;
    cout << "orchid orders : " << orchidOrders.size() << endl;*/



    //std::thread roseThread([&roseOrderprocessor](std::vector<std::vector<std::string>>& roseOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& roseMtx, bool& doneRose, int& doneWriting) {
    //    roseOrderprocessor.ProcessAllOrders(roseOrders, executionReports, writerMtx, roseMtx, doneRose, doneWriting);
    //    }, std::ref(roseOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(roseMtx), std::ref(doneRose), std::ref(doneWriting));
    //std::thread lavenderThread([&lavenderOrderprocessor](std::vector<std::vector<std::string>>& lavenderOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& lavenderMtx, bool& doneLavender, int& doneWriting) {
    //    lavenderOrderprocessor.ProcessAllOrders(lavenderOrders, executionReports, writerMtx, lavenderMtx, doneLavender, doneWriting);
    //    }, std::ref(lavenderOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(lavenderMtx), std::ref(doneLavender), std::ref(doneWriting));
    //std::thread lotusThread([&lotusOrderprocessor](std::vector<std::vector<std::string>>& lotusOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& lotusMtx, bool& doneLotus, int& doneWriting) {
    //    lotusOrderprocessor.ProcessAllOrders(lotusOrders, executionReports, writerMtx, lotusMtx, doneLotus, doneWriting);
    //    }, std::ref(lotusOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(lotusMtx), std::ref(doneLotus), std::ref(doneWriting));
    //std::thread tulipThread([&tulipOrderprocessor](std::vector<std::vector<std::string>>& tulipOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& tulipMtx, bool& doneTulip, int& doneWriting) {
    //    tulipOrderprocessor.ProcessAllOrders(tulipOrders, executionReports, writerMtx, tulipMtx, doneTulip, doneWriting);
    //    }, std::ref(tulipOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(tulipMtx), std::ref(doneTulip), std::ref(doneWriting));
    //std::thread orchidThread([&orchidOrderprocessor](std::vector<std::vector<std::string>>& orchidOrders, std::vector<std::vector<std::string>>& executionReports, std::mutex& writerMtx, std::mutex& orchidMtx, bool& doneOrchid, int& doneWriting) {
    //    orchidOrderprocessor.ProcessAllOrders(orchidOrders, executionReports, writerMtx, orchidMtx, doneOrchid, doneWriting);
    //    }, std::ref(orchidOrders), std::ref(executionReports), std::ref(writerMtx), std::ref(orchidMtx), std::ref(doneOrchid), std::ref(doneWriting));

    roseThread.join();
    lavenderThread.join();
    lotusThread.join();
    tulipThread.join();
    orchidThread.join();





 //   std::cout << "newOrders : " << newOrderCount << endl;
 //   std::cout << "roseOrders : " << roseOrderCount << endl;
 //   std::cout << "lavenderOrders : " << lavenderOrderCount << endl;
 //   std::cout << "lotusOrders : " << lotusOrderCount << endl;
 //   std::cout << "tulipOrders : " << tulipOrderCount << endl;
 //   std::cout << "orchidOrders : " << orchidOrderCount << endl;
 //   std::cout << "invalidOrders : " << invalidOrderCount << endl;
 //   int total = roseOrderCount + lavenderOrderCount + lotusOrderCount + tulipOrderCount + orchidOrderCount + invalidOrderCount;
 //   std::cout << "total : " << total << endl;

    //add code to measure time at the end of the program
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken to process all orders: " << elapsed_seconds.count() << "s\n";


    return 0;
}
