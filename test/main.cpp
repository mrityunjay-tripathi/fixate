#include <iostream>
#include <ctime>
#include <vector>
#include <cstdint>
#include <fstream>
#include "common.hpp"

int writer(int N, const char* filename) {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file to write.\n";
        return 0;
    }

    char buffer[8192];
    std::memset(buffer, 0, sizeof(buffer));

    MarketDataIncrementalRefresh g;
    g.set<MessageType>(MessageTypeEnum::MarketDataIncrementalRefresh);
    g.set<TargetCompId>("TSERVER");
    g.set<SenderCompId>("DERIBITSERVER");

    ExecutionReport e;
    e.set<MessageType>(MessageTypeEnum::ExecutionReport);
    e.set<TargetCompId>("TSERVER");
    e.set<SenderCompId>("DERIBITSERVER");

    int reqId = random_number(10000, 20000);
    for (int i = 0; i < N; ++i) {
        int bW = 0;
        bool which = rand() % 2;
        if (which) {
            int noMdEntries = 4;
            {
                g.set<MsgSeqNum>(i);
                g.set<SendingTime>();
                g.set<MDReqID>(std::to_string(reqId++));
                g.set<NoMDEntries>(noMdEntries);
                g.resize<PxArray>(noMdEntries);
                for (int i = 0; i < noMdEntries; ++i) {
                    g.set<PxArray, BidPx>(i, random_number(100.0, 200.0), 2);
                    g.set<PxArray, BidSize>(i, random_number(1.0, 20.0), 1);
                    g.set<PxArray, OfferPx>(i, random_number(200.0, 300.0), 2);
                    g.set<PxArray, OfferSize>(i, random_number(1.0, 20.0), 1);
                }
            }
            bW = g.dump(buffer, true, true);
        } else {
            e.set<MsgSeqNum>(i);
            e.set<SendingTime>();
            e.set<ClOrdID>(std::to_string(random_number(100000, 999999)));
            e.set<OrigClOrdID>(std::to_string(random_number(100000, 999999)));
            e.set<Price>(random_number(150.0, 250.0), 2);
            e.set<OrderQty>(random_number(1.0, 5.0), 1);
            bW = e.dump(buffer, true, true);
        }
        file << std::string(buffer, bW);
    }
    return 1;
}

int reader(const char* filename)
{
    file_client fc(filename,
            [](){ std::cout << "Connected" << std::endl; },
            [](){ std::cout << "Disconnected" << std::endl; },
            [](int ec, const std::string& msg){ std::cout << "Error:" << ec << "," << msg << std::endl; });
    fc.connect();
    if (fc.active() == false) return 0;

    struct MessageVisitor
    {
        int count = 0;
        void operator()(MessageTypeEnum msgType, const char* buffer, size_t n)
        {
            count++;
            char d[8192];
            // int64_t start = system_timestamp();
            if (msgType == MessageTypeEnum::MarketDataIncrementalRefresh) {
                MarketDataIncrementalRefresh u;
                u.parse(buffer);

                u.dump(d);
                // std::cout << details::fixstring(d, b) << std::endl;
            }
            else if (msgType == MessageTypeEnum::ExecutionReport) {
                ExecutionReport e;
                e.parse(buffer);

                e.dump(d);
                // std::cout << details::fixstring(d, b) << std::endl;
            }
            // std::cout << (end - start) << std::endl;
        }
    };

    MessageVisitor mv;
    FixEngine e(&fc, &mv);

    int64_t start, end;
    try {
        start = system_timestamp();
        while (fc.active()) {
            e.perform();
        }
    }
    catch (const connection_exception& exc) {
        end = system_timestamp();
        char bufStart[32]; std::memset(bufStart, 0, sizeof(bufStart));
        strfutc<clock_precision::nanoseconds>(bufStart, end);
        char bufEnd[32]; std::memset(bufEnd, 0, sizeof(bufEnd));
        strfutc<clock_precision::nanoseconds>(bufEnd, end);
        std::cout << "Exception: " << exc.what() << ", avg time: " << (end - start) / mv.count << ", start: " << bufStart << ", end: " << bufEnd << std::endl;
    }
    return 1;
}

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage:\n\t<test read/write/both>\n";
        return -1;
    }
    char q = argv[1][0];
    if (argc < 3) {
        std::cout << "Usage:\n\t<test read/write/both> <filename>\n";
        return -1;
    }
    if ((q == 'w' || q == 'b') && (argc < 4)) {
        std::cout << "Usage:\n\t<test read/write/both> <filename> <msg count>\n";
        return -1;
    }
    const char* filename = argv[2];
    int N = std::stoi(argv[3]);

    if (!writer(N, filename)) return -1;
    if (!reader(filename)) return -1;
    return 0;
}

