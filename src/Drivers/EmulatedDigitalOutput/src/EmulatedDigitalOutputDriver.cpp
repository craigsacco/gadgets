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

// SPDX-License-Identifier: MIT

#include <Gadgets/Drivers/EmulatedDigitalOutputDriver.hpp>

namespace Gadgets
{
namespace Drivers
{
EmulatedDigitalOutputDriver::EmulatedDigitalOutputDriver( const std::string& name )
    : BaseDeviceDriver( name, "EmulatedDigitalOutputDriver" )
    , m_state( false )
{
}

EmulatedDigitalOutputDriver::~EmulatedDigitalOutputDriver()
{
}

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
EmulatedDigitalOutputDriver::SetState( bool state,
                                       std::function<void( Devices::DriverResponse )> cb )
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