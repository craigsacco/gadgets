

#pragma once

#include <Gadgets/Devices/IDevice.hpp>
#include <Gadgets/Devices/DriverResponse.hpp>
#include <Gadgets/Core/Semaphore.hpp>

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
			BaseDevice(const std::string& name, const std::string& type, IDeviceDriverSPtr pDriver);
			virtual ~BaseDevice();

			// overrides from IDevice
			void Initialise() override final;
			void Shutdown() override final;
			void Wait(std::chrono::milliseconds timeout_ms) override final;
			std::string Name() const override final;
			std::string Type() const override final;

		protected:
			void StartAsyncAction();
			void FinaliseAsyncAction(DeviceResponse response);
			virtual DeviceResponse ToDeviceResponse(DriverResponse response) const = 0;

		private:
			const std::string m_name;
			const std::string m_type;
			IDeviceDriverSPtr m_pDriver;
			Gadgets::Core::Semaphore m_semaphore;
		};
	}
}