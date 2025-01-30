#pragma once

#include <random>
#include "fixate/fixate.hpp"

inline double random_number(double min, double max)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

inline int64_t random_number(int min, int max)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int64_t> distribution(min, max);

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
    MDReqID, NoMDEntries, PxArray
> MarketDataIncrementalRefresh;

typedef FixMessage<
    FixVersionType::FIX_4_4,
    MessageType, MsgSeqNum, SenderCompId, TargetCompId, SendingTime,
    ClOrdID, OrigClOrdID, Price, OrderQty
> ExecutionReport;

