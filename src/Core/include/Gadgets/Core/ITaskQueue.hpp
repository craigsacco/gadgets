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

#include <chrono>
#include <functional>

namespace Gadgets
{
namespace Core
{

/**
 * @brief   Interface for a type of task queue.
 */
class ITaskQueue
{
public:
    /**
     * @brief       Dispatches a task in the task queue and returns immediately.
     *
     * @details     If the task queue is empty, the task will be executed within the context of the
     * task queue thread. If the task queue is not empty, the task will be queued until it reaches
     * the front of the queue, where it will be executed.
     *
     * @param[in]   task    The task to dispatch into the queue.
     */
    virtual void BeginInvoke( std::function<void()> task ) = 0;

protected:
    ITaskQueue() = default;
    ~ITaskQueue() = default;
};
} // namespace Core
} // namespace Gadgets
