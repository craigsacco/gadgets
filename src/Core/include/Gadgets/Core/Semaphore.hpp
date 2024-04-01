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

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace Gadgets
{
namespace Core
{

/**
 * @brief   Implementation of a binary semaphore for synchronising operations between threads.
 */
class Semaphore : public virtual IObject
{
public:
    /**
     * @brief   Constructor for a binary semaphore.
     */
    Semaphore();

    /**
     * @brief   Virtual destructor.
     */
    virtual ~Semaphore();

#pragma region "Overrides from IObject"
    std::string Type() const final;
#pragma endregion

    /**
     * @brief       Acquire a synchronisation lock on the binary semaphore.
     *
     * @return      True if the synchronisation lock was acquired, or false if it is already locked.
     */
    bool Acquire();

    /**
     * @brief       Release an existing synchronisation lock on the binary semaphore.
     *
     * @return      True if the synchronisation lock was released, or false if it was never
     *              acquired in the first place.
     */
    bool Release();

    /**
     * @brief       Wait for the synchronisation lock to be release within the given timeout.
     *
     * @param[in]   timeout_ms  The maximum timeout to wait for a release.
     * @return      True if the synchronisation lock was released within the given timeout period
     *              or the lock was already release; or false if the lock was not release before
     *              the timeout expired.
     */
    bool Wait( std::chrono::milliseconds timeout_ms );

    /**
     * @brief       Gets the acquisition state of this semaphore.
     *
     * @return      True if the semaphore has been acqired.
     */
    bool IsAcquired() const;

private:
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_acquired;
};
} // namespace Core
} // namespace Gadgets
