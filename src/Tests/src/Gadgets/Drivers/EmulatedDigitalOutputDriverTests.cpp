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
#include <Gadgets/Devices/DriverResponse.hpp>
#include <Gadgets/Drivers/EmulatedDigitalOutputDriver.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

namespace Gadgets
{
namespace Drivers
{
class EmulatedDigitalOutputDriverTests : public Test
{
public:
    EmulatedDigitalOutputDriverTests()
        : m_pTaskQueue( std::make_shared<Core::MockTaskQueue>() )
        , m_driver( TestDriverName )
    {
        // setup task queue - execute invoked tasks immediately
        m_pTaskQueue->RunOnInvoke();
        m_driver.SetTaskQueue( m_pTaskQueue );
    }

    void
    SetUp() override
    {
        // implicit tests to boost coverage
        ASSERT_EQ( EmulatedDigitalOutputDriver::DriverType, m_driver.Type() );
        ASSERT_EQ( TestDriverName, m_driver.Name() );
    }

    void
    TearDown() override
    {
    }

    bool
    GetInternalDriverState() const
    {
        return m_driver.m_state;
    }

    void
    SetInternalDriverState( bool state )
    {
        m_driver.m_state = state;
    }

    MOCK_METHOD1( OnDriverComplete, void( Devices::DriverResponse ) );
    MOCK_METHOD2( OnDriverCompleteWithBoolean, void( Devices::DriverResponse, bool ) );

protected:
    static const std::string TestDriverName;

    std::shared_ptr<Core::MockTaskQueue> m_pTaskQueue;
    EmulatedDigitalOutputDriver m_driver;
};

const std::string EmulatedDigitalOutputDriverTests::TestDriverName = "MyDigitalOutput";

TEST_F( EmulatedDigitalOutputDriverTests, InitialiseAction )
{
    EXPECT_CALL( *this, OnDriverComplete( Devices::StandardDriverResponses::DriverOK ) ).Times( 1 );
    m_driver.Initialise( std::bind( &EmulatedDigitalOutputDriverTests::OnDriverComplete, this,
                                    std::placeholders::_1 ) );
    ASSERT_FALSE( GetInternalDriverState() );
}

TEST_F( EmulatedDigitalOutputDriverTests, ShutdownAction )
{
    EXPECT_CALL( *this, OnDriverComplete( Devices::StandardDriverResponses::DriverOK ) ).Times( 1 );
    m_driver.Shutdown( std::bind( &EmulatedDigitalOutputDriverTests::OnDriverComplete, this,
                                  std::placeholders::_1 ) );
    ASSERT_FALSE( GetInternalDriverState() );
}

TEST_F( EmulatedDigitalOutputDriverTests, OnAction )
{
    EXPECT_CALL( *this, OnDriverComplete( Devices::StandardDriverResponses::DriverOK ) ).Times( 1 );
    m_driver.On( std::bind( &EmulatedDigitalOutputDriverTests::OnDriverComplete, this,
                            std::placeholders::_1 ) );
    ASSERT_TRUE( GetInternalDriverState() );
}

TEST_F( EmulatedDigitalOutputDriverTests, OffAction )
{
    EXPECT_CALL( *this, OnDriverComplete( Devices::StandardDriverResponses::DriverOK ) ).Times( 1 );
    m_driver.Off( std::bind( &EmulatedDigitalOutputDriverTests::OnDriverComplete, this,
                             std::placeholders::_1 ) );
    ASSERT_FALSE( GetInternalDriverState() );
}

TEST_F( EmulatedDigitalOutputDriverTests, SetStateAction )
{
    // test when setting true
    {
        EXPECT_CALL( *this, OnDriverComplete( Devices::StandardDriverResponses::DriverOK ) )
            .Times( 1 );
        m_driver.SetState( true, std::bind( &EmulatedDigitalOutputDriverTests::OnDriverComplete,
                                            this, std::placeholders::_1 ) );
        ASSERT_TRUE( GetInternalDriverState() );

        Mock::VerifyAndClearExpectations( this );
    }

    // test when setting false
    {
        EXPECT_CALL( *this, OnDriverComplete( Devices::StandardDriverResponses::DriverOK ) )
            .Times( 1 );
        m_driver.SetState( false, std::bind( &EmulatedDigitalOutputDriverTests::OnDriverComplete,
                                             this, std::placeholders::_1 ) );
        ASSERT_FALSE( GetInternalDriverState() );

        Mock::VerifyAndClearExpectations( this );
    }
}

TEST_F( EmulatedDigitalOutputDriverTests, GetStateAction )
{
    // test when returning true
    {
        SetInternalDriverState( true );

        EXPECT_CALL(
            *this, OnDriverCompleteWithBoolean( Devices::StandardDriverResponses::DriverOK, true ) )
            .Times( 1 );
        m_driver.GetState(
            std::bind( &EmulatedDigitalOutputDriverTests::OnDriverCompleteWithBoolean, this,
                       std::placeholders::_1, std::placeholders::_2 ) );

        Mock::VerifyAndClearExpectations( this );
    }

    // test when returning false
    {
        SetInternalDriverState( false );

        EXPECT_CALL( *this, OnDriverCompleteWithBoolean( Devices::StandardDriverResponses::DriverOK,
                                                         false ) )
            .Times( 1 );
        m_driver.GetState(
            std::bind( &EmulatedDigitalOutputDriverTests::OnDriverCompleteWithBoolean, this,
                       std::placeholders::_1, std::placeholders::_2 ) );

        Mock::VerifyAndClearExpectations( this );
    }
}

} // namespace Drivers
} // namespace Gadgets
