#ifndef ALIVE_CHECK_RESPONSE_H
#define ALIVE_CHECK_RESPONSE_H

#include "./message.h"

namespace DoipLib
{
    /// @brief DoIP tester alive check response
    class AliveCheckResponse : public Message
    {
    private:
        static const PayloadType cPayloadType{PayloadType::AliveCheckResponse};

        uint16_t mSourceAddress;

    protected:
         void GetPayload(std::vector<uint8_t> &payload) override;

         virtual bool TrySetPayload(const std::vector<uint8_t> &payload) override;
         
    public:
        AliveCheckResponse() noexcept;
        
        /// @brief Constructor
        /// @param protocolVersion DoIP ISO protocol version
        /// @param sourceAddress Tester logical address
        explicit AliveCheckResponse(
            uint16_t protocolVersion, uint16_t sourceAddress) noexcept;

        /// @brief Get source address
        /// @return Tester logical address
        uint16_t GetSourceAddress() const noexcept;
    };
}

#endif