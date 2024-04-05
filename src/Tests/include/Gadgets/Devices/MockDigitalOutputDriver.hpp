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

#pragma once

#include <Gadgets/Devices/IDigitalOutputDriver.hpp>
#include <Gadgets/Devices/MockDeviceDriver.hpp>

#if defined( _MSC_VER )
// methods inherited by dominance are fine - inhibit this warning (cleared at end
// of file)
#pragma warning( push )
#pragma warning( disable : 4250 )
#endif

namespace Gadgets
{
namespace Devices
{

class MockDigitalOutputDriver
    : public MockDeviceDriver
    , public virtual IDigitalOutputDriver
{
public:
    MockDigitalOutputDriver() = default;
    virtual ~MockDigitalOutputDriver() = default;

#pragma region "Overrides from MockDeviceDriver"
    std::string
    Type() const override
    {
        return "MockDigitalOutputDriver";
    }
#pragma endregion

#pragma region "Overrides from IDigitalOutputDriver"
    MOCK_METHOD1( On, void( std::function<void( DriverResponse )> cb ) );
    MOCK_METHOD1( Off, void( std::function<void( DriverResponse )> cb ) );
    MOCK_METHOD2( SetState, void( bool state, std::function<void( DriverResponse )> cb ) );
    MOCK_METHOD1( GetState, void( std::function<void( DriverResponse, bool )> cb ) );
#pragma endregion
};

} // namespace Devices
} // namespace Gadgets

#if defined( _MSC_VER )
#pragma warning( pop )
#endif
