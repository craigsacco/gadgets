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

#pragma once

#include <Gadgets/Core/ITaskQueue.hpp>

#include <gmock/gmock.h>

#include <queue>

namespace Gadgets
{
namespace Core
{

class MockTaskQueue : public virtual ITaskQueue
{
public:
    MockTaskQueue()
        : m_runOnInvoke( false )
        , m_tasks()
    {
    }

    virtual ~MockTaskQueue() = default;

#pragma region "Overrides from IObject"
    std::string
    Type() const
    {
        return "MockTaskQueue";
    }
#pragma endregion

#pragma region "Overrides from ITaskQueue"
    void
    BeginInvoke( TaskFunction task )
    {
        if ( m_runOnInvoke )
        {
            task();
        }
        else
        {
            m_tasks.push( task );
        }
    }
#pragma endregion

    void
    RunOnInvoke()
    {
        m_runOnInvoke = true;
    }

    size_t
    GetNumberOfQueuedTasks() const
    {
        return m_tasks.size();
    }

    void
    RunTasks( size_t tasksToRun )
    {
        if ( m_tasks.size() < tasksToRun )
        {
            FAIL() << "Not enough tasks to run";
        }

        while ( tasksToRun != 0 )
        {
            auto task = m_tasks.front();
            m_tasks.pop();
            task();
            tasksToRun--;
        }
    }

private:
    bool m_runOnInvoke;
    std::queue<TaskFunction> m_tasks;
};
} // namespace Core
} // namespace Gadgets
