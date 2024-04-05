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

#include <Gadgets/Core/TaskQueue.hpp>

namespace Gadgets
{
namespace Core
{
TaskQueue::TaskQueue( const std::string& name )
    : Thread( name )
    , m_mutex()
    , m_cv()
    , m_queue()
{
}

TaskQueue::~TaskQueue()
{
}

std::string
TaskQueue::Type() const
{
    return "TaskQueue";
}

void
TaskQueue::Run()
{
    for ( ;; )
    {
        TaskFunction task = nullptr;

        // synchronise access to the task queue
        {
            std::unique_lock lock( m_mutex );

            if ( m_queue.empty() )
            {
                // if the thread is stopping, bail out since there are no more tasks to handle
                if ( IsStopping() )
                {
                    return;
                }

                // wait for new task to be inserted - pop task if one exists in the queue
                m_cv.wait( lock );
                if ( !m_queue.empty() )
                {
                    task = m_queue.front();
                    m_queue.pop();
                }
            }
            else
            {
                // pop task at the front of the queue
                task = m_queue.front();
                m_queue.pop();
            }
        }

        // execute task if it has been popped
        if ( task != nullptr )
        {
            task();
        }
    }
}

void
TaskQueue::NotifyStopping()
{
    std::lock_guard<std::mutex> lock( m_mutex );

    // notify when the queue is empty so that the thread is woken up
    if ( m_queue.empty() )
    {
        m_cv.notify_one();
    }
}

void
TaskQueue::BeginInvoke( TaskFunction task )
{
    std::lock_guard<std::mutex> lock( m_mutex );

    // insert new task and notify thread if it was empty
    const auto wasEmpty = m_queue.empty();
    m_queue.push( task );
    if ( wasEmpty )
    {
        m_cv.notify_one();
    }
}
} // namespace Core
} // namespace Gadgets