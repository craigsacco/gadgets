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
// Forward declarations
class IDigitalOutputDriver;
using IDigitalOutputDriverSPtr = std::shared_ptr<IDigitalOutputDriver>;

/**
 * @brief   Implementation of a digital output device.
 */
class DigitalOutputDevice
    : public BaseDevice
    , public virtual IDigitalOutputDevice
{
public:
    /**
     * @brief       Constructor for an digital output device.
     *
     * @param[in]   name    The name of the device.
     * @param[in]   pDriver The driver instance assigned to the device.
     */
    DigitalOutputDevice( const std::string& name, IDigitalOutputDriverSPtr pDriver );

    /**
     * @brief       Virtual destructor.
     */
    virtual ~DigitalOutputDevice();

#pragma region "Overrides from DigitalOutputDevice"
    void On() override final;
    void Off() override final;
    void SetState( bool state ) override final;
    bool GetState() override final;
#pragma endregion

protected:
#pragma region "Overrides from BaseDevice"
    DeviceResponse ToDeviceResponse( DriverResponse response ) const override final;
    void HandleActionResponse( DeviceResponse response ) const override final;
#pragma endregion

private:
    IDigitalOutputDriverSPtr m_pDriver;
};
} // namespace Devices
} // namespace Gadgets

#if defined( _MSC_VER )
#pragma warning( pop )
#endif
