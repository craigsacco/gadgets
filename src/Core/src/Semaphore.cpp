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

namespace Gadgets
{
namespace Core
{
Semaphore::Semaphore()
    : m_mutex()
    , m_cv()
    , m_acquired( false )
{
}

Semaphore::~Semaphore()
{
}

std::string
Semaphore::Type() const
{
    return "Semaphore";
}

bool
Semaphore::Acquire()
{
    std::lock_guard<std::mutex> lock( m_mutex );
    if ( !m_acquired )
    {
        m_acquired = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool
Semaphore::Release()
{
    std::lock_guard<std::mutex> lock( m_mutex );
    if ( m_acquired )
    {
        m_acquired = false;
        m_cv.notify_all();
        return true;
    }
    else
    {
        return false;
    }
}

bool
Semaphore::Wait( std::chrono::milliseconds timeout_ms )
{
    std::unique_lock<std::mutex> lock( m_mutex );
    if ( m_acquired )
    {
        return ( m_cv.wait_for( lock, timeout_ms ) == std::cv_status::no_timeout );
    }
    else
    {
        return true;
    }
}

bool
Semaphore::IsAcquired() const
{
    std::lock_guard<std::mutex> lock( m_mutex );

    return m_acquired;
}
} // namespace Core
} // namespace Gadgets