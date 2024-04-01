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

#include <Gadgets/Core/MockTaskQueue.hpp>
#include <Gadgets/Devices/BaseDevice.hpp>
#include <Gadgets/Devices/MockDeviceDriver.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

int
BaseDeviceTests()
{
    return 0;
}

namespace Gadgets
{
namespace Devices
{
class BaseDeviceTests : public Test
{
public:
    BaseDeviceTests()
        : m_pDriver( std::make_shared<StrictMock<MockDeviceDriver>>() )
        , m_pTaskQueue( std::make_shared<Core::MockTaskQueue>() )
        , m_device( m_pDriver )
    {
        // setup task queue - execute invoked tasks immediately
        m_pTaskQueue->RunOnInvoke();
        EXPECT_CALL( *m_pDriver, GetTaskQueue() ).WillRepeatedly( Return( m_pTaskQueue ) );
    }

    void
    SetUp() override
    {
        // implicit tests to boost coverage
        ASSERT_EQ( TestDevice::DeviceType, m_device.Type() );
        ASSERT_EQ( TestDevice::DeviceName, m_device.Name() );
    }

    void
    TearDown() override
    {
    }

protected:
    std::shared_ptr<StrictMock<MockDeviceDriver>> m_pDriver;
    std::shared_ptr<Core::MockTaskQueue> m_pTaskQueue;

    class TestDevice : public BaseDevice
    {
    public:
        TestDevice( IDeviceDriverSPtr pDriver )
            : BaseDevice( DeviceName, DeviceType, pDriver )
        {
        }

        static const std::string DeviceName;
        static const std::string DeviceType;
    };
    TestDevice m_device;
};

const std::string BaseDeviceTests::TestDevice::DeviceName = "MyTestDevice";
const std::string BaseDeviceTests::TestDevice::DeviceType = "TestDevice";

TEST_F( BaseDeviceTests, InitialiseActionSuccess )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, Initialise( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.Initialise();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverOK );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_NO_THROW( m_device.Wait() );
}

TEST_F( BaseDeviceTests, InitialiseActionFailed )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, Initialise( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.Initialise();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverFailed );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_THROW( m_device.Wait(), DeviceException );
}

TEST_F( BaseDeviceTests, ShutdownActionSuccess )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, Shutdown( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.Shutdown();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverOK );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_NO_THROW( m_device.Wait() );
}

TEST_F( BaseDeviceTests, ShutdownActionFailed )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, Shutdown( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.Shutdown();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverFailed );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_THROW( m_device.Wait(), DeviceException );
}

} // namespace Devices
} // namespace Gadgets
