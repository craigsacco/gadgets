

#pragma once

#include <Gadgets/Devices/IDeviceDriver.hpp>

namespace Gadgets
{
namespace Devices
{
class IDigitalOutputDriver : public virtual IDeviceDriver
{
public:
    virtual void On( std::function<void( DriverResponse )> cb ) = 0;
    virtual void Off( std::function<void( DriverResponse )> cb ) = 0;
    virtual void SetState( bool state, std::function<void( DriverResponse )> cb ) = 0;
    virtual void GetState( std::function<void( DriverResponse, bool )> cb ) = 0;

protected:
    IDigitalOutputDriver() = default;
    ~IDigitalOutputDriver() = default;
};
} // namespace Devices
} // namespace Gadgets
