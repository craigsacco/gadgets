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

#include <Gadgets/Devices/IDevice.hpp>

#include <chrono>
#include <string>

namespace Gadgets
{
namespace Devices
{

/**
 * @brief   Interface device class for a digital output.
 */
class IDigitalOutputDevice : public virtual IDevice
{
public:
    /**
     * @brief       Turns the digital output on.
     *
     * @gadgets_device_non_blocking
     *
     * @throws      Gadgets::Devices::DeviceException
     */
    virtual void On() = 0;

    /**
     * @brief       Turns the digital output off.
     *
     * @gadgets_device_non_blocking
     *
     * @throws      Gadgets::Devices::DeviceException
     */
    virtual void Off() = 0;

    /**
     * @brief       Turns the digital output to the desired state.
     *
     * @gadgets_device_non_blocking
     *
     * @param[in]   state   The state of the output.
     */
    virtual void SetState( bool state ) = 0;

    /**
     * @brief       Gets the current state of the digital output.
     *
     * @gadgets_device_blocking
     *
     * @return      The current state of the output.
     */
    virtual bool GetState() = 0;

protected:
    IDigitalOutputDevice() = default;
    ~IDigitalOutputDevice() = default;
};
} // namespace Devices
} // namespace Gadgets
