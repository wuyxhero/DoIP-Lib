#include "doiplib/generic_nack.h"
#include "doiplib/convert.h"

namespace DoipLib
{
    const PayloadType GenericNack::cPayloadType;

    GenericNack::GenericNack() noexcept : Message(cPayloadType)
    {
    }

    GenericNack::GenericNack(
        uint16_t protocolVersion,
        GenericNackType nackCode) noexcept : Message(protocolVersion, cPayloadType),
                                      mNackCode{nackCode}
    {
    }

    void GenericNack::GetPayload(std::vector<uint8_t> &payload)
    {
        auto _nackCodeByte{static_cast<uint8_t>(mNackCode)};
        payload.insert(payload.begin(), _nackCodeByte);
    }

    bool GenericNack::TrySetPayload(const std::vector<uint8_t> &payload)
    {
        const std::size_t cExpectedSize{cHeaderSize + sizeof(GenericNackType)};
        std::size_t _offset{cHeaderSize};

        if (payload.size() == cExpectedSize)
        {
            mNackCode = Convert::ToEnum<GenericNackType>(payload, _offset);
            return true;
        }
        else
        {
            return false;
        }
    }

    GenericNackType GenericNack::GetNackCode() const noexcept
    {
        return mNackCode;
    }
}