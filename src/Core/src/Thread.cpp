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

#include <Gadgets/Core/LoggerMacros.hpp>
#include <Gadgets/Core/Thread.hpp>

namespace Gadgets
{
namespace Core
{
Thread::Thread( const std::string& name )
    : m_name( name )
    , m_thread()
    , m_state( Stopped )
    , m_mutex()
{
}

Thread::~Thread()
{
    Stop();
}

void
Thread::Start()
{
    std::lock_guard lock( m_mutex );

    if ( m_state == Stopped )
    {
        LOG_DEBUG_INTERNAL( "Starting thread " + m_name );

        m_state = Started;
        m_thread = std::thread(
            [ this ]()
            {
                this->Run();
            } );

        LOG_DEBUG_INTERNAL( "Started thread " + m_name );
    }
}

void
Thread::Stop()
{
    std::lock_guard lock( m_mutex );

    if ( m_state == Started )
    {
        LOG_DEBUG_INTERNAL( "Stopping thread " + m_name );

        m_state = Stopping;
        NotifyStopping();
        m_thread.join();
        m_thread = std::thread();

        LOG_DEBUG_INTERNAL( "Stopped thread " + m_name );
    }
}

void
Thread::Run()
{
    RunInternal();
    m_state = Stopped;
}

void
Thread::NotifyStopping()
{
    // by default, do nothing
}

std::string
Thread::Name() const
{
    return m_name;
}

bool
Thread::IsStopping() const
{
    return ( m_state == Stopping );
}
} // namespace Core
} // namespace Gadgets