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

#include <Gadgets/Devices/IDeviceDriver.hpp>

#include <gmock/gmock.h>

namespace Gadgets
{
namespace Devices
{

class MockDeviceDriver : public virtual IDeviceDriver
{
public:
    MockDeviceDriver() = default;
    virtual ~MockDeviceDriver() = default;

#pragma region "Overrides from IObject"
    virtual std::string
    Type() const override
    {
        return "MockDeviceDriver";
    }
#pragma endregion

#pragma region "Overrides from IDeviceDriver"
    MOCK_METHOD1( Initialise, void( std::function<void( DriverResponse )> cb ) );
    MOCK_METHOD1( Shutdown, void( std::function<void( DriverResponse )> cb ) );
    MOCK_CONST_METHOD0( Name, std::string() );

    void
    SetTaskQueue( Core::ITaskQueueSPtr pTaskQueue ) override final
    {
        m_pTaskQueue = pTaskQueue;
    }

    Core::ITaskQueueSPtr
    GetTaskQueue() const override final
    {
        return m_pTaskQueue;
    }
#pragma endregion

private:
    Core::ITaskQueueSPtr m_pTaskQueue;
};

} // namespace Devices
} // namespace Gadgets
