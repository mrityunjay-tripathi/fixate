/**
* @file fixate/fixmsgtype.hpp
* @author Mrityunjay Tripathi
*
* fixate is free software; you may redistribute it and/or modify it under the
* terms of the BSD 2-Clause "Simplified" License. You should have received a copy of the
* BSD 2-Clause "Simplified" License along with fixate. If not, see
* http://www.opensource.org/licenses/BSD-2-Clause for more information.
*
* Copyright (c) 2025, Mrityunjay Tripathi
*/
#ifndef FIXATE_FIX_MSG_TYPE_HPP_
#define FIXATE_FIX_MSG_TYPE_HPP_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsubobject-linkage"

#include "fixate/fixbase.hpp"

namespace fixate {

    //! Note: I might need to change enum type from uint8_t to uint16_t
    //        as more number of message types are added.
    enum class MessageTypeEnum : uint8_t
    {
        Heartbeat = 0,
        TestRequest,
        ResendRequest,
        Reject,
        SequenceReset,
        Logout,
        IOI,
        Advertisement,
        ExecutionReport,
        OrderCancelReject,
        QuoteStatusRequest,
        Logon,
        DerivativeSecurityList,
        NewOrderMultileg,
        MultilegOrderCancelReplace,
        TradeCaptureReportRequest,
        TradeCaptureReport,
        OrderMassStatusRequest,
        QuoteRequestReject,
        RFQRequest,
        QuoteStatusReport,
        QuoteResponse,
        Confirmation,
        PositionMaintenanceRequest,
        PositionMaintenanceReport,
        RequestForPositions,
        RequestForPositionsAck,
        PositionReport,
        TradeCaptureReportRequestAck,
        TradeCaptureReportAck,
        AllocationReport,
        AllocationReportAck,
        ConfirmationAck,
        SettlementInstructionRequest,
        AssignmentReport,
        CollateralRequest,
        CollateralAssignment,
        CollateralResponse,
        MassQuoteAcknowledgement,
        News,
        CollateralReport,
        CollateralInquiry,
        NetworkCounterpartySystemStatusRequest,
        NetworkCounterpartySystemStatusResponse,
        UserRequest,
        UserResponse,
        CollateralInquiryAck,
        ConfirmationRequest,
        SecurityDefinitionRequest,
        Email,
        SecurityDefinition,
        NewOrderSingle,
        SecurityStatusRequest,
        NewOrderList,
        SecurityStatus,
        OrderCancelRequest,
        TradingSessionStatusRequest,
        OrderCancelReplaceRequest,
        TradingSessionStatus,
        OrderStatusRequest,
        MassQuote,
        BusinessMessageReject,
        AllocationInstruction,
        BidRequest,
        ListCancelRequest,
        BidResponse,
        ListExecute,
        ListStrikePrice,
        ListStatusRequest,
        XMLMessage,
        ListStatus,
        RegistrationInstructions,
        RegistrationInstructionsResponse,
        AllocationInstructionAck,
        OrderMassCancelRequest,
        DontKnowTrade,
        OrderMassCancelReport,
        QuoteRequest,
        NewOrderCross,
        Quote,
        CrossOrderCancelReplaceRequest,
        SettlementInstructions,
        CrossOrderCancelRequest,
        SecurityTypeRequest,
        MarketDataRequest,
        SecurityTypes,
        MarketDataSnapshotFullRefresh,
        SecurityListRequest,
        MarketDataIncrementalRefresh,
        SecurityList,
        MarketDataRequestReject,
        DerivativeSecurityListRequest,
        QuoteCancel,
    };

    static constexpr const char* M_Heartbeat = "0";
    static constexpr const char* M_TestRequest = "1";
    static constexpr const char* M_ResendRequest = "2";
    static constexpr const char* M_Reject = "3";
    static constexpr const char* M_SequenceReset = "4";
    static constexpr const char* M_Logout = "5";
    static constexpr const char* M_IOI = "6";
    static constexpr const char* M_Advertisement = "7";
    static constexpr const char* M_ExecutionReport = "8";
    static constexpr const char* M_OrderCancelReject = "9";
    static constexpr const char* M_QuoteStatusRequest = "a";
    static constexpr const char* M_Logon = "A";
    static constexpr const char* M_DerivativeSecurityList = "AA";
    static constexpr const char* M_NewOrderMultileg = "AB";
    static constexpr const char* M_MultilegOrderCancelReplace = "AC";
    static constexpr const char* M_TradeCaptureReportRequest = "AD";
    static constexpr const char* M_TradeCaptureReport = "AE";
    static constexpr const char* M_OrderMassStatusRequest = "AF";
    static constexpr const char* M_QuoteRequestReject = "AG";
    static constexpr const char* M_RFQRequest = "AH";
    static constexpr const char* M_QuoteStatusReport = "AI";
    static constexpr const char* M_QuoteResponse = "AJ";
    static constexpr const char* M_Confirmation = "AK";
    static constexpr const char* M_PositionMaintenanceRequest = "AL";
    static constexpr const char* M_PositionMaintenanceReport = "AM";
    static constexpr const char* M_RequestForPositions = "AN";
    static constexpr const char* M_RequestForPositionsAck = "AO";
    static constexpr const char* M_PositionReport = "AP";
    static constexpr const char* M_TradeCaptureReportRequestAck = "AQ";
    static constexpr const char* M_TradeCaptureReportAck = "AR";
    static constexpr const char* M_AllocationReport = "AS";
    static constexpr const char* M_AllocationReportAck = "AT";
    static constexpr const char* M_ConfirmationAck = "AU";
    static constexpr const char* M_SettlementInstructionRequest = "AV";
    static constexpr const char* M_AssignmentReport = "AW";
    static constexpr const char* M_CollateralRequest = "AX";
    static constexpr const char* M_CollateralAssignment = "AY";
    static constexpr const char* M_CollateralResponse = "AZ";
    static constexpr const char* M_MassQuoteAcknowledgement = "b";
    static constexpr const char* M_News = "B";
    static constexpr const char* M_CollateralReport = "BA";
    static constexpr const char* M_CollateralInquiry = "BB";
    static constexpr const char* M_NetworkCounterpartySystemStatusRequest = "BC";
    static constexpr const char* M_NetworkCounterpartySystemStatusResponse = "BD";
    static constexpr const char* M_UserRequest = "BE";
    static constexpr const char* M_UserResponse = "BF";
    static constexpr const char* M_CollateralInquiryAck = "BG";
    static constexpr const char* M_ConfirmationRequest = "BH";
    static constexpr const char* M_SecurityDefinitionRequest = "c";
    static constexpr const char* M_Email = "C";
    static constexpr const char* M_SecurityDefinition = "d";
    static constexpr const char* M_NewOrderSingle = "D";
    static constexpr const char* M_SecurityStatusRequest = "e";
    static constexpr const char* M_NewOrderList = "E";
    static constexpr const char* M_SecurityStatus = "f";
    static constexpr const char* M_OrderCancelRequest = "F";
    static constexpr const char* M_TradingSessionStatusRequest = "g";
    static constexpr const char* M_OrderCancelReplaceRequest = "G";
    static constexpr const char* M_TradingSessionStatus = "h";
    static constexpr const char* M_OrderStatusRequest = "H";
    static constexpr const char* M_MassQuote = "i";
    static constexpr const char* M_BusinessMessageReject = "j";
    static constexpr const char* M_AllocationInstruction = "J";
    static constexpr const char* M_BidRequest = "k";
    static constexpr const char* M_ListCancelRequest = "K";
    static constexpr const char* M_BidResponse = "l";
    static constexpr const char* M_ListExecute = "L";
    static constexpr const char* M_ListStrikePrice = "m";
    static constexpr const char* M_ListStatusRequest = "M";
    static constexpr const char* M_XMLMessage = "n";
    static constexpr const char* M_ListStatus = "N";
    static constexpr const char* M_RegistrationInstructions = "o";
    static constexpr const char* M_RegistrationInstructionsResponse = "p";
    static constexpr const char* M_AllocationInstructionAck = "P";
    static constexpr const char* M_OrderMassCancelRequest = "q";
    static constexpr const char* M_DontKnowTrade = "Q";
    static constexpr const char* M_OrderMassCancelReport = "r";
    static constexpr const char* M_QuoteRequest = "R";
    static constexpr const char* M_NewOrderCross = "s";
    static constexpr const char* M_Quote = "S";
    static constexpr const char* M_CrossOrderCancelReplaceRequest = "t";
    static constexpr const char* M_SettlementInstructions = "T";
    static constexpr const char* M_CrossOrderCancelRequest = "u";
    static constexpr const char* M_SecurityTypeRequest = "v";
    static constexpr const char* M_MarketDataRequest = "V";
    static constexpr const char* M_SecurityTypes = "w";
    static constexpr const char* M_MarketDataSnapshotFullRefresh = "W";
    static constexpr const char* M_SecurityListRequest = "x";
    static constexpr const char* M_MarketDataIncrementalRefresh = "X";
    static constexpr const char* M_SecurityList = "y";
    static constexpr const char* M_MarketDataRequestReject = "Y";
    static constexpr const char* M_DerivativeSecurityListRequest = "z";
    static constexpr const char* M_QuoteCancel = "Z";

    namespace details {

        constexpr const std::array<const char*, 96> MessageTypeEnumToString = {
            M_Heartbeat,
            M_TestRequest,
            M_ResendRequest,
            M_Reject,
            M_SequenceReset,
            M_Logout,
            M_IOI,
            M_Advertisement,
            M_ExecutionReport,
            M_OrderCancelReject,
            M_QuoteStatusRequest,
            M_Logon,
            M_DerivativeSecurityList,
            M_NewOrderMultileg,
            M_MultilegOrderCancelReplace,
            M_TradeCaptureReportRequest,
            M_TradeCaptureReport,
            M_OrderMassStatusRequest,
            M_QuoteRequestReject,
            M_RFQRequest,
            M_QuoteStatusReport,
            M_QuoteResponse,
            M_Confirmation,
            M_PositionMaintenanceRequest,
            M_PositionMaintenanceReport,
            M_RequestForPositions,
            M_RequestForPositionsAck,
            M_PositionReport,
            M_TradeCaptureReportRequestAck,
            M_TradeCaptureReportAck,
            M_AllocationReport,
            M_AllocationReportAck,
            M_ConfirmationAck,
            M_SettlementInstructionRequest,
            M_AssignmentReport,
            M_CollateralRequest,
            M_CollateralAssignment,
            M_CollateralResponse,
            M_MassQuoteAcknowledgement,
            M_News,
            M_CollateralReport,
            M_CollateralInquiry,
            M_NetworkCounterpartySystemStatusRequest,
            M_NetworkCounterpartySystemStatusResponse,
            M_UserRequest,
            M_UserResponse,
            M_CollateralInquiryAck,
            M_ConfirmationRequest,
            M_SecurityDefinitionRequest,
            M_Email,
            M_SecurityDefinition,
            M_NewOrderSingle,
            M_SecurityStatusRequest,
            M_NewOrderList,
            M_SecurityStatus,
            M_OrderCancelRequest,
            M_TradingSessionStatusRequest,
            M_OrderCancelReplaceRequest,
            M_TradingSessionStatus,
            M_OrderStatusRequest,
            M_MassQuote,
            M_BusinessMessageReject,
            M_AllocationInstruction,
            M_BidRequest,
            M_ListCancelRequest,
            M_BidResponse,
            M_ListExecute,
            M_ListStrikePrice,
            M_ListStatusRequest,
            M_XMLMessage,
            M_ListStatus,
            M_RegistrationInstructions,
            M_RegistrationInstructionsResponse,
            M_AllocationInstructionAck,
            M_OrderMassCancelRequest,
            M_DontKnowTrade,
            M_OrderMassCancelReport,
            M_QuoteRequest,
            M_NewOrderCross,
            M_Quote,
            M_CrossOrderCancelReplaceRequest,
            M_SettlementInstructions,
            M_CrossOrderCancelRequest,
            M_SecurityTypeRequest,
            M_MarketDataRequest,
            M_SecurityTypes,
            M_MarketDataSnapshotFullRefresh,
            M_SecurityListRequest,
            M_MarketDataIncrementalRefresh,
            M_SecurityList,
            M_MarketDataRequestReject,
            M_DerivativeSecurityListRequest,
            M_QuoteCancel
        };

        template <const char* const* MsgTypeStrRef, size_t Size = strlen(*MsgTypeStrRef)>
        struct MessageTypeHash { enum : uint16_t { value = uint16_t(-1) }; };

        template <const char* const* MsgTypeStrRef>
        struct MessageTypeHash<MsgTypeStrRef, 1> { enum : uint16_t { value = (*MsgTypeStrRef)[0] - 48 }; };

        template <const char* const* MsgTypeStrRef>
        struct MessageTypeHash<MsgTypeStrRef, 2> { enum : uint16_t { value = ((*MsgTypeStrRef)[0] - 48) | ((*MsgTypeStrRef)[1] - 48) << 8 }; };

        inline uint16_t GetMessageTypeHash(const char* str, int strLen) {
            return strLen == 1 ? (str[0] - 48) : (str[0] - 48) | ((str[0] - 48) << 8);
        }

        constexpr const std::array<std::pair<uint16_t, MessageTypeEnum>, 96> MsgTypeHashMap = {
            std::make_pair(MessageTypeHash<&M_MarketDataIncrementalRefresh>::value, MessageTypeEnum::MarketDataIncrementalRefresh),
            std::make_pair(MessageTypeHash<&M_MarketDataSnapshotFullRefresh>::value, MessageTypeEnum::MarketDataSnapshotFullRefresh),
            std::make_pair(MessageTypeHash<&M_Quote>::value, MessageTypeEnum::Quote),
            std::make_pair(MessageTypeHash<&M_ExecutionReport>::value, MessageTypeEnum::ExecutionReport),
            std::make_pair(MessageTypeHash<&M_TradeCaptureReport>::value, MessageTypeEnum::TradeCaptureReport),
            std::make_pair(MessageTypeHash<&M_PositionReport>::value, MessageTypeEnum::PositionReport),
            std::make_pair(MessageTypeHash<&M_QuoteResponse>::value, MessageTypeEnum::QuoteResponse),
            std::make_pair(MessageTypeHash<&M_Heartbeat>::value, MessageTypeEnum::Heartbeat),
            std::make_pair(MessageTypeHash<&M_TestRequest>::value, MessageTypeEnum::TestRequest),
            std::make_pair(MessageTypeHash<&M_ResendRequest>::value, MessageTypeEnum::ResendRequest),
            std::make_pair(MessageTypeHash<&M_Reject>::value, MessageTypeEnum::Reject),
            std::make_pair(MessageTypeHash<&M_SequenceReset>::value, MessageTypeEnum::SequenceReset),
            std::make_pair(MessageTypeHash<&M_Logout>::value, MessageTypeEnum::Logout),
            std::make_pair(MessageTypeHash<&M_IOI>::value, MessageTypeEnum::IOI),
            std::make_pair(MessageTypeHash<&M_Advertisement>::value, MessageTypeEnum::Advertisement),
            std::make_pair(MessageTypeHash<&M_OrderCancelReject>::value, MessageTypeEnum::OrderCancelReject),
            std::make_pair(MessageTypeHash<&M_QuoteStatusRequest>::value, MessageTypeEnum::QuoteStatusRequest),
            std::make_pair(MessageTypeHash<&M_Logon>::value, MessageTypeEnum::Logon),
            std::make_pair(MessageTypeHash<&M_DerivativeSecurityList>::value, MessageTypeEnum::DerivativeSecurityList),
            std::make_pair(MessageTypeHash<&M_NewOrderMultileg>::value, MessageTypeEnum::NewOrderMultileg),
            std::make_pair(MessageTypeHash<&M_MultilegOrderCancelReplace>::value, MessageTypeEnum::MultilegOrderCancelReplace),
            std::make_pair(MessageTypeHash<&M_TradeCaptureReportRequest>::value, MessageTypeEnum::TradeCaptureReportRequest),
            std::make_pair(MessageTypeHash<&M_OrderMassStatusRequest>::value, MessageTypeEnum::OrderMassStatusRequest),
            std::make_pair(MessageTypeHash<&M_QuoteRequestReject>::value, MessageTypeEnum::QuoteRequestReject),
            std::make_pair(MessageTypeHash<&M_RFQRequest>::value, MessageTypeEnum::RFQRequest),
            std::make_pair(MessageTypeHash<&M_QuoteStatusReport>::value, MessageTypeEnum::QuoteStatusReport),
            std::make_pair(MessageTypeHash<&M_Confirmation>::value, MessageTypeEnum::Confirmation),
            std::make_pair(MessageTypeHash<&M_PositionMaintenanceRequest>::value, MessageTypeEnum::PositionMaintenanceRequest),
            std::make_pair(MessageTypeHash<&M_PositionMaintenanceReport>::value, MessageTypeEnum::PositionMaintenanceReport),
            std::make_pair(MessageTypeHash<&M_RequestForPositions>::value, MessageTypeEnum::RequestForPositions),
            std::make_pair(MessageTypeHash<&M_RequestForPositionsAck>::value, MessageTypeEnum::RequestForPositionsAck),
            std::make_pair(MessageTypeHash<&M_TradeCaptureReportRequestAck>::value, MessageTypeEnum::TradeCaptureReportRequestAck),
            std::make_pair(MessageTypeHash<&M_TradeCaptureReportAck>::value, MessageTypeEnum::TradeCaptureReportAck),
            std::make_pair(MessageTypeHash<&M_AllocationReport>::value, MessageTypeEnum::AllocationReport),
            std::make_pair(MessageTypeHash<&M_AllocationReportAck>::value, MessageTypeEnum::AllocationReportAck),
            std::make_pair(MessageTypeHash<&M_ConfirmationAck>::value, MessageTypeEnum::ConfirmationAck),
            std::make_pair(MessageTypeHash<&M_SettlementInstructionRequest>::value, MessageTypeEnum::SettlementInstructionRequest),
            std::make_pair(MessageTypeHash<&M_AssignmentReport>::value, MessageTypeEnum::AssignmentReport),
            std::make_pair(MessageTypeHash<&M_CollateralRequest>::value, MessageTypeEnum::CollateralRequest),
            std::make_pair(MessageTypeHash<&M_CollateralAssignment>::value, MessageTypeEnum::CollateralAssignment),
            std::make_pair(MessageTypeHash<&M_CollateralResponse>::value, MessageTypeEnum::CollateralResponse),
            std::make_pair(MessageTypeHash<&M_MassQuoteAcknowledgement>::value, MessageTypeEnum::MassQuoteAcknowledgement),
            std::make_pair(MessageTypeHash<&M_News>::value, MessageTypeEnum::News),
            std::make_pair(MessageTypeHash<&M_CollateralReport>::value, MessageTypeEnum::CollateralReport),
            std::make_pair(MessageTypeHash<&M_CollateralInquiry>::value, MessageTypeEnum::CollateralInquiry),
            std::make_pair(MessageTypeHash<&M_NetworkCounterpartySystemStatusRequest>::value, MessageTypeEnum::NetworkCounterpartySystemStatusRequest),
            std::make_pair(MessageTypeHash<&M_NetworkCounterpartySystemStatusResponse>::value, MessageTypeEnum::NetworkCounterpartySystemStatusResponse),
            std::make_pair(MessageTypeHash<&M_UserRequest>::value, MessageTypeEnum::UserRequest),
            std::make_pair(MessageTypeHash<&M_UserResponse>::value, MessageTypeEnum::UserResponse),
            std::make_pair(MessageTypeHash<&M_CollateralInquiryAck>::value, MessageTypeEnum::CollateralInquiryAck),
            std::make_pair(MessageTypeHash<&M_ConfirmationRequest>::value, MessageTypeEnum::ConfirmationRequest),
            std::make_pair(MessageTypeHash<&M_SecurityDefinitionRequest>::value, MessageTypeEnum::SecurityDefinitionRequest),
            std::make_pair(MessageTypeHash<&M_Email>::value, MessageTypeEnum::Email),
            std::make_pair(MessageTypeHash<&M_SecurityDefinition>::value, MessageTypeEnum::SecurityDefinition),
            std::make_pair(MessageTypeHash<&M_NewOrderSingle>::value, MessageTypeEnum::NewOrderSingle),
            std::make_pair(MessageTypeHash<&M_SecurityStatusRequest>::value, MessageTypeEnum::SecurityStatusRequest),
            std::make_pair(MessageTypeHash<&M_NewOrderList>::value, MessageTypeEnum::NewOrderList),
            std::make_pair(MessageTypeHash<&M_SecurityStatus>::value, MessageTypeEnum::SecurityStatus),
            std::make_pair(MessageTypeHash<&M_OrderCancelRequest>::value, MessageTypeEnum::OrderCancelRequest),
            std::make_pair(MessageTypeHash<&M_TradingSessionStatusRequest>::value, MessageTypeEnum::TradingSessionStatusRequest),
            std::make_pair(MessageTypeHash<&M_OrderCancelReplaceRequest>::value, MessageTypeEnum::OrderCancelReplaceRequest),
            std::make_pair(MessageTypeHash<&M_TradingSessionStatus>::value, MessageTypeEnum::TradingSessionStatus),
            std::make_pair(MessageTypeHash<&M_OrderStatusRequest>::value, MessageTypeEnum::OrderStatusRequest),
            std::make_pair(MessageTypeHash<&M_MassQuote>::value, MessageTypeEnum::MassQuote),
            std::make_pair(MessageTypeHash<&M_BusinessMessageReject>::value, MessageTypeEnum::BusinessMessageReject),
            std::make_pair(MessageTypeHash<&M_AllocationInstruction>::value, MessageTypeEnum::AllocationInstruction),
            std::make_pair(MessageTypeHash<&M_BidRequest>::value, MessageTypeEnum::BidRequest),
            std::make_pair(MessageTypeHash<&M_ListCancelRequest>::value, MessageTypeEnum::ListCancelRequest),
            std::make_pair(MessageTypeHash<&M_BidResponse>::value, MessageTypeEnum::BidResponse),
            std::make_pair(MessageTypeHash<&M_ListExecute>::value, MessageTypeEnum::ListExecute),
            std::make_pair(MessageTypeHash<&M_ListStrikePrice>::value, MessageTypeEnum::ListStrikePrice),
            std::make_pair(MessageTypeHash<&M_ListStatusRequest>::value, MessageTypeEnum::ListStatusRequest),
            std::make_pair(MessageTypeHash<&M_XMLMessage>::value, MessageTypeEnum::XMLMessage),
            std::make_pair(MessageTypeHash<&M_ListStatus>::value, MessageTypeEnum::ListStatus),
            std::make_pair(MessageTypeHash<&M_RegistrationInstructions>::value, MessageTypeEnum::RegistrationInstructions),
            std::make_pair(MessageTypeHash<&M_RegistrationInstructionsResponse>::value, MessageTypeEnum::RegistrationInstructionsResponse),
            std::make_pair(MessageTypeHash<&M_AllocationInstructionAck>::value, MessageTypeEnum::AllocationInstructionAck),
            std::make_pair(MessageTypeHash<&M_OrderMassCancelRequest>::value, MessageTypeEnum::OrderMassCancelRequest),
            std::make_pair(MessageTypeHash<&M_DontKnowTrade>::value, MessageTypeEnum::DontKnowTrade),
            std::make_pair(MessageTypeHash<&M_OrderMassCancelReport>::value, MessageTypeEnum::OrderMassCancelReport),
            std::make_pair(MessageTypeHash<&M_QuoteRequest>::value, MessageTypeEnum::QuoteRequest),
            std::make_pair(MessageTypeHash<&M_NewOrderCross>::value, MessageTypeEnum::NewOrderCross),
            std::make_pair(MessageTypeHash<&M_CrossOrderCancelReplaceRequest>::value, MessageTypeEnum::CrossOrderCancelReplaceRequest),
            std::make_pair(MessageTypeHash<&M_SettlementInstructions>::value, MessageTypeEnum::SettlementInstructions),
            std::make_pair(MessageTypeHash<&M_CrossOrderCancelRequest>::value, MessageTypeEnum::CrossOrderCancelRequest),
            std::make_pair(MessageTypeHash<&M_SecurityTypeRequest>::value, MessageTypeEnum::SecurityTypeRequest),
            std::make_pair(MessageTypeHash<&M_MarketDataRequest>::value, MessageTypeEnum::MarketDataRequest),
            std::make_pair(MessageTypeHash<&M_SecurityTypes>::value, MessageTypeEnum::SecurityTypes),
            std::make_pair(MessageTypeHash<&M_SecurityListRequest>::value, MessageTypeEnum::SecurityListRequest),
            std::make_pair(MessageTypeHash<&M_SecurityList>::value, MessageTypeEnum::SecurityList),
            std::make_pair(MessageTypeHash<&M_MarketDataRequestReject>::value, MessageTypeEnum::MarketDataRequestReject),
            std::make_pair(MessageTypeHash<&M_DerivativeSecurityListRequest>::value, MessageTypeEnum::DerivativeSecurityListRequest),
            std::make_pair(MessageTypeHash<&M_QuoteCancel>::value, MessageTypeEnum::QuoteCancel)
        };
    }
    inline MessageTypeEnum MsgTypeStringToEnum(const char* str, int strLen) {
        uint16_t h = details::GetMessageTypeHash(str, strLen);
        for (size_t i = 0; i < details::MsgTypeHashMap.max_size(); ++i) {
            const auto& p = details::MsgTypeHashMap[i];
            if (p.first == h) return p.second;
        }
        return MessageTypeEnum(-1);
    }
    inline MessageTypeEnum MsgTypeStringToEnum(std::string_view str) {
        return MsgTypeStringToEnum(str.data(), (int)str.size());
    }
    inline MessageTypeEnum MsgTypeStringToEnum(const std::string& str) {
        return MsgTypeStringToEnum(str.c_str(), (int)str.size());
    }
}

#endif


