/**
* @file fixate/fixdatetime.hpp
* @author Mrityunjay Tripathi
*
* fixate is free software; you may redistribute it and/or modify it under the
* terms of the BSD 2-Clause "Simplified" License. You should have received a copy of the
* BSD 2-Clause "Simplified" License along with fixate. If not, see
* http://www.opensource.org/licenses/BSD-2-Clause for more information.
*
* Copyright (c) 2025, Mrityunjay Tripathi
*/
#ifndef FIXATE_FIXMESSAGE_HPP_
#define FIXATE_FIXMESSAGE_HPP_

#include "fixate/fixbase.hpp"
#include "fixate/fixtags.hpp"

namespace fixate {

    enum class FixVersionType {
        FIX_4_0,
        FIX_4_1,
        FIX_4_2,
        FIX_4_3,
        FIX_4_4,
        FIX_5_0
    };

    template <FixVersionType FixVersion> struct FixVersionTag { using type = void; };
    template <> struct FixVersionTag<FixVersionType::FIX_4_0> { using type = FixVersion_4_0; };
    template <> struct FixVersionTag<FixVersionType::FIX_4_1> { using type = FixVersion_4_1; };
    template <> struct FixVersionTag<FixVersionType::FIX_4_2> { using type = FixVersion_4_2; };
    template <> struct FixVersionTag<FixVersionType::FIX_4_3> { using type = FixVersion_4_3; };
    template <> struct FixVersionTag<FixVersionType::FIX_4_4> { using type = FixVersion_4_4; };
    template <> struct FixVersionTag<FixVersionType::FIX_5_0> { using type = FixVersion_5_0; };

    template <typename Target, typename First, typename ... Rest>
    struct IsLeader { static constexpr bool value = std::is_same_v<Target, typename LeaderTvpType<First>::type>; };

    template <typename Target, typename First, typename ... Rest>
    constexpr bool IsLeaderV = IsLeader<Target, First, Rest...>::value;

    template <FixVersionType FixVersion, typename ... TvpTypes>
    class FixMessage
    {
        static_assert(
            CheckUniqueV<FixVersionTag<FixVersion>, BodyLength, TvpTypes..., CheckSum>,
            "Tag-Value Pair must be unique in message."
        );
        static_assert(
            IsLeaderV<MessageType, TvpTypes...>,
            "The FIX Message body must start with `MessageType`."
        );
    public:
        FixMessage() : mBodyLen(0) {}

        template <typename TvpType, typename ... TArgs, typename ... Args>
        void resize(Args&& ... args) { return mMsgBody.template resize<TvpType, TArgs...>(std::forward<Args>(args)...); }

        template <typename TvpType, typename ... TArgs, typename ... Args>
        auto get(Args&& ... args) const { return mMsgBody.template get<TvpType, TArgs...>(std::forward<Args>(args)...); }

        template <typename TvpType, typename ... TArgs, typename ... Args>
        void set(Args&& ... args) { return mMsgBody.template set<TvpType, TArgs...>(std::forward<Args>(args)...); }

        int getBodyLength() { return mBodyLen; }

        int updateBodyLength() {
            mBodyLen = mMsgBody.width();
            mMsgHeader.template set<BodyLength>(mBodyLen);
            return mBodyLen;
        }

        void updateCheckSum() {
            uint8_t checksum = mMsgHeader.sum() + mMsgBody.sum();
            mMsgTrailer.set<CheckSum>(checksum);
        }

        int dump(char* dest, bool setBodyLength = false, bool setCheckSum = false) {
            if (setBodyLength) updateBodyLength();
            if (setCheckSum) updateCheckSum();
            int bW = mMsgHeader.dump(dest);
            bW += mMsgBody.dump(dest + bW);
            bW += mMsgTrailer.dump(dest + bW);
            return bW;
        }

        int parse(const char* src) {
            int bR = mMsgHeader.parse(src);
            bR += mMsgBody.parse(src + bR);
            bR += mMsgTrailer.parse(src + bR);
            return bR;
        }

    private:
        TvpGroup<typename FixVersionTag<FixVersion>::type, BodyLength> mMsgHeader;
        TvpGroup<TvpTypes ...> mMsgBody;
        TvpGroup<CheckSum> mMsgTrailer;
        int mBodyLen;
    };
}

#endif

