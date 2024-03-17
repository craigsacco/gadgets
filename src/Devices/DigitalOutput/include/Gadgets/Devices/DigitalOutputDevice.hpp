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

#include <Gadgets/Devices/BaseDevice.hpp>
#include <Gadgets/Devices/IDigitalOutputDevice.hpp>

#include <memory>

#if defined( _MSC_VER )
// methods inherited by dominance are fine - inhibit this warning (cleared at end
// of file)
#pragma warning( push )
#pragma warning( disable : 4250 )
#endif

namespace Gadgets
{
namespace Devices
{
class IDigitalOutputDriver;
using IDigitalOutputDriverSPtr = std::shared_ptr<IDigitalOutputDriver>;

class DigitalOutputDevice
    : public BaseDevice
    , public virtual IDigitalOutputDevice
{
public:
    DigitalOutputDevice( const std::string& name, IDigitalOutputDriverSPtr pDriver );
    virtual ~DigitalOutputDevice();

    // overrides from DigitalOutputDevice
    void On() override final;
    void Off() override final;
    void SetState( bool state ) override final;
    bool GetState() override final;

protected:
    // overrides from BaseDevice
    DeviceResponse ToDeviceResponse( DriverResponse response ) const override final;
    void ResponseThrowOnError( DeviceResponse response ) const override final;

private:
    IDigitalOutputDriverSPtr m_pDriver;
};
} // namespace Devices
} // namespace Gadgets

#if defined( _MSC_VER )
#pragma warning( pop )
#endif
