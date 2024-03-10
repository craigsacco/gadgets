#include <Gadgets/Core/Semaphore.hpp>

#include <gtest/gtest.h>

#include <thread>

using namespace ::testing;

class SemaphoreTests : public Test
{
public:
    SemaphoreTests() : m_semaphore(), m_thread(), m_releaseResult( false ) {}

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
        m_thread = std::thread( [ this, delay_ms ] {
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

TEST_F( SemaphoreTests, ReleaseWithoutAcquire ) { ASSERT_FALSE( m_semaphore.Release() ); }

TEST_F( SemaphoreTests, WaitWithoutAcquire ) { ASSERT_TRUE( m_semaphore.Wait( std::chrono::seconds( 1 ) ) ); }

TEST_F( SemaphoreTests, WaitAfterAcquireAndRelease )
{
    ASSERT_TRUE( m_semaphore.Acquire() );
    ASSERT_TRUE( m_semaphore.Release() );
    ASSERT_TRUE( m_semaphore.Wait( std::chrono::seconds( 1 ) ) );
}
