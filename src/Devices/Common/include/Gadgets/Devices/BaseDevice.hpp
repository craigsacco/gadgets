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

#include <Gadgets/Core/Semaphore.hpp>
#include <Gadgets/Devices/DeviceException.hpp>
#include <Gadgets/Devices/DriverResponse.hpp>
#include <Gadgets/Devices/IDevice.hpp>

#include <memory>

namespace Gadgets
{
namespace Devices
{

#define THROW_DEVICE_EXCEPTION( msg, response )                                                    \
    throw Gadgets::Devices::DeviceException( msg " [" __FILE__ ":" STRINGIZE(__LINE__) "]",        \
                                                                             response )

// Forward declarations
class IDeviceDriver;
using IDeviceDriverSPtr = std::shared_ptr<IDeviceDriver>;

/**
 * @brief   Basic implementation of a device.
 */
class BaseDevice : public virtual IDevice
{
protected:
    /**
     * @brief       Constructor for this device.
     *
     * @param[in]   name    The name of the driver.
     * @param[in]   type    The type of device as a string.
     * @param[in]   pDriver The driver instance assigned to the device.
     */
    BaseDevice( const std::string& name, const std::string& type, IDeviceDriverSPtr pDriver );

    /**
     * @brief       Virtual destructor.
     */
    virtual ~BaseDevice();

public:
#pragma region "Overrides from IObject"
    std::string Type() const override final;
#pragma endregion

#pragma region "Overrides from IDevice"
    void Initialise() override final;
    void Shutdown() override final;
    void Wait() override final;
    void Wait( std::chrono::milliseconds timeout_ms ) override final;
    std::string Name() const override final;
    bool IsActionInProgress() const override final;
#pragma endregion

    /**
     * @brief       Gets the default timeout period for any action that needs to await using the
     * Wait() method.
     *
     * @return      The default timeout period.
     */
    std::chrono::milliseconds DefaultTimeout() const;

protected:
    /**
     * @brief       Internally starts the asynchronous operation and prevents any other operation
     * from occurring on this device.
     *
     * @note        A call to FinaliseAsyncAction(...) will complete the current operation in
     * progress.
     */
    void StartAsyncAction();

    /**
     * @brief       Finalises the current operation and allows new operations to occur on this
     * device.
     *
     * @param[in]   response    The response code of the operation that just completed.
     */
    void FinaliseAsyncAction( DeviceResponse response );

    /**
     * @brief       Converts the driver response code to a device response code.
     *
     * @param[in]   response    The driver response code to convert.
     * @return      The device response code.
     */
    virtual DeviceResponse ToDeviceResponse( DriverResponse response ) const;

    /**
     * @brief       Handles the response from the action that just complete.
     *
     * @param[in]   response    The device response code to handle.
     */
    virtual void HandleActionResponse( DeviceResponse response ) const;

private:
    const std::string m_name;
    const std::string m_type;
    IDeviceDriverSPtr m_pDriver;
    Gadgets::Core::Semaphore m_semaphore;
    DeviceResponse m_lastActionResponse;
};
} // namespace Devices
} // namespace Gadgets