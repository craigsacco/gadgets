/*
 * Copyright (c) 2024 Craig Sacco
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Devices/DigitalOutputDevice.hpp>
#include <Gadgets/Devices/IDigitalOutputDriver.hpp>

namespace Gadgets
{
namespace Devices
{
DigitalOutputDevice::DigitalOutputDevice( const std::string& name,
                                          IDigitalOutputDriverSPtr pDriver )
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
    };

    m_pDriver->GetTaskQueue()->BeginInvoke( [ this, cb ] { m_pDriver->On( cb ); } );
}

void
DigitalOutputDevice::Off()
{
    StartAsyncAction();

    const auto cb = [ this ]( DriverResponse driverResponse )
    {
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
    };

    m_pDriver->GetTaskQueue()->BeginInvoke( [ this, cb ] { m_pDriver->Off( cb ); } );
}

void
DigitalOutputDevice::SetState( bool state )
{
    StartAsyncAction();

    const auto cb = [ this ]( DriverResponse driverResponse )
    {
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
    };

    m_pDriver->GetTaskQueue()->BeginInvoke( [ this, state, cb ]
                                            { m_pDriver->SetState( state, cb ); } );
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
    };

    m_pDriver->GetTaskQueue()->BeginInvoke( [ this, cb ] { m_pDriver->GetState( cb ); } );

    Wait();
    return state;
}

DeviceResponse
DigitalOutputDevice::ToDeviceResponse( DriverResponse response ) const
{
    return BaseDevice::ToDeviceResponse( response );
}

void
DigitalOutputDevice::HandleActionResponse( DeviceResponse response ) const
{
    BaseDevice::HandleActionResponse( response );
}
} // namespace Devices
} // namespace Gadgets