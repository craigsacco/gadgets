

#pragma once

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
	}

	namespace Devices
	{
		class IDeviceDriver
		{
		public:
			virtual void Initialise(std::function<void(DriverResponse)> cb) = 0;
			virtual void Shutdown(std::function<void(DriverResponse)> cb) = 0;

			virtual std::string Name() const = 0;
			virtual std::string Type() const = 0;

			virtual Core::ITaskQueueSPtr GetTaskQueue() const = 0;

		protected:
			IDeviceDriver() = default;
			~IDeviceDriver() = default;
		};
	}
}
