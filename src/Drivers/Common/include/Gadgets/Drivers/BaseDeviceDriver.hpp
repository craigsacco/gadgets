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

#include <Gadgets/Devices/IDeviceDriver.hpp>

#include <functional>
#include <memory>
#include <string>

namespace Gadgets
{
namespace Drivers
{

/**
 * @brief   Basic implementation of a device driver.
 */
class BaseDeviceDriver : public virtual Devices::IDeviceDriver
{
public:
    /**
     * @brief       Constructor for this device driver.
     *
     * @param[in]   name    The name of the driver.
     * @param[in]   type    The type of driver as a string.
     */
    BaseDeviceDriver( const std::string& name, const std::string& type );

    /**
     * @brief       Virtual destructor.
     */
    virtual ~BaseDeviceDriver();

#pragma region "Overrides from IObject"
    std::string Type() const override final;
#pragma endregion

#pragma region "Overrides from IDeviceDriver"
    std::string Name() const override final;
    void SetTaskQueue( Core::ITaskQueueSPtr pTaskQueue ) override final;
    Core::ITaskQueueSPtr GetTaskQueue() const override final;
#pragma endregion

private:
    const std::string m_name;
    const std::string m_type;
    Core::ITaskQueueSPtr m_pTaskQueue;
};
} // namespace Drivers
} // namespace Gadgets
