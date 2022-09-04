#include <array>
#include <iterator>
#include <algorithm>
#include <gtest/gtest.h>
#include <doiplib/generic_nack.h>

namespace DoipLib
{
    TEST(GenericNackTest, NackCodeProperty)
    {
        const uint8_t cProtocolVersion{0x02};
        const NackType cExpectedResult{NackType::InvalidProtocolVersion};

        GenericNack _message(cProtocolVersion, cExpectedResult);
        NackType _actualResult{_message.GetNackCode()};

        EXPECT_EQ(cExpectedResult, _actualResult);
    }

    TEST(GenericNackTest, Serialization)
    {
        const uint8_t cProtocolVersion{0x02};
        const NackType cNackCode{NackType::InvalidPayloadLength};
        const std::size_t cPayloadLength{9};
        const std::array<uint8_t, cPayloadLength> cExpectedResult{
            0x02, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04};

        GenericNack _message(cProtocolVersion, cNackCode);
        std::vector<uint8_t> _actualResult;
        _message.Serialize(_actualResult);

        bool _areEqual =
            std::equal(
                std::cbegin(cExpectedResult),
                std::cend(cExpectedResult),
                std::cbegin(_actualResult));
        EXPECT_TRUE(_areEqual);
    }

    TEST(GenericNackTest, ValidDeserialization)
    {
        const NackType cExpectedResult{NackType::InvalidPayloadLength};
        const std::vector<uint8_t> cSerializedMessage{
            0x02, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04};

        GenericNack _message;
        bool _succeed{_message.TryDeserialize(cSerializedMessage)};
        EXPECT_TRUE(_succeed);

        NackType _actualResult{_message.GetNackCode()};
        EXPECT_EQ(cExpectedResult, _actualResult);
    }

    TEST(GenericNackTest, InvalidDeserialization)
    {
        const std::vector<uint8_t> cSerializedMessage{
            0x02, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

        GenericNack _message;
        bool _succeed{_message.TryDeserialize(cSerializedMessage)};
        EXPECT_FALSE(_succeed);
    }
}