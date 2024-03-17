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

#include <Gadgets/Core/IObject.hpp>

#include <mutex>
#include <thread>

namespace Gadgets
{
namespace Core
{
class Thread : public virtual IObject
{
public:
    Thread( const std::string& name );
    virtual ~Thread();

    void Start();
    void Stop();
    void Run();
    std::string Name() const;

    virtual void RunInternal() = 0;
    virtual void NotifyStopping();

protected:
    enum State
    {
        Stopped,
        Started,
        Stopping,
    };
    bool IsStopping() const;

private:
    const std::string m_name;
    std::thread m_thread;
    std::atomic<State> m_state;
    std::mutex m_mutex;
};
} // namespace Core
} // namespace Gadgets