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

#include <Gadgets/Core/MockTaskQueue.hpp>
#include <Gadgets/Devices/DigitalOutputDevice.hpp>
#include <Gadgets/Devices/MockDigitalOutputDriver.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

namespace Gadgets
{
namespace Devices
{
class DigitalOutputDeviceTests : public Test
{
public:
    DigitalOutputDeviceTests()
        : m_pDriver( std::make_shared<StrictMock<MockDigitalOutputDriver>>() )
        , m_pTaskQueue( std::make_shared<Core::MockTaskQueue>() )
        , m_device( TestDeviceName, m_pDriver )
    {
        // setup task queue - execute invoked tasks immediately
        m_pTaskQueue->RunOnInvoke();
        m_pDriver->SetTaskQueue( m_pTaskQueue );
    }

    void
    SetUp() override
    {
        // implicit tests to boost coverage
        ASSERT_EQ( DigitalOutputDevice::DeviceType, m_device.Type() );
        ASSERT_EQ( TestDeviceName, m_device.Name() );
    }

    void
    TearDown() override
    {
    }

protected:
    static const std::string TestDeviceName;

    std::shared_ptr<StrictMock<MockDigitalOutputDriver>> m_pDriver;
    std::shared_ptr<Core::MockTaskQueue> m_pTaskQueue;
    DigitalOutputDevice m_device;
};

const std::string DigitalOutputDeviceTests::TestDeviceName = "MyDigitalOutput";

TEST_F( DigitalOutputDeviceTests, OnActionSuccess )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, On( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.On();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverOK );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_NO_THROW( m_device.Wait() );
}

TEST_F( DigitalOutputDeviceTests, OnActionFailed )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, On( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.On();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverFailed );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_THROW( m_device.Wait(), DeviceException );
}

TEST_F( DigitalOutputDeviceTests, OffActionSuccess )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, Off( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.Off();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverOK );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_NO_THROW( m_device.Wait() );
}

TEST_F( DigitalOutputDeviceTests, OffActionFailed )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, Off( _ ) ).WillOnce( SaveArg<0>( &cb ) );
    m_device.Off();
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverFailed );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_THROW( m_device.Wait(), DeviceException );
}

TEST_F( DigitalOutputDeviceTests, SetStateActionSuccess )
{
    // test when setting true
    {
        std::function<void( DriverResponse )> cb = nullptr;
        EXPECT_CALL( *m_pDriver, SetState( true, _ ) ).WillOnce( SaveArg<1>( &cb ) );
        m_device.SetState( true );
        ASSERT_TRUE( m_device.IsActionInProgress() );

        cb( StandardDriverResponses::DriverOK );
        ASSERT_FALSE( m_device.IsActionInProgress() );

        ASSERT_NO_THROW( m_device.Wait() );

        Mock::VerifyAndClearExpectations( m_pDriver.get() );
    }

    // test when setting false
    {
        std::function<void( DriverResponse )> cb = nullptr;
        EXPECT_CALL( *m_pDriver, SetState( false, _ ) ).WillOnce( SaveArg<1>( &cb ) );
        m_device.SetState( false );
        ASSERT_TRUE( m_device.IsActionInProgress() );

        cb( StandardDriverResponses::DriverOK );
        ASSERT_FALSE( m_device.IsActionInProgress() );

        ASSERT_NO_THROW( m_device.Wait() );

        Mock::VerifyAndClearExpectations( m_pDriver.get() );
    }
}

TEST_F( DigitalOutputDeviceTests, SetStateActionFailed )
{
    std::function<void( DriverResponse )> cb = nullptr;
    EXPECT_CALL( *m_pDriver, SetState( true, _ ) ).WillOnce( SaveArg<1>( &cb ) );
    m_device.SetState( true );
    ASSERT_TRUE( m_device.IsActionInProgress() );

    cb( StandardDriverResponses::DriverFailed );
    ASSERT_FALSE( m_device.IsActionInProgress() );

    ASSERT_THROW( m_device.Wait(), DeviceException );
}

TEST_F( DigitalOutputDeviceTests, GetStateActionSuccess )
{
    // test when returning true
    {
        EXPECT_CALL( *m_pDriver, GetState( _ ) )
            .WillOnce( Invoke( []( std::function<void( DriverResponse, bool )> cb )
                               { cb( StandardDriverResponses::DriverOK, true ); } ) );
        ASSERT_TRUE( m_device.GetState() );

        Mock::VerifyAndClearExpectations( m_pDriver.get() );
    }

    // test when returning true
    {
        EXPECT_CALL( *m_pDriver, GetState( _ ) )
            .WillOnce( Invoke( []( std::function<void( DriverResponse, bool )> cb )
                               { cb( StandardDriverResponses::DriverOK, false ); } ) );
        ASSERT_FALSE( m_device.GetState() );

        Mock::VerifyAndClearExpectations( m_pDriver.get() );
    }
}

TEST_F( DigitalOutputDeviceTests, GetStateActionFailed )
{
    EXPECT_CALL( *m_pDriver, GetState( _ ) )
        .WillOnce( Invoke( []( std::function<void( DriverResponse, bool )> cb )
                           { cb( StandardDriverResponses::DriverFailed, true ); } ) );
    ASSERT_THROW( m_device.GetState(), DeviceException );
}

} // namespace Devices
} // namespace Gadgets
