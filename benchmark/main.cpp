#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <random>
#include <stdio.h>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <benchmark/benchmark.h>

#include "fixate/fixate.hpp"

#define LO 1 << 1
#define HI 1 << 8

inline int64_t random_number(int min, int max)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int64_t> distribution(min, max);

    return distribution(generator);
}

inline double random_number(double min, double max)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

using namespace fixate;
using MsgInitials = TvpGroup<BeginString<16>, BodyLength, MessageType>;

struct PeekMessage {
    int operator()(const char* buffer, MsgInitials& g) {
        g.parse(buffer);
        return g.width<BeginString<16>>() + g.width<BodyLength>() + g.get<BodyLength>() + 7;
    }
};

using PxArray = TvpVector<TvpGroup<BidPx, BidSize, OfferPx, OfferSize>>;

typedef FixMessage<
    FixVersionType::FIX_4_4,
    MessageType, MsgSeqNum, SenderCompId, TargetCompId, SendingTime,
    MDReqID, NoMDEntries, PxArray, CumQty
> MarketDataIncrementalRefresh;

typedef FixMessage<
    FixVersionType::FIX_4_4,
    MessageType, MsgSeqNum, SenderCompId, TargetCompId, SendingTime,
    ClOrdID, OrigClOrdID, Price, OrderQty
> ExecutionReport;

static void BM_FixWriter(benchmark::State &state)
{
    const size_t N = state.range(0);
    std::vector<std::pair<double, double>> randomBids;
    for (size_t i = 0; i < N; ++i) {
        randomBids.push_back({random_number(10000.0, 20000.0), random_number(100.0, 900.0)});
    }
    std::vector<std::pair<double, double>> randomOffers;
    for (size_t i = 0; i < N; ++i) {
        randomOffers.push_back({random_number(20000.0, 30000.0), random_number(100.0, 900.0)});
    }

    MarketDataIncrementalRefresh g;
    int noMdEntries = N;
    {
        g.set<MsgSeqNum>(567);
        g.set<SenderCompId>("CLIENT");
        g.set<TargetCompId>("SERVER");
        g.set<SendingTime>();
        g.set<MDReqID>("RAND-MD-ID");
        g.set<NoMDEntries>(noMdEntries);
        g.resize<PxArray>(noMdEntries);
        for (int i = 0; i < noMdEntries; ++i) {
            g.set<PxArray, BidPx>(i, randomBids[i].first, 2);
            g.set<PxArray, BidSize>(i, randomBids[i].second, 2);
            g.set<PxArray, OfferPx>(i, randomOffers[i].first, 2);
            g.set<PxArray, OfferSize>(i, randomOffers[i].second, 2);
        }
        g.updateBodyLength();
        g.updateCheckSum();
    }

    char buffer[8192];
    for (auto _ : state)
    {
        g.dump(buffer);
        benchmark::ClobberMemory();
    }
    state.SetComplexityN(state.range(0));
    state.SetItemsProcessed(long(state.iterations()) * long(N));
}
BENCHMARK(BM_FixWriter)->RangeMultiplier(2)->Range(2, 32)->Complexity(benchmark::oN);

static void BM_FixReader(benchmark::State &state)
{
    const size_t N = state.range(0);
    MarketDataIncrementalRefresh g;

    const char* buffer = "8=FIX.4.4""\x01""9=234""\x01""35=X""\x01""34=0""\x01""49=DERIBITSERVER""\x01""56=TSERVER""\x01""52=20250211-12:28:38.728""\x01""262=19985""\x01""268=4""\x01""132=125.30""\x01""134=4.1""\x01""133=220.93""\x01""135=9.1""\x01""132=144.97""\x01""134=4.8""\x01""133=207.69""\x01""135=5.9""\x01""132=170.00""\x01""134=18.5""\x01""133=289.20""\x01""135=8.0""\x01""132=161.83""\x01""134=16.4""\x01""133=294.64""\x01""135=11.0""\x01""10=090";
    for (auto _ : state)
    {
        g.parse(buffer);
        benchmark::ClobberMemory();
    }
    state.SetComplexityN(state.range(0));
    state.SetItemsProcessed(long(state.iterations()) * long(N));
}
BENCHMARK(BM_FixReader)->RangeMultiplier(2)->Range(LO, HI)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
