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

#include <Gadgets/Core/Semaphore.hpp>
#include <Gadgets/Devices/DriverResponse.hpp>
#include <Gadgets/Devices/IDevice.hpp>

#include <memory>

namespace Gadgets
{
namespace Devices
{
class IDeviceDriver;
using IDeviceDriverSPtr = std::shared_ptr<IDeviceDriver>;

class BaseDevice : public virtual IDevice
{
public:
    BaseDevice( const std::string& name, const std::string& type, IDeviceDriverSPtr pDriver );
    virtual ~BaseDevice();

    // overrides from IObject
    std::string Name() const override final;

    // overrides from IDevice
    void Initialise() override final;
    void Shutdown() override final;
    void Wait() override final;
    void Wait( std::chrono::milliseconds timeout_ms ) override final;
    std::string Type() const override final;

    std::chrono::milliseconds DefaultTimeout() const;

protected:
    void StartAsyncAction();
    void FinaliseAsyncAction( DeviceResponse response );
    virtual DeviceResponse ToDeviceResponse( DriverResponse response ) const;
    virtual void ResponseThrowOnError( DeviceResponse response ) const;

private:
    const std::string m_name;
    const std::string m_type;
    IDeviceDriverSPtr m_pDriver;
    Gadgets::Core::Semaphore m_semaphore;
};
} // namespace Devices
} // namespace Gadgets