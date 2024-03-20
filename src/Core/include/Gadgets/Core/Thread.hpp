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

#include <Gadgets/Core/IThread.hpp>

#include <mutex>
#include <thread>

namespace Gadgets
{
namespace Core
{

/**
 * @brief   Implementation of a thread instance.
 */
class Thread : public virtual IThread
{
public:
    /**
     * @brief       Constructor for a thread.
     *
     * @param[in]   name    The name of the thread.
     */
    Thread( const std::string& name );

    /**
     * @brief       Virtual destructor.
     */
    virtual ~Thread();

#pragma region "Overrides from IThread"
    void Start() override final;
    void Stop() override final;
    std::string Name() const override final;
#pragma endregion

protected:
    /**
     * @brief       The thread function being executed.
     */
    virtual void Run() = 0;

    /**
     * @brief       Notification function to run when a stop request is issued.
     *
     * @note        This is not run withing the same context as the thread - any interactions
     *              between NotifyStopping() and Run() will need to be synchronised.
     */
    virtual void NotifyStopping();

    /**
     * @brief   Thread state.
     */
    enum State
    {
        //! @brief  Thread is stopped.
        Stopped,

        //! @brief  Thread is started.
        Started,

        //! @brief  Thread is stopping.
        Stopping,
    };

    /**
     * @brief       Indicates within the thread loop that the thread should be stopped.
     *
     * @return      True if a stop request is issued and the thread has not terminated.
     */
    bool IsStopping() const;

private:
    const std::string m_name;
    std::thread m_thread;
    std::atomic<State> m_state;
    std::mutex m_mutex;
};
} // namespace Core
} // namespace Gadgets