

#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Devices/DigitalOutputDevice.hpp>
#include <Gadgets/Devices/IDigitalOutputDriver.hpp>

namespace Gadgets
{
namespace Devices
{
DigitalOutputDevice::DigitalOutputDevice( const std::string& name, IDigitalOutputDriverSPtr pDriver )
    : BaseDevice( name, "DigitalOutput", pDriver )
    , m_pDriver( pDriver )
{
}

DigitalOutputDevice::~DigitalOutputDevice()
{
}

void
DigitalOutputDevice::On()
{
    StartAsyncAction();

    const auto cb = [ this ]( DriverResponse driverResponse )
    {
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
        ResponseThrowOnError( response );
    };

    m_pDriver->GetTaskQueue()->Enqueue(
        [ this, cb ]
        {
            m_pDriver->On( cb );
        } );
}

void
DigitalOutputDevice::Off()
{
    StartAsyncAction();

    const auto cb = [ this ]( DriverResponse driverResponse )
    {
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
        ResponseThrowOnError( response );
    };

    m_pDriver->GetTaskQueue()->Enqueue(
        [ this, cb ]
        {
            m_pDriver->Off( cb );
        } );
}

void
DigitalOutputDevice::SetState( bool state )
{
    StartAsyncAction();

    const auto cb = [ this ]( DriverResponse driverResponse )
    {
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
        ResponseThrowOnError( response );
    };

    m_pDriver->GetTaskQueue()->Enqueue(
        [ this, state, cb ]
        {
            m_pDriver->SetState( state, cb );
        } );
}

bool
DigitalOutputDevice::GetState()
{
    bool state = false;

    StartAsyncAction();

    const auto cb = [ this, &state ]( DriverResponse driverResponse, bool returnState )
    {
        state = returnState;
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
        ResponseThrowOnError( response );
    };

    m_pDriver->GetTaskQueue()->Enqueue(
        [ this, cb ]
        {
            m_pDriver->GetState( cb );
        } );

    Wait();
    return state;
}

DeviceResponse
DigitalOutputDevice::ToDeviceResponse( DriverResponse response ) const
{
    return BaseDevice::ToDeviceResponse( response );
}

void
DigitalOutputDevice::ResponseThrowOnError( DeviceResponse response ) const
{
    BaseDevice::ResponseThrowOnError( response );
}
} // namespace Devices
} // namespace Gadgets