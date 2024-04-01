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

#include <Gadgets/Core/IObject.hpp>
#include <Gadgets/Devices/DeviceResponse.hpp>

#include <chrono>
#include <string>

namespace Gadgets
{
namespace Devices
{

/**
 * @brief   Interface device class for any type of device.
 */
class IDevice : public virtual Core::IObject
{
public:
    /**
     * @brief       Initialises the device.
     *
     * @gadgets_device_non_blocking
     *
     * @throws      Gadgets::Devices::DeviceException
     */
    virtual void Initialise() = 0;

    /**
     * @brief       Shutdown the device.
     *
     * @gadgets_device_non_blocking
     *
     * @throws      Gadgets::Devices::DeviceException
     */
    virtual void Shutdown() = 0;

    /**
     * @brief       Waits for the current executing action to complete, using the default device
     * timeout period.
     *
     * @throws      Gadgets::Devices::DeviceException
     */
    virtual void Wait() = 0;

    /**
     * @brief       Waits for the current executing action to complete, using the user-provided
     * timeout period.
     *
     * @param[in]   timeout_ms  The maximum amount of time to wait before a timeout occurs.
     *
     * @throws      Gadgets::Devices::DeviceException
     */
    virtual void Wait( std::chrono::milliseconds timeout_ms ) = 0;

    /**
     * @brief       Gets the name of the device.
     *
     * @return      The name of the device.
     */
    virtual std::string Name() const = 0;

    /**
     * @brief       Checks if an action is in progress.
     *
     * @return      True if an action is in progress.
     */
    virtual bool IsActionInProgress() const = 0;

protected:
    IDevice() = default;
    ~IDevice() = default;
};
} // namespace Devices
} // namespace Gadgets
