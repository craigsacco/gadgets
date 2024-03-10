

#include <Gadgets/Drivers/EmulatedDigitalOutputDriver.hpp>

namespace Gadgets
{
    namespace Drivers
    {
        EmulatedDigitalOutputDriver::EmulatedDigitalOutputDriver( const std::string& name )
            : BaseDeviceDriver( name, "EmulatedDigitalOutputDriver" ), m_state( false )
        {
        }

        EmulatedDigitalOutputDriver::~EmulatedDigitalOutputDriver() {}

        void
        EmulatedDigitalOutputDriver::Initialise( std::function<void( Devices::DriverResponse )> cb )
        {
            Off( cb );
        }

        void
        EmulatedDigitalOutputDriver::Shutdown( std::function<void( Devices::DriverResponse )> cb )
        {
            Off( cb );
        }

        void
        EmulatedDigitalOutputDriver::On( std::function<void( Devices::DriverResponse )> cb )
        {
            m_state = true;
            cb( Devices::StandardDriverResponses::DriverOK );
        }

        void
        EmulatedDigitalOutputDriver::Off( std::function<void( Devices::DriverResponse )> cb )
        {
            m_state = false;
            cb( Devices::StandardDriverResponses::DriverOK );
        }

        void
        EmulatedDigitalOutputDriver::SetState( bool state, std::function<void( Devices::DriverResponse )> cb )
        {
            m_state = state;
            cb( Devices::StandardDriverResponses::DriverOK );
        }

        void
        EmulatedDigitalOutputDriver::GetState( std::function<void( Devices::DriverResponse, bool )> cb )
        {
            cb( Devices::StandardDriverResponses::DriverOK, m_state );
        }
    } // namespace Drivers
} // namespace Gadgets