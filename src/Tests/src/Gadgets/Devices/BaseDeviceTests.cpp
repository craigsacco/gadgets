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

#include <Gadgets/Devices/BaseDevice.hpp>
#include <Gadgets/Core/MockTaskQueue.hpp>
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
    }

    void
    SetUp() override
    {
        // implicit tests to boost coverage
        //ASSERT_EQ( "TaskQueue", m_taskQueue.Type() );
        //ASSERT_EQ( s_taskQueueName, m_taskQueue.Name() );
    }

    void
    TearDown() override
    {
    }

    MOCK_METHOD1( OnCallback, void( uint32_t ) );

protected:
    std::shared_ptr<StrictMock<MockDeviceDriver>> m_pDriver;
    std::shared_ptr<Core::MockTaskQueue> m_pTaskQueue;

    class TestDevice : public BaseDevice
    {
    public:
        TestDevice(IDeviceDriverSPtr pDriver)
            : BaseDevice("MyTestDevice", "TestDevice", pDriver)
        {
        }
    };
    TestDevice m_device;
};

TEST_F( BaseDeviceTests, xxx )
{
}

} // namespace Core
} // namespace Gadgets
