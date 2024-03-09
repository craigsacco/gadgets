

#pragma once

#include <Gadgets/Devices/BaseDevice.hpp>
#include <Gadgets/Devices/IDigitalOutputDevice.hpp>

#include <memory>

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4250 )
#endif

namespace Gadgets
{
	namespace Devices
	{
		class IDigitalOutputDriver;
		using IDigitalOutputDriverSPtr = std::shared_ptr<IDigitalOutputDriver>;

		class DigitalOutputDevice : public BaseDevice, public virtual IDigitalOutputDevice
		{
		public:
			DigitalOutputDevice(const std::string& name, IDigitalOutputDriverSPtr pDriver);
			virtual ~DigitalOutputDevice();

			// overrides from DigitalOutputDevice
			void On() override final;
			void Off() override final;
			void SetState(bool state) override final;
			bool GetState() override final;

		protected:
			// overrides from BaseDevice
			DeviceResponse ToDeviceResponse(DriverResponse response) const override final;

		private:
			IDigitalOutputDriverSPtr m_pDriver;
		};
	}
}

#if defined(_MSC_VER)
#pragma warning( pop )
#endif
