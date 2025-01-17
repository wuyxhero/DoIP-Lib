#include <stdexcept>
#include <utility>
#include "doiplib/vin_vehicle_id_request.h"
#include "doiplib/convert.h"

namespace DoipLib
{
    const PayloadType VinVehicleIdRequest::cPayloadType;
    const std::size_t VinVehicleIdRequest::cVinSize;

    VinVehicleIdRequest::VinVehicleIdRequest() noexcept : Message(cPayloadType)
    {
    }

    VinVehicleIdRequest::VinVehicleIdRequest(
        uint16_t protocolVersion, const std::string &vin) : Message(protocolVersion, cPayloadType),
                                                     mVin{vin.size() == cVinSize ? vin : throw std::out_of_range("Invalid vehicle ID number")}
    {
    }

    VinVehicleIdRequest::VinVehicleIdRequest(
        uint16_t protocolVersion, std::string &&vin) : Message(protocolVersion, cPayloadType),
                                                       mVin{vin.size() == cVinSize ? std::move(vin) : throw std::out_of_range("Invalid vehicle ID number")}
    {
    }

    void VinVehicleIdRequest::GetPayload(std::vector<uint8_t> &payload)
    {
        payload = std::vector<uint8_t>(mVin.cbegin(), mVin.cend());
    }

    bool VinVehicleIdRequest::TrySetPayload(const std::vector<uint8_t> &payload)
    {
        const std::size_t cExpectedSize{
            static_cast<std::size_t>(cHeaderSize + cVinSize)};

        if (payload.size() == cExpectedSize)
        {
            std::size_t _offset{cHeaderSize};
            mVin = Convert::ToString<cVinSize>(payload, _offset);

            return true;
        }
        else
        {
            return false;
        }
    }

    std::string VinVehicleIdRequest::GetVin() const
    {
        return mVin;
    }
}