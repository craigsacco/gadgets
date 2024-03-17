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

#include <Gadgets/Core/Semaphore.hpp>

#include <gtest/gtest.h>

#include <thread>

using namespace ::testing;

class SemaphoreTests : public Test
{
public:
    SemaphoreTests()
        : m_semaphore()
        , m_thread()
        , m_releaseResult( false )
    {
    }

    void
    SetUp() override
    {
    }

    void
    TearDown() override
    {
        if ( m_thread.joinable() )
        {
            m_thread.join();
        }
    }

protected:
    void
    CreateThreadForRelease( std::chrono::milliseconds delay_ms )
    {
        m_thread = std::thread(
            [ this, delay_ms ]
            {
                std::this_thread::sleep_for( delay_ms );
                m_releaseResult = m_semaphore.Release();
            } );
    }

    Gadgets::Core::Semaphore m_semaphore;
    std::thread m_thread;
    std::atomic<bool> m_releaseResult;
};

TEST_F( SemaphoreTests, WaitBlocksUntilRelease )
{
    ASSERT_TRUE( m_semaphore.Acquire() );
    CreateThreadForRelease( std::chrono::milliseconds( 500 ) );
    ASSERT_TRUE( m_semaphore.Wait( std::chrono::seconds( 1 ) ) );
    m_thread.join();
    ASSERT_TRUE( m_releaseResult );
}

TEST_F( SemaphoreTests, WaitTimesOutBeforeRelease )
{
    ASSERT_TRUE( m_semaphore.Acquire() );
    CreateThreadForRelease( std::chrono::seconds( 1 ) );
    ASSERT_FALSE( m_semaphore.Wait( std::chrono::milliseconds( 500 ) ) );
    m_thread.join();
    ASSERT_TRUE( m_releaseResult );
}

TEST_F( SemaphoreTests, ReleaseWithoutAcquire )
{
    ASSERT_FALSE( m_semaphore.Release() );
}

TEST_F( SemaphoreTests, WaitWithoutAcquire )
{
    ASSERT_TRUE( m_semaphore.Wait( std::chrono::seconds( 1 ) ) );
}

TEST_F( SemaphoreTests, WaitAfterAcquireAndRelease )
{
    ASSERT_TRUE( m_semaphore.Acquire() );
    ASSERT_TRUE( m_semaphore.Release() );
    ASSERT_TRUE( m_semaphore.Wait( std::chrono::seconds( 1 ) ) );
}
