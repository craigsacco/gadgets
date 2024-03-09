

#pragma once

#include <Gadgets/Drivers/BaseDeviceDriver.hpp>
#include <Gadgets/Devices/IDigitalOutputDriver.hpp>

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4250 )
#endif

namespace Gadgets
{
	namespace Drivers
	{
		class EmulatedDigitalOutputDriver : public BaseDeviceDriver, public virtual Devices::IDigitalOutputDriver
		{
		public:
			EmulatedDigitalOutputDriver(const std::string& name);
			virtual ~EmulatedDigitalOutputDriver();

			// overrides from IDeviceDriver
			void Initialise(std::function<void(Devices::DriverResponse)> cb) override final;
			void Shutdown(std::function<void(Devices::DriverResponse)> cb) override final;

			// overrides from IDigitalOutputDriver
			void On(std::function<void(Devices::DriverResponse)> cb) override final;
			void Off(std::function<void(Devices::DriverResponse)> cb) override final;
			void SetState(bool state, std::function<void(Devices::DriverResponse)> cb) override final;
			void GetState(std::function<void(Devices::DriverResponse, bool)> cb) override final;

		private:
			bool m_state;
		};
	}
}

#if defined(_MSC_VER)
#pragma warning( pop )
#endif
