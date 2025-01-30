/**
* @file fixate/fixtags.hpp
* @author Mrityunjay Tripathi
*
* fixate is free software; you may redistribute it and/or modify it under the
* terms of the BSD 2-Clause "Simplified" License. You should have received a copy of the
* BSD 2-Clause "Simplified" License along with fixate. If not, see
* http://www.opensource.org/licenses/BSD-2-Clause for more information.
*
* Copyright (c) 2025, Mrityunjay Tripathi
*/
#ifndef FIXATE_FIX_TAGS_HPP_
#define FIXATE_FIX_TAGS_HPP_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsubobject-linkage"

#include "fixate/fixbase.hpp"
#include "fixate/fixmsgtype.hpp"
#include "fixate/fixdatetime.hpp"

namespace fixate {

    // FIX specified tags in range [1, 5000).
    // User defined tags are in range [5000, inf).
    // Do not add user defined tags here.
    static constexpr const char* TagAccount = "1";
    static constexpr const char* TagAdvId = "2";
    static constexpr const char* TagAdvRefID = "3";
    static constexpr const char* TagAdvSide = "4";
    static constexpr const char* TagAdvTransType = "5";
    static constexpr const char* TagAvgPx = "6";
    static constexpr const char* TagBeginSeqNo = "7";
    static constexpr const char* TagBeginString = "8";
    static constexpr const char* TagBodyLength = "9";
    static constexpr const char* TagCheckSum = "10";
    static constexpr const char* TagClOrdID = "11";
    static constexpr const char* TagCommission = "12";
    static constexpr const char* TagCommType = "13";
    static constexpr const char* TagCumQty = "14";
    static constexpr const char* TagCurrency = "15";
    static constexpr const char* TagEndSeqNo = "16";
    static constexpr const char* TagExecID = "17";
    static constexpr const char* TagExecInst = "18";
    static constexpr const char* TagExecRefID = "19";
    static constexpr const char* TagExecTransType = "20";
    static constexpr const char* TagLastMkt = "30";
    static constexpr const char* TagLastPx = "31";
    static constexpr const char* TagLastQty = "32";
    static constexpr const char* TagMsgSeqNum = "34";
    static constexpr const char* TagMessageType = "35";
    static constexpr const char* TagNewSeqNo = "36";
    static constexpr const char* TagOrderID = "37";
    static constexpr const char* TagOrderQty = "38";
    static constexpr const char* TagOrderStatus = "39";
    static constexpr const char* TagOrderType = "40";
    static constexpr const char* TagOrigClOrdID = "41";
    static constexpr const char* TagPossDupFlag = "43";
    static constexpr const char* TagPrice = "44";
    static constexpr const char* TagRefSeqNum = "45";
    static constexpr const char* TagSecurityID = "48";
    static constexpr const char* TagSenderCompId = "49";
    static constexpr const char* TagSenderSubID = "50";
    static constexpr const char* TagSendingDate = "51";
    static constexpr const char* TagSendingTime = "52";
    static constexpr const char* TagQuantity = "53";
    static constexpr const char* TagSide = "54";
    static constexpr const char* TagSymbol = "55";
    static constexpr const char* TagTargetCompId = "56";
    static constexpr const char* TagText = "58";
    static constexpr const char* TagTimeInForce = "59";
    static constexpr const char* TagValidUntilTime = "62";
    static constexpr const char* TagTransactTime = "60";
    static constexpr const char* TagRawDataLength = "95";
    static constexpr const char* TagRawData = "96";
    static constexpr const char* TagPossResend = "97";
    static constexpr const char* TagEncryptMethod = "98";
    static constexpr const char* TagStopPx = "99";
    static constexpr const char* TagOrdRejReason = "103";
    static constexpr const char* TagHeartBtInt = "108";
    static constexpr const char* TagTestReqId = "112";
    static constexpr const char* TagQuoteID = "117";
    static constexpr const char* TagQuoteReqID = "131";
    static constexpr const char* TagBidPx = "132";
    static constexpr const char* TagOfferPx = "133";
    static constexpr const char* TagBidSize = "134";
    static constexpr const char* TagOfferSize = "135";
    static constexpr const char* TagResetSeqNumFlag = "141";
    static constexpr const char* TagExecType = "150";
    static constexpr const char* TagLeavesQty = "151";
    static constexpr const char* TagSecondaryOrderID = "198";
    static constexpr const char* TagPutOrCall = "201";
    static constexpr const char* TagSecurityExchange = "207";
    static constexpr const char* TagMaxShow = "210";
    static constexpr const char* TagPegOffsetValue = "211";
    static constexpr const char* TagContractMultiplier = "231";
    static constexpr const char* TagMDReqID = "262";
    static constexpr const char* TagSubscriptionRequestType = "263";
    static constexpr const char* TagMarketDepth = "264";
    static constexpr const char* TagMDUpdateType = "265";
    static constexpr const char* TagAggregatedBook = "266";
    static constexpr const char* TagMDEntryType = "269";
    static constexpr const char* TagMDEntryPx = "270";
    static constexpr const char* TagMDEntrySize = "271";
    static constexpr const char* TagMDEntryDate = "272";
    static constexpr const char* TagMDUpdateAction = "279";
    static constexpr const char* TagMDReqRejReason = "281";
    static constexpr const char* TagUnderlyingSymbol = "311";
    static constexpr const char* TagRefMsgType = "372";
    static constexpr const char* TagSessionRejectReason = "373";
    static constexpr const char* TagSecondaryExecID = "373";
    static constexpr const char* TagMDImplicitDelete = "547";
    static constexpr const char* TagUsername = "553";
    static constexpr const char* TagPassword = "554";
    static constexpr const char* TagOpenInterest = "746";
    static constexpr const char* TagUnderlyingPrice = "810";
    static constexpr const char* TagPeggedPrice = "839";
    static constexpr const char* TagQtyType = "854";
    static constexpr const char* TagTrdMatchID = "880";
    static constexpr const char* TagPegPriceType = "1094";
    static constexpr const char* TagVolatility = "1188";
    static constexpr const char* TagFillExecID = "1363";
    static constexpr const char* TagFillPx = "1364";
    static constexpr const char* TagFillQty = "1365";
    static constexpr const char* TagSessionStatus = "1409";
    static constexpr const char* TagFillLiquidityInd = "1443";

    static constexpr const char* TagNoAllocs = "78";
    static constexpr const char* TagNoRelatedSym = "146";
    static constexpr const char* TagNoMDEntryTypes = "267";
    static constexpr const char* TagNoMDEntries = "268";
    static constexpr const char* TagNoBidDescriptors = "398";
    static constexpr const char* TagNoBidComponents = "420";
    static constexpr const char* TagNoContAmts = "518";
    static constexpr const char* TagNoAffectedOrders = "534";
    static constexpr const char* TagNoClearingInstructions = "576";
    static constexpr const char* TagNoAltMDSource = "816";
    static constexpr const char* TagNoCapacities = "862";
    static constexpr const char* TagNoCollInquiryQualifier = "938";
    static constexpr const char* TagNoCompIDs = "936";
    static constexpr const char* TagNoFills = "1362";
}

namespace fixate {

    template <size_t VSize>
    struct BeginString : public TvpStringFixed<VSize, &TagBeginString> {
        typedef TvpStringFixed<VSize, &TagBeginString> Base;
        BeginString(const std::string& str = "") : Base(str) {}
        BeginString(const char* str, size_t strLen) : Base(str, strLen) {}
    };
    struct FixVersion_4_0 : public BeginString<7> {
        typedef BeginString<7> Base;
        FixVersion_4_0() : Base() { Base::set("FIX.4.0"); }
    };
    struct FixVersion_4_1 : public BeginString<7> {
        typedef BeginString<7> Base;
        FixVersion_4_1() : Base() { Base::set("FIX.4.1"); }
    };
    struct FixVersion_4_2 : public BeginString<7> {
        typedef BeginString<7> Base;
        FixVersion_4_2() : Base() { Base::set("FIX.4.2"); }
    };
    struct FixVersion_4_3 : public BeginString<7> {
        typedef BeginString<7> Base;
        FixVersion_4_3() : Base() { Base::set("FIX.4.3"); }
    };
    struct FixVersion_4_4 : public BeginString<7> {
        typedef BeginString<7> Base;
        FixVersion_4_4() : Base() { Base::set("FIX.4.4"); }
    };
    struct FixVersion_5_0 : public BeginString<7> {
        typedef BeginString<7> Base;
        FixVersion_5_0() : Base() { Base::set("FIX.5.0"); }
    };
    struct Account : public TvpStringFixed<32, &TagAccount> {};
    struct AdvId : public TvpStringFixed<32, &TagAdvId> {};
    struct AdvRefID : public TvpStringFixed<32, &TagAdvRefID> {};
    struct AdvSide : public TvpChar<&TagAdvSide> {};
    struct AdvTransType : public TvpChar<&TagAdvTransType> {};
    struct AvgPx : public TvpFloat<double, 32, &TagAvgPx> {};
    struct BeginSeqNo : public TvpInteger<int64_t, 32, &TagBeginSeqNo> {};
    struct BodyLength : public TvpInteger<int, 6, &TagBodyLength> {};
    struct CheckSum : public TvpInteger<uint8_t, 3, &TagCheckSum> {
        typedef TvpInteger<uint8_t, 3, &TagCheckSum> Base;
        template <typename T = void>
        void set(uint8_t checksum) {
            value[0] = '0' + ((checksum / 100) % 10);
            value[1] = '0' + ((checksum / 10) % 10);
            value[2] = '0' + (checksum % 10);
            Base::usedLen = 3;
        }
    };
    struct ClOrdID : public TvpStringFixed<32, &TagClOrdID> {};
    struct CommType : public TvpChar<&TagCommType> {};
    struct Commission : public TvpFloat<double, 32, &TagCommission> {};
    struct CumQty : public TvpFloat<double, 32, &TagCumQty> {};
    struct Currency : public TvpStringFixed<16, &TagCurrency> {};
    struct EndSeqNo : public TvpInteger<int64_t, 32, &TagEndSeqNo> {};
    struct ExecID : public TvpStringFixed<32, &TagExecID> {};
    struct ExecInst : public TvpChar<&TagExecInst> {};
    struct ExecRefID : public TvpStringFixed<32, &TagExecRefID> {};
    struct ExecTransType : public TvpChar<&TagExecTransType> {};
    struct LastMkt : public TvpStringFixed<32, &TagLastMkt> {};
    struct LastPx : public TvpFloat<double, 32, &TagLastPx> {};
    struct LastQty : public TvpFloat<double, 32, &TagLastQty> {};
    struct MsgSeqNum : public TvpInteger<int, 16, &TagMsgSeqNum> {
        typedef TvpInteger<int, 16, &TagMsgSeqNum> Base;
        MsgSeqNum() : Base() {}
        MsgSeqNum(const char* buf, size_t bufSize) : Base() {
            std::memcpy(Base::value, buf, bufSize);
        }
    };
    struct MessageType : public TvpStringFixed<3, &TagMessageType> {
        typedef TvpStringFixed<3, &TagMessageType> Base;
        bool operator==(const MessageType& other) {
            return usedLen == other.usedLen && 0 == std::memcmp(value, other.value, usedLen);
        }
        bool operator!=(const MessageType& other) { return !(*this == other); }
        template <typename T = void>
        void set(MessageTypeEnum val) {
            const char* str = details::MessageTypeEnumToString[(int)val];
            size_t strLen = strlen(str);
            Base::set(std::string_view(str, strLen));
        }
    };
    struct NewSeqNo : public TvpInteger<int64_t, 32, &TagNewSeqNo> {};
    struct OrderID : public TvpStringFixed<32, &TagOrderID> {};
    struct OrderQty : public TvpFloat<double, 32, &TagOrderQty> {};
    struct OrderStatus : public TvpChar<&TagOrderStatus> {};
    struct OrderType : public TvpChar<&TagOrderType> {};
    struct OrigClOrdID : public TvpStringFixed<32, &TagOrigClOrdID> {};
    struct PossDupFlag : public TvpChar<&TagPossDupFlag> {};
    struct Price : public TvpFloat<double, 32, &TagPrice> {};
    struct RefSeqNum : public TvpInteger<int64_t, 32, &TagRefSeqNum> {};
    struct SecurityID : public TvpStringFixed<32, &TagSecurityID> {};
    struct SenderCompId : public TvpStringFixed<32, &TagSenderCompId> {};
    struct SenderSubID : public TvpStringFixed<32, &TagSenderSubID> {};
    struct SendingDate : public TvpStringFixed<32, &TagSendingDate> {};
    struct SendingTime : public TvpStringFixed<32, &TagSendingTime> {
        typedef TvpStringFixed<32, &TagSendingTime> Base;
        template <typename T = void>
        void set(int64_t ts, bool utc = true, char prec = 'm') {
            if (utc) { Base::usedLen = strfutc(&Base::value[0], ts, prec); }
            else { Base::usedLen = strflocal(&Base::value[0], ts, prec); }
        }
        template <typename T = void>
        void set(bool utc = true, char prec = 'm') {
            return set(epoch_timestamp(), utc, prec);
        }
    };
    struct Quantity : public TvpFloat<double, 32, &TagQuantity> {};
    struct Side : public TvpChar<&TagSide> {};
    struct Symbol : public TvpStringFixed<32, &TagSymbol> {};
    struct TargetCompId : public TvpStringFixed<32, &TagTargetCompId> {};
    struct Text : public TvpStringFixed<256, &TagText> {};
    struct TimeInForce : public TvpChar<&TagTimeInForce> {};
    struct ValidUntilTime : public TvpStringFixed<32, &TagValidUntilTime> {};
    struct TransactTime : public TvpStringFixed<32, &TagTransactTime> {};
    struct RawDataLength : public TvpInteger<int, 16, &TagRawDataLength> {};
    struct RawData : public TvpStringDynamic<&TagRawData> {};
    struct PossResend : public TvpChar<&TagPossResend> {};
    struct EncryptMethod : public TvpChar<&TagEncryptMethod> {};
    struct StopPx : public TvpFloat<double, 32, &TagStopPx> {};
    struct OrdRejReason : public TvpInteger<int, 16, &TagOrdRejReason> {};
    struct HeartBtInt: public TvpInteger<int64_t, 32, &TagHeartBtInt> {};
    struct TestReqId : public TvpStringFixed<32, &TagTestReqId> {};
    struct QuoteReqID : public TvpStringFixed<32, &TagQuoteReqID> {};
    struct BidPx : public TvpFloat<double, 32, &TagBidPx> {};
    struct OfferPx : public TvpFloat<double, 32, &TagOfferPx> {};
    struct BidSize : public TvpFloat<double, 32, &TagBidSize> {};
    struct OfferSize : public TvpFloat<double, 32, &TagOfferSize> {};
    struct QuoteID : public TvpStringFixed<32, &TagQuoteID> {};
    struct ResetSeqNumFlag : public TvpChar<&TagResetSeqNumFlag> {};
    struct ExecType : public TvpChar<&TagExecType> {};
    struct LeavesQty : public TvpFloat<double, 32, &TagLeavesQty> {};
    struct SecondaryOrderID : public TvpStringFixed<32, &TagSecondaryOrderID> {};
    struct PutOrCall : public TvpChar<&TagPutOrCall> {};
    struct SecurityExchange : public TvpStringFixed<32, &TagSecurityExchange> {};
    struct MaxShow : public TvpFloat<double, 32, &TagMaxShow> {};
    struct PegOffsetValue : public TvpFloat<double, 32, &TagPegOffsetValue> {};
    struct ContractMultiplier : public TvpFloat<double, 32, &TagContractMultiplier> {};
    struct MDReqID : public TvpStringFixed<64, &TagMDReqID> {};
    struct SubscriptionRequestType : public TvpChar<&TagSubscriptionRequestType> {};
    struct MarketDepth : public TvpInteger<int, 16, &TagMarketDepth> {};
    struct MDUpdateType : public TvpChar<&TagMDUpdateType> {};
    struct AggregatedBook : public TvpChar<&TagAggregatedBook> {};
    struct MDEntryType : public TvpChar<&TagMDEntryType> {};
    struct MDEntryPx : public TvpFloat<double, 32, &TagMDEntryPx> {};
    struct MDEntrySize : public TvpFloat<double, 32, &TagMDEntrySize> {};
    struct MDEntryDate : public TvpStringFixed<32, &TagMDEntryDate> {};
    struct MDUpdateAction : public TvpChar<&TagMDUpdateAction> {};
    struct MDReqRejReason : public TvpChar<&TagMDReqRejReason> {};
    struct UnderlyingSymbol : public TvpStringFixed<32, &TagUnderlyingSymbol> {};
    struct RefMsgType : public TvpStringFixed<64, &TagRefMsgType> {};
    struct SessionRejectReason : public TvpInteger<int, 16, &TagSessionRejectReason> {};
    struct SecondaryExecID : public TvpStringFixed<64, &TagSecondaryExecID> {};
    struct MDImplicitDelete : public TvpChar<&TagMDImplicitDelete> {};
    struct Username : public TvpStringFixed<64, &TagUsername> {};
    struct Password : public TvpStringFixed<256, &TagPassword> {};
    struct OpenInterest : public TvpFloat<double, 32, &TagOpenInterest> {};
    struct UnderlyingPrice : public TvpFloat<double, 32, &TagUnderlyingPrice> {};
    struct PeggedPrice : public TvpFloat<double, 32, &TagPeggedPrice> {};
    struct QtyType : public TvpChar<&TagQtyType> {};
    struct TrdMatchID : public TvpStringFixed<64, &TagTrdMatchID> {};
    struct PegPriceType : public TvpInteger<int, 4, &TagPegPriceType> {};
    struct Volatility : public TvpFloat<double, 32, &TagVolatility> {};
    struct FillExecID : public TvpStringFixed<32, &TagFillExecID> {};
    struct FillPx : public TvpFloat<double, 32, &TagFillPx> {};
    struct FillQty : public TvpFloat<double, 32, &TagFillQty> {};
    struct SessionStatus : public TvpChar<&TagSessionStatus> {};
    struct FillLiquidityInd : public TvpChar<&TagFillLiquidityInd> {};

    /// Here goes all the vector/array size specifying tags.
    struct NoAllocs : public TvpInteger<int64_t, 16, &TagNoAllocs> {
        typedef TvpInteger<int64_t, 16, &TagNoAllocs> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoRelatedSym : public TvpInteger<int64_t, 16, &TagNoRelatedSym> {
        typedef TvpInteger<int64_t, 16, &TagNoRelatedSym> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoMDEntryTypes : public TvpInteger<int64_t, 16, &TagNoMDEntryTypes> {
        typedef TvpInteger<int64_t, 16, &TagNoMDEntryTypes> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoMDEntries : public TvpInteger<int64_t, 16, &TagNoMDEntries> {
        typedef TvpInteger<int64_t, 16, &TagNoMDEntries> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoBidDescriptors : public TvpInteger<int64_t, 16, &TagNoBidDescriptors> {
        typedef TvpInteger<int64_t, 16, &TagNoBidDescriptors> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoBidComponents : public TvpInteger<int64_t, 16, &TagNoBidComponents> {
        typedef TvpInteger<int64_t, 16, &TagNoBidComponents> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoContAmts : public TvpInteger<int64_t, 16, &TagNoContAmts> {
        typedef TvpInteger<int64_t, 16, &TagNoContAmts> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoAffectedOrders : public TvpInteger<int64_t, 16, &TagNoAffectedOrders> {
        typedef TvpInteger<int64_t, 16, &TagNoAffectedOrders> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoClearingInstructions : public TvpInteger<int64_t, 16, &TagNoClearingInstructions> {
        typedef TvpInteger<int64_t, 16, &TagNoClearingInstructions> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoAltMDSource : public TvpInteger<int64_t, 16, &TagNoAltMDSource> {
        typedef TvpInteger<int64_t, 16, &TagNoAltMDSource> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoCapacities : public TvpInteger<int64_t, 16, &TagNoCapacities> {
        typedef TvpInteger<int64_t, 16, &TagNoCapacities> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoCollInquiryQualifier : public TvpInteger<int64_t, 16, &TagNoCollInquiryQualifier> {
        typedef TvpInteger<int64_t, 16, &TagNoCollInquiryQualifier> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoCompIDs : public TvpInteger<int64_t, 16, &TagNoCompIDs> {
        typedef TvpInteger<int64_t, 16, &TagNoCompIDs> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
    struct NoFills : public TvpInteger<int64_t, 16, &TagNoFills> {
        typedef TvpInteger<int64_t, 16, &TagNoFills> Base;
        int parse(TvpParseData& pd) { int bR = Base::parse(pd); pd.meta = get(); return bR; }
    };
}

#endif

