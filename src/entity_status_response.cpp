#include "doiplib/entity_status_response.h"
#include "doiplib/convert.h"

namespace DoipLib
{
    const PayloadType EntityStatusResponse::cPayloadType;

    EntityStatusResponse::EntityStatusResponse() noexcept : Message(cPayloadType)
    {
    }

    EntityStatusResponse::EntityStatusResponse(
        uint16_t protocolVersion,
        NodeType entityType,
        uint8_t maxOpenSockets,
        uint8_t currentlyOpenSocket,
        bool hasMaxDataSize,
        uint32_t maxDataSize) noexcept : Message(protocolVersion, cPayloadType),
                                         mEntityType{entityType},
                                         mMaxOpenSockets{maxOpenSockets},
                                         mCurrentlyOpenSocket{currentlyOpenSocket},
                                         mHasMaxDataSize{hasMaxDataSize},
                                         mMaxDataSize{maxDataSize}
    {
    }

    EntityStatusResponse::EntityStatusResponse(
        uint16_t protocolVersion,
        NodeType entityType,
        uint8_t maxOpenSockets,
        uint8_t currentlyOpenSocket) noexcept : EntityStatusResponse(protocolVersion, entityType, maxOpenSockets, currentlyOpenSocket, false)
    {
    }

    EntityStatusResponse::EntityStatusResponse(
        uint16_t protocolVersion,
        NodeType entityType,
        uint8_t maxOpenSockets,
        uint8_t currentlyOpenSocket,
        uint32_t maxDataSize) noexcept : EntityStatusResponse(protocolVersion, entityType, maxOpenSockets, currentlyOpenSocket, true, maxDataSize)
    {
    }

    void EntityStatusResponse::GetPayload(std::vector<uint8_t> &payload)
    {
        if (mHasMaxDataSize)
        {
            Convert::ToByteVector<uint32_t>(mMaxDataSize, payload);
        }

        payload.insert(payload.begin(), mCurrentlyOpenSocket);

        payload.insert(payload.begin(), mMaxOpenSockets);

        auto _entityTypeByte{static_cast<uint8_t>(mEntityType)};
        payload.insert(payload.begin(), _entityTypeByte);
    }

    void EntityStatusResponse::SetPayload(const std::vector<uint8_t> &payload)
    {
        std::size_t _offset{cHeaderSize};

        mEntityType = Convert::ToEnum<NodeType>(payload, _offset);
        mMaxOpenSockets = Convert::ToUnsignedInteger<uint8_t>(payload, _offset);
        mCurrentlyOpenSocket = Convert::ToUnsignedInteger<uint8_t>(payload, _offset);
    }

    bool EntityStatusResponse::TrySetPayload(const std::vector<uint8_t> &payload)
    {
        const std::size_t cExpectedSizeMin{
            static_cast<std::size_t>(cHeaderSize + 3)};
        const std::size_t cExpectedSizeMax{
            static_cast<std::size_t>(cHeaderSize + 7)};
        std::size_t _offset{cExpectedSizeMin};

        if (payload.size() == cExpectedSizeMin)
        {
            SetPayload(payload);
            // No maximum data size field
            mHasMaxDataSize = false;

            return true;
        }
        else if (payload.size() == cExpectedSizeMax)
        {
            SetPayload(payload);
            // Has maximum data size field
            mHasMaxDataSize = true;
            mMaxDataSize =
                Convert::ToUnsignedInteger<uint32_t>(payload, _offset);

            return true;
        }
        else
        {
            return false;
        }
    }

    NodeType EntityStatusResponse::GetEntityType() const noexcept
    {
        return mEntityType;
    }

    uint8_t EntityStatusResponse::GetMaxOpenSockets() const noexcept
    {
        return mMaxOpenSockets;
    }

    uint8_t EntityStatusResponse::GetCurrentlyOpenSocket() const noexcept
    {
        return mCurrentlyOpenSocket;
    }

    bool EntityStatusResponse::TryGetMaxDataSize(uint32_t &maxDataSize) const noexcept
    {
        if (mHasMaxDataSize)
        {
            maxDataSize = mMaxDataSize;
            return true;
        }
        else
        {
            return false;
        }
    }
}
