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

#pragma once

#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Core/Semaphore.hpp>
#include <Gadgets/Core/Thread.hpp>

#include <boost/asio.hpp>

namespace Gadgets
{
namespace Core
{

/**
 * @brief   Implementation of a task queue.
 */
class TaskQueue
    : public Thread
    , public virtual ITaskQueue
{
public:
    /**
     * @brief       Constructor for a task queue.
     *
     * @param[in]   name    The name of the task queue.
     */
    TaskQueue( const std::string& name );

    /**
     * @brief       Virtual destructor.
     */
    virtual ~TaskQueue();

#pragma region "Overrides from IObject"
    std::string Type() const final;
#pragma endregion

#pragma region "Overrides from Thread"
    void Run() override final;
    void NotifyStopping() override final;
#pragma endregion

#pragma region "Overrides from ITaskQueue"
    void BeginInvoke( std::function<void()> task ) override final;
    void Invoke( std::function<void()> task, std::chrono::milliseconds timeout_ms ) override final;
#pragma endregion

private:
    boost::asio::io_context m_context;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workguard;
    Semaphore m_blockingSemaphore;
};
} // namespace Core
} // namespace Gadgets
