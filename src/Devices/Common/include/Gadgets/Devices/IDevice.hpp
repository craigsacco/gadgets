

#pragma once

#include <Gadgets/Core/IObject.hpp>
#include <Gadgets/Devices/DeviceResponse.hpp>

#include <chrono>
#include <string>

namespace Gadgets
{
namespace Devices
{
class IDevice : public virtual Core::IObject
{
public:
    virtual void Initialise() = 0;
    virtual void Shutdown() = 0;
    virtual void Wait() = 0;
    virtual void Wait( std::chrono::milliseconds timeout_ms ) = 0;

    virtual std::string Name() const = 0;

protected:
    IDevice() = default;
    ~IDevice() = default;
};
} // namespace Devices
} // namespace Gadgets
