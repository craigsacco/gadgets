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

#include <Gadgets/Core/ExceptionMacros.hpp>
#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Devices/BaseDevice.hpp>
#include <Gadgets/Devices/IDeviceDriver.hpp>

#include <map>

namespace Gadgets
{
namespace Devices
{
BaseDevice::BaseDevice( const std::string& name, const std::string& type,
                        IDeviceDriverSPtr pDriver )
    : m_name( name )
    , m_type( type )
    , m_pDriver( pDriver )
    , m_semaphore()
{
}

BaseDevice::~BaseDevice()
{
}

std::string
BaseDevice::Name() const
{
    return m_name;
}

void
BaseDevice::Initialise()
{
    StartAsyncAction();

    const auto cb = [ this ]( DriverResponse driverResponse )
    {
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
        ResponseThrowOnError( response );
    };

    m_pDriver->GetTaskQueue()->BeginInvoke(
        [ this, cb ]
        {
            m_pDriver->Initialise( cb );
        } );
}

void
BaseDevice::Shutdown()
{
    StartAsyncAction();

    const auto cb = [ this ]( DriverResponse driverResponse )
    {
        auto response = ToDeviceResponse( driverResponse );
        FinaliseAsyncAction( response );
        ResponseThrowOnError( response );
    };

    m_pDriver->GetTaskQueue()->BeginInvoke(
        [ this, cb ]
        {
            m_pDriver->Shutdown( cb );
        } );
}

void
BaseDevice::Wait()
{
    Wait( DefaultTimeout() );
}

void
BaseDevice::Wait( std::chrono::milliseconds timeout_ms )
{
    if ( !m_semaphore.Wait( timeout_ms ) )
    {
        THROW_RUNTIME_ERROR( "Action timed out" );
    }
}

std::string
BaseDevice::Type() const
{
    return m_type;
}

std::chrono::milliseconds
BaseDevice::DefaultTimeout() const
{
    return std::chrono::milliseconds( 2000 );
}

void
BaseDevice::StartAsyncAction()
{
    if ( !m_semaphore.Acquire() )
    {
        THROW_RUNTIME_ERROR( "Device is busy" );
    }
}

void
BaseDevice::FinaliseAsyncAction( DeviceResponse response )
{
    ( void )response;

    if ( !m_semaphore.Release() )
    {
        THROW_LOGIC_ERROR( "StartAsyncAction() not called beforehand" );
    }
}

DeviceResponse
BaseDevice::ToDeviceResponse( DriverResponse response ) const
{
    static const std::map<DriverResponse, DeviceResponse> responseMap = {
        std::make_pair( StandardDriverResponses::DriverOK, StandardDeviceResponses::DeviceOK ),
        std::make_pair( StandardDriverResponses::DriverFailed,
                        StandardDeviceResponses::DeviceFailed ),
    };

    if ( responseMap.find( response ) != responseMap.end() )
    {
        return responseMap.at( response );
    }

    return StandardDeviceResponses::DeviceFailed;
}

void
BaseDevice::ResponseThrowOnError( DeviceResponse response ) const
{
    switch ( response )
    {
    case StandardDeviceResponses::DeviceOK:
        break; // no error

    case StandardDeviceResponses::DeviceFailed:
        THROW_RUNTIME_ERROR( "Device action encountered a failure" );
        break;

    default:
        THROW_RUNTIME_ERROR( "Device encountered an unhandled error" );
        break;
    }
}
} // namespace Devices
} // namespace Gadgets