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

#include <Gadgets/Devices/IDigitalOutputDriver.hpp>
#include <Gadgets/Drivers/BaseDeviceDriver.hpp>

#if defined( _MSC_VER )
// methods inherited by dominance are fine - inhibit this warning (cleared at end
// of file)
#pragma warning( push )
#pragma warning( disable : 4250 )
#endif

namespace Gadgets
{
namespace Drivers
{

/**
 * @brief   Implementation of an emumated digital output driver.
 */
class EmulatedDigitalOutputDriver
    : public BaseDeviceDriver
    , public virtual Devices::IDigitalOutputDriver
{
public:
    /**
     * @brief       Constructor for an emulated digital output driver.
     *
     * @param[in]   name    The name of the driver.
     */
    EmulatedDigitalOutputDriver( const std::string& name );

    /**
     * @brief       Virtual destructor.
     */
    virtual ~EmulatedDigitalOutputDriver();

#pragma region "Overrides from IDeviceDriver"
    //! @copydoc Gadgets::Devices::IDeviceDriver::Initialise
    void Initialise( std::function<void( Devices::DriverResponse )> cb ) override final;
    //! @copydoc Gadgets::Devices::IDeviceDriver::Shutdown
    void Shutdown( std::function<void( Devices::DriverResponse )> cb ) override final;
#pragma endregion

#pragma region "Overrides from IDigitalOutputDriver"
    //! @copydoc Gadgets::Devices::IDigitalOutputDriver::On
    void On( std::function<void( Devices::DriverResponse )> cb ) override final;
    //! @copydoc Gadgets::Devices::IDigitalOutputDriver::Off
    void Off( std::function<void( Devices::DriverResponse )> cb ) override final;
    //! @copydoc Gadgets::Devices::IDigitalOutputDriver::SetState
    void SetState( bool state, std::function<void( Devices::DriverResponse )> cb ) override final;
    //! @copydoc Gadgets::Devices::IDigitalOutputDriver::GetState
    void GetState( std::function<void( Devices::DriverResponse, bool )> cb ) override final;
#pragma endregion

private:
    bool m_state;
};
} // namespace Drivers
} // namespace Gadgets

#if defined( _MSC_VER )
#pragma warning( pop )
#endif
