#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <cstdint>
#include <fstream>
#include <cassert>
#include <thread>
#include <chrono>

#include "deribitmsg.hpp"

using namespace fixate;
using namespace examples;

struct DeribitConf
{
    std::string remoteAddress;
    int port;
    std::string apiKey;
    std::string secretKey;
    std::string senderCompId;
    std::string targetCompId;
};

class DeribitMarketDataAdapter
{
public:
    typedef tcp_client DataSourceType;
    typedef FixEngine<tcp_client, DeribitMarketDataAdapter> FixEngineType;
    static constexpr const int HEARTBEAT_INTERVAL_SEC = 15;
public:
    DeribitMarketDataAdapter(const DeribitConf& conf) : mConf(conf) {}
    ~DeribitMarketDataAdapter() { teardown(); }
    //! Call before program is about to die.
    void teardown() {
        mTimerActive = false;
        if (mTimerThread->joinable())
            mTimerThread->join();
        mFixEngine.disconnect();
    }
    //! Establish connection to remote server and perform login. This is a blocking operation.
    bool connectAndLogOn() {
        mTimerThread = std::make_unique<std::thread>([this](){
            this->mTimerActive = true;
            while (this->mTimerActive) {
                this->mCurrentTimestamp = epoch_timestamp();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });

        mDataSource = std::move(DataSourceType(mConf.remoteAddress, mConf.port,
                [this](){ std::cout << "Connected " << this->mConf.remoteAddress << ":" << this->mConf.port << std::endl; },
                [this](){ std::cout << "Disconnected " << this->mConf.remoteAddress << ":" << this->mConf.port << std::endl; },
                [](int ec, const std::string& msg){ std::cout << "Error:" << ec << "," << msg << std::endl; }));
        mFixEngine = std::move(FixEngineType(&mDataSource, this));
        mFixEngine.connect();

        int64_t ts = fx::epoch_timestamp();
        LogonRequest logOnRequest(mConf.apiKey, mConf.secretKey, 15);
        logOnRequest.set<CancelOnDisconnect>('Y');
        logOnRequest.set<SenderCompId>(mConf.senderCompId);
        logOnRequest.set<TargetCompId>(mConf.targetCompId);
        int bytesSent = sendmsg(logOnRequest, ts);
        assert(((void)"Failed to send login message", (bytesSent > 0)));
        while (!mIsLoggedOn && !mIsLogOnFailed) {
            perform();
        }
        return mIsLoggedOn;
    }
    bool perform() {
        if (mCurrentTimestamp > mNextHeartbeatTs && mIsLoggedOn) {
            sendHeartbeat(mCurrentTimestamp);
            mNextHeartbeatTs = mCurrentTimestamp + HEARTBEAT_INTERVAL_SEC * 1000000000LL;
        }
        return mFixEngine.perform();
    }
    template <typename TFixMessage>
    size_t sendmsg(TFixMessage& msg, int64_t timestamp) {
        msg.template set<fixate::MsgSeqNum>(++mOutMsgSeqNum);
        msg.template set<fixate::SendingTime>(timestamp);
        return mFixEngine.sendmsg(msg);
    }
    bool sendHeartbeat(int64_t ts) {
        TestRequest testRequest;
        testRequest.set<fx::TestReqId>(std::to_string(ts));
        testRequest.set<fx::SenderCompId>(mConf.senderCompId);
        testRequest.set<fx::TargetCompId>(mConf.targetCompId);
        return sendmsg(testRequest, ts) > 0;
    }
    bool subscribeMarketData(const std::string& contractName) {
        int64_t ts = fx::epoch_timestamp();
        MarketDataRequest marketDataRequest;
        marketDataRequest.set<MDReqID>(std::to_string(ts));
        marketDataRequest.set<SubscriptionRequestType>('1');
        marketDataRequest.set<MarketDepth>(0);
        marketDataRequest.set<MDUpdateType>('1');
        marketDataRequest.set<NoMDEntryTypes>(2);
        marketDataRequest.set<MDEntryTypes, MDEntryType>(0, '0');
        marketDataRequest.set<MDEntryTypes, MDEntryType>(1, '1');
        marketDataRequest.set<NoRelatedSym>(1);
        marketDataRequest.resize<RelatedSymbols>(1);
        marketDataRequest.set<RelatedSymbols, Symbol>(0, contractName);
        marketDataRequest.set<SenderCompId>(mConf.senderCompId);
        marketDataRequest.set<TargetCompId>(mConf.targetCompId);
        return sendmsg(marketDataRequest, ts) > 0;
    }
    void operator()(MessageTypeEnum msgType, const char* buffer, size_t n)
    {
        std::cout << "Incoming Message: " << fx::details::fixstring(buffer, n) << std::endl;
        if (msgType == MessageTypeEnum::MarketDataIncrementalRefresh) {
            MarketDataIncrementalRefresh m;
            m.parse(buffer);
        }
        else if (msgType == MessageTypeEnum::MarketDataSnapshotFullRefresh) {
            MarketDataSnapshotFullRefresh m;
            m.parse(buffer);
        }
        else if (msgType == fx::MessageTypeEnum::Heartbeat) {
            Heartbeat m;
            m.parse(buffer);
        }
        else if (msgType == fx::MessageTypeEnum::Logon)
        {
            LogonResponse m;
            m.parse(buffer);
            mIsLoggedOn = true;
            mIsLogOnFailed = false;
            std::cout << "Deribit: LoggedIn Successfully!" << std::endl;
        }
        else if (msgType == fx::MessageTypeEnum::Logout)
        {
            LogoutResponse m;
            m.parse(buffer);
            mIsLoggedOn = false;
            mIsLogOnFailed = true;
            std::cout << "Deribit: LoggedOut, Reason: " << m.get<fx::Text>() << std::endl;
        }
    }
private:
    DeribitConf mConf;
    DataSourceType mDataSource;
    FixEngineType mFixEngine;
    bool mIsLoggedOn = false;
    bool mIsLogOnFailed = false;
    int mOutMsgSeqNum = 0;
    int64_t mNextHeartbeatTs = -1;
    int64_t mCurrentTimestamp = -1;
    bool mTimerActive = false;
    std::unique_ptr<std::thread> mTimerThread;
};

