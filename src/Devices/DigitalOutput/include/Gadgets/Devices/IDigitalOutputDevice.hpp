

#pragma once

#include <Gadgets/Devices/IDevice.hpp>

#include <chrono>
#include <string>

namespace Gadgets
{
    namespace Devices
    {
        class IDigitalOutputDevice : public virtual IDevice
        {
          public:
            virtual void
            On() = 0;
            virtual void
            Off() = 0;
            virtual void
            SetState( bool state ) = 0;
            virtual bool
            GetState() = 0;

          protected:
            IDigitalOutputDevice() = default;
            ~IDigitalOutputDevice() = default;
        };
    } // namespace Devices
} // namespace Gadgets
