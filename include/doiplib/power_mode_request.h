#ifndef POWER_MODE_REQUEST_H
#define POWER_MODE_REQUEST_H

#include "./message.h"

namespace DoipLib
{
    /// @brief Diagnostic node power mode information request
    class PowerModeRequest : public Message
    {
    private:
        static const PayloadType cPayloadType{
            PayloadType::DiagPowerModeInfoRequest};

    protected:
         void GetPayload(std::vector<uint8_t> &payload) override;

         virtual bool TrySetPayload(const std::vector<uint8_t> &payload) override;
         
    public:
        PowerModeRequest() noexcept;
        
        /// @brief Constructor
        /// @param protocolVersion DoIP ISO protocol version
        explicit PowerModeRequest(uint16_t protocolVersion) noexcept;
    };
}

#endif