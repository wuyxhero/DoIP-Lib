#include "doiplib/power_mode_request.h"

namespace DoipLib
{
    const PayloadType PowerModeRequest::cPayloadType;

    PowerModeRequest::PowerModeRequest() noexcept : Message(cPayloadType)
    {
    }


    PowerModeRequest::PowerModeRequest(
        uint16_t protocolVersion) noexcept : Message(protocolVersion, cPayloadType)
    {
    }

    void PowerModeRequest::GetPayload(std::vector<uint8_t> &payload)
    {
        // The message contain no payload.
    }

    bool PowerModeRequest::TrySetPayload(const std::vector<uint8_t> &payload)
    {
        // The message contain no payload.
        return true;
    }
}