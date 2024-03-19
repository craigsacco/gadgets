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
#include <Gadgets/Devices/DriverResponse.hpp>

#include <functional>
#include <memory>
#include <string>

namespace Gadgets
{
namespace Core
{
class ITaskQueue;
using ITaskQueueSPtr = std::shared_ptr<ITaskQueue>;
} // namespace Core

namespace Devices
{

/**
 * @brief   Interface driver class for any type of device.
 */
class IDeviceDriver : public virtual Core::IObject
{
public:
    /**
     * @brief       Initialises the driver.
     *
     * @gadgets_driver_async
     *
     * @param[in]   cb  The callback function to run at the completion of the underlying action
     * containing the driver response.
     */
    virtual void Initialise( std::function<void( DriverResponse )> cb ) = 0;

    /**
     * @brief       Shutdown the driver.
     *
     * @gadgets_driver_async
     *
     * @param[in]   cb  The callback function to run at the completion of the underlying action
     * containing the driver response.
     */
    virtual void Shutdown( std::function<void( DriverResponse )> cb ) = 0;

    /**
     * @brief       Gets the name of the driver.
     *
     * @return      The name of the driver.
     */
    virtual std::string Name() const = 0;

    /**
     * @brief       Sets the task queue instance to use for synchronising internal operations within
     * the driver.
     *
     * @param[in]   pTaskQueue  The task queue instance to assign to the driver.
     */
    virtual void SetTaskQueue( Core::ITaskQueueSPtr pTaskQueue ) = 0;

    /**
     * @brief       Gets the task queue instance from the driver.
     *
     * @return      The task queue instance.
     */
    virtual Core::ITaskQueueSPtr GetTaskQueue() const = 0;

protected:
    IDeviceDriver() = default;
    ~IDeviceDriver() = default;
};
} // namespace Devices
} // namespace Gadgets
