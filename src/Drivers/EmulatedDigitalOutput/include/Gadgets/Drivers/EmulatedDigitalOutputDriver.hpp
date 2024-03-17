

#pragma once

#include <Gadgets/Devices/IDigitalOutputDriver.hpp>
#include <Gadgets/Drivers/BaseDeviceDriver.hpp>

#if defined( _MSC_VER )
// methods inherited by dominance are fine - inhibit this warning (cleared at end
// of file)
#pragma warning( push )
#pragma warning( disable : 4250 )
#endif

namespace Gadgets
{
namespace Drivers
{
class EmulatedDigitalOutputDriver
    : public BaseDeviceDriver
    , public virtual Devices::IDigitalOutputDriver
{
public:
    EmulatedDigitalOutputDriver( const std::string& name );
    virtual ~EmulatedDigitalOutputDriver();

    // overrides from IDeviceDriver
    void Initialise( std::function<void( Devices::DriverResponse )> cb ) override final;
    void Shutdown( std::function<void( Devices::DriverResponse )> cb ) override final;

    // overrides from IDigitalOutputDriver
    void On( std::function<void( Devices::DriverResponse )> cb ) override final;
    void Off( std::function<void( Devices::DriverResponse )> cb ) override final;
    void SetState( bool state, std::function<void( Devices::DriverResponse )> cb ) override final;
    void GetState( std::function<void( Devices::DriverResponse, bool )> cb ) override final;

private:
    bool m_state;
};
} // namespace Drivers
} // namespace Gadgets

#if defined( _MSC_VER )
#pragma warning( pop )
#endif
