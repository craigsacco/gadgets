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

#include <Gadgets/Core/TaskQueue.hpp>

namespace Gadgets
{
namespace Core
{
TaskQueue::TaskQueue( const std::string& name )
    : Thread( name )
    , m_context()
    , m_workguard( boost::asio::make_work_guard( m_context ) )
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
        m_context.run();
        if ( IsStopping() )
        {
            break;
        }
    }

    m_context.reset();
}

void
TaskQueue::NotifyStopping()
{
    m_context.stop();
}

void
TaskQueue::BeginInvoke( std::function<void()> task )
{
    boost::asio::post( m_context, task );
}
} // namespace Core
} // namespace Gadgets