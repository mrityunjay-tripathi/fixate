#ifndef DERIBIT_MESSAGE_HPP_
#define DERIBIT_MESSAGE_HPP_

#include <string>
#include <fixate/fixate.hpp>
#include "crypt.hpp"

namespace fixate {

    // Custom server defined tags.
    static constexpr const char* TagCancelOnDisconnect = "9001";
    static constexpr const char* TagUnsubscribeExecutionReports = "9009";
    static constexpr const char* TagConnectionOnlyExecutionReports = "9010";
    static constexpr const char* TagCancelOnDisconnectType = "35002";
    static constexpr const char* TagDeribitTradeAmount = "100007";
    static constexpr const char* TagDeribitTradeId = "100009";
    static constexpr const char* TagDeribitLabel = "100010";
    static constexpr const char* TagTradeVolume24h = "100087";
    static constexpr const char* TagMarkPrice = "100090";
    static constexpr const char* TagDeribitLiquidation = "100091";
    static constexpr const char* TagCurrentFunding = "100092";
    static constexpr const char* TagFunding8h = "100093";

    // Tag value pair for custom server defined tags.
    struct CancelOnDisconnect : public TvpChar<&TagCancelOnDisconnect> {};
    struct UnsubscribeExecutionReports : public TvpChar<&TagUnsubscribeExecutionReports> {};
    struct ConnectionOnlyExecutionReports : public TvpChar<&TagConnectionOnlyExecutionReports> {};
    struct CancelOnDisconnectType : public TvpChar<&TagCancelOnDisconnectType> {};
    struct DeribitTradeAmount : public TvpInteger<int, 16, &TagDeribitTradeAmount> {};
    struct DeribitTradeId : public TvpStringFixed<32, &TagDeribitTradeId> {};
    struct DeribitLabel : public TvpStringFixed<64, &TagDeribitLabel> {};
    struct TradeVolume24h : public TvpFloat<double, 32, &TagTradeVolume24h> {};
    struct MarkPrice : public TvpFloat<double, 32, &TagMarkPrice> {};
    struct DeribitLiquidation : public TvpStringFixed<4, &TagDeribitLiquidation> {};
    struct CurrentFunding : public TvpFloat<double, 32, &TagCurrentFunding> {};
    struct Funding8h : public TvpFloat<double, 32, &TagFunding8h> {};

    // Standard Header template for deribit.
    struct DeribitHeader : public TvpGroup<
       MessageType, PossDupFlag, SenderCompId, TargetCompId,
       MsgSeqNum, SendingTime, PossResend
    > {};

    // Fix message template for deribit.
    template <typename ... TvpTypes>
    struct DeribitFixMessage : public FixMessage<FixVersionType::FIX_4_4, DeribitHeader, TvpTypes...> {
        typedef FixMessage<FixVersionType::FIX_4_4, DeribitHeader, TvpTypes...> Base;
        DeribitFixMessage() : Base() {}
    };
}
namespace fx = fixate;

namespace examples {

    struct LogonRequest : public fx::DeribitFixMessage<fx::RawDataLength,
        fx::RawData, fx::HeartBtInt, fx::Username, fx::Password, fx::CancelOnDisconnect,
        fx::UnsubscribeExecutionReports, fx::ConnectionOnlyExecutionReports>
    {
    public:
        typedef fx::DeribitFixMessage<fx::RawDataLength,
            fx::RawData, fx::HeartBtInt, fx::Username, fx::Password, fx::CancelOnDisconnect,
            fx::UnsubscribeExecutionReports, fx::ConnectionOnlyExecutionReports
        > Base;
    public:
        LogonRequest(const std::string& apiKey, const std::string& secretKey, int heartbeatInterval) : Base()
        {
            Base::set<fx::MessageType>(fx::MessageTypeEnum::Logon);
            Base::set<fx::HeartBtInt>(heartbeatInterval);

            unsigned char nonce[32] = {};
            RAND_bytes(nonce, sizeof(nonce));
            std::string nonce64 = base64Encode(nonce, sizeof(nonce));
            std::string rawData = std::to_string(fx::epoch_timestamp() / 1000000LL) + "." + nonce64;

            Base::set<fx::RawDataLength>(rawData.size());
            Base::set<fx::RawData>(rawData);

            std::string baseSignatureStr = rawData + secretKey;
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, baseSignatureStr.c_str(), baseSignatureStr.size());
            SHA256_Final(hash, &sha256);
            std::string base64Encoding = base64Encode(hash, sizeof(hash));

            Base::set<fx::Username>(apiKey);
            Base::set<fx::Password>(base64Encoding);
        }
    };

    struct LogonResponse : public fx::DeribitFixMessage<fx::EncryptMethod,
    fx::HeartBtInt, fx::ResetSeqNumFlag, fx::CancelOnDisconnectType>
    {
        typedef fx::DeribitFixMessage<fx::EncryptMethod,
            fx::HeartBtInt, fx::ResetSeqNumFlag, fx::CancelOnDisconnectType
        > Base;
        LogonResponse() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::Logon); }
    };

    struct LogoutResponse : public fx::DeribitFixMessage<fx::Text, fx::SessionStatus>
    {
        typedef fx::DeribitFixMessage<fx::Text, fx::SessionStatus> Base;
        LogoutResponse() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::Logout); }
    };

    struct Heartbeat : public fx::DeribitFixMessage<fx::TestReqId>
    {
        typedef fx::DeribitFixMessage<fx::TestReqId> Base;
        Heartbeat() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::Heartbeat); }
    };

    struct TestRequest : public fx::DeribitFixMessage<fx::TestReqId>
    {
        typedef fx::DeribitFixMessage<fx::TestReqId> Base;
        TestRequest() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::TestRequest); }
    };

    using MDEntryTypes = fx::TvpArray<fx::MDEntryType, 3>;
    using RelatedSymbols = fx::TvpVector<fx::Symbol>;
    struct MarketDataRequest : public fx::DeribitFixMessage<fx::MDReqID, fx::SubscriptionRequestType, fx::MarketDepth,
        fx::MDUpdateType, fx::DeribitTradeAmount, fx::NoMDEntryTypes, MDEntryTypes, fx::NoRelatedSym, RelatedSymbols>
    {
        typedef fx::DeribitFixMessage<fx::MDReqID, fx::SubscriptionRequestType, fx::MarketDepth,
            fx::MDUpdateType, fx::DeribitTradeAmount, fx::NoMDEntryTypes, MDEntryTypes, fx::NoRelatedSym, RelatedSymbols
        > Base;
        MarketDataRequest() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::MarketDataRequest); }
    };

    struct MarketDataRequestReject : public fx::DeribitFixMessage<fx::MDReqRejReason, fx::MDReqID, fx::Text>
    {
        typedef fx::DeribitFixMessage<fx::MDReqRejReason, fx::MDReqID, fx::Text> Base;
        MarketDataRequestReject() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::MarketDataRequestReject); }
    };

    using MDEntries = fx::TvpVector<fx::TvpGroup<fx::MDUpdateAction, fx::MDEntryType, fx::MDEntryPx, fx::MDEntrySize, fx::MDEntryDate,
        fx::DeribitTradeId, fx::Side, fx::OrderID, fx::SecondaryOrderID, fx::OrderStatus, fx::DeribitLabel, fx::Price, fx::Text,
        fx::DeribitLiquidation, fx::TrdMatchID>>;
    struct MarketDataIncrementalRefresh : public fx::DeribitFixMessage<fx::Symbol, fx::ContractMultiplier,
        fx::TradeVolume24h, fx::MarkPrice, fx::OpenInterest, fx::PutOrCall,
        fx::MDReqID, fx::NoMDEntries, MDEntries>
    {
        typedef fx::DeribitFixMessage<fx::Symbol, fx::ContractMultiplier,
            fx::TradeVolume24h, fx::MarkPrice, fx::OpenInterest, fx::PutOrCall,
            fx::MDReqID, fx::NoMDEntries, MDEntries
        > Base;
        MarketDataIncrementalRefresh() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::MarketDataIncrementalRefresh); }
    };

    struct MarketDataSnapshotFullRefresh : public fx::DeribitFixMessage<fx::Symbol, fx::ContractMultiplier,
        fx::UnderlyingSymbol, fx::UnderlyingPrice, fx::TradeVolume24h, fx::MarkPrice, fx::OpenInterest, fx::PutOrCall,
        fx::CurrentFunding, fx::Funding8h, fx::MDReqID, fx::NoMDEntries, MDEntries>
    {
        typedef fx::DeribitFixMessage<fx::Symbol, fx::ContractMultiplier, fx::UnderlyingSymbol, fx::UnderlyingPrice,
            fx::TradeVolume24h, fx::MarkPrice, fx::OpenInterest, fx::PutOrCall, fx::CurrentFunding, fx::Funding8h,
            fx::MDReqID, fx::NoMDEntries, MDEntries
        > Base;
        MarketDataSnapshotFullRefresh() : Base() { Base::set<fx::MessageType>(fx::MessageTypeEnum::MarketDataSnapshotFullRefresh); }
    };

}

#endif

