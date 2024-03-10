

#pragma once

#include <cstdint>

namespace Gadgets
{
    namespace Devices
    {
        using DriverResponse = uint32_t;

        namespace StandardDriverResponses
        {
            static constexpr DriverResponse DriverOK = 0;
            static constexpr DriverResponse DriverFailed = 1;
        }; // namespace StandardDriverResponses
    }      // namespace Devices
} // namespace Gadgets
