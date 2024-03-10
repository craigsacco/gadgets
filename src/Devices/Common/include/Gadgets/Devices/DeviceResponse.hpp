

#pragma once

#include <cstdint>

namespace Gadgets
{
namespace Devices
{
using DeviceResponse = uint32_t;

namespace StandardDeviceResponses
{
static constexpr DeviceResponse DeviceOK = 0;
static constexpr DeviceResponse DeviceFailed = 1;
}; // namespace StandardDeviceResponses
} // namespace Devices
} // namespace Gadgets
