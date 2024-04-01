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

#include <Gadgets/Core/Semaphore.hpp>
#include <Gadgets/Core/TaskQueue.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <thread>

using namespace ::testing;

namespace Gadgets
{
namespace Core
{
class TaskQueueTests : public Test
{
public:
    TaskQueueTests()
        : m_taskQueue( s_taskQueueName )
    {
    }

    void
    SetUp() override
    {
        // implicit tests to boost coverage
        ASSERT_EQ( "TaskQueue", m_taskQueue.Type() );
        ASSERT_EQ( s_taskQueueName, m_taskQueue.Name() );
    }

    void
    TearDown() override
    {
        m_taskQueue.Stop();
    }

    MOCK_METHOD1( OnCallback, void( uint32_t ) );

protected:
    TaskQueue m_taskQueue;
    static const std::string s_taskQueueName;
};

const std::string TaskQueueTests::s_taskQueueName( "MyTaskQueueUnderTest" );

TEST_F( TaskQueueTests, TasksAreDispatchedInOrderBeforeStop )
{
    Semaphore semaphore;

    {
        InSequence sequence;
        EXPECT_CALL( *this, OnCallback( 1 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 2 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 3 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 4 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 5 ) ).Times( 1 );
    }

    // start and dispatch tasks - synchronise the completion of the last one with this thread
    // before stopping the task queue
    m_taskQueue.Start();
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 1 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 2 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 3 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 4 ); } );
    semaphore.Acquire();
    m_taskQueue.BeginInvoke(
        [ & ]
        {
            OnCallback( 5 );
            semaphore.Release();
        } );
    semaphore.Wait( std::chrono::milliseconds( 1000 ) );
    m_taskQueue.Stop();
}

TEST_F( TaskQueueTests, DispatchedTasksBeforeStartAreStillExecutedWhenStarted )
{
    Semaphore semaphore;

    {
        InSequence sequence;
        EXPECT_CALL( *this, OnCallback( 1 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 2 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 3 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 4 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 5 ) ).Times( 1 );
    }

    // dispatch tasks before starting thread - start thread and synchronise the completion of the
    // last task with this thread before stopping the task queue
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 1 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 2 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 3 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 4 ); } );
    semaphore.Acquire();
    m_taskQueue.BeginInvoke(
        [ & ]
        {
            OnCallback( 5 );
            semaphore.Release();
        } );
    m_taskQueue.Start();
    semaphore.Wait( std::chrono::milliseconds( 1000 ) );
    m_taskQueue.Stop();
}

TEST_F( TaskQueueTests, DispatchTasksCompleteBeforeCompleteStop )
{
    {
        InSequence sequence;
        EXPECT_CALL( *this, OnCallback( 1 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 2 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 3 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 4 ) ).Times( 1 );
        EXPECT_CALL( *this, OnCallback( 5 ) ).Times( 1 );
    }

    // deliberately delay the completion of the last task after Stop() is issued, but it is still
    // executed
    m_taskQueue.Start();
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 1 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 2 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 3 ); } );
    m_taskQueue.BeginInvoke( [ this ] { OnCallback( 4 ); } );
    m_taskQueue.BeginInvoke(
        [ & ]
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
            OnCallback( 5 );
        } );
    m_taskQueue.Stop();
}

} // namespace Core
} // namespace Gadgets
