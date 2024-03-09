

#pragma once

#include <Gadgets/Devices/IDeviceDriver.hpp>

#include <functional>
#include <memory>
#include <string>

namespace Gadgets
{
	namespace Drivers
	{
		class BaseDeviceDriver : public virtual Devices::IDeviceDriver
		{
		public:
			BaseDeviceDriver(const std::string& name, const std::string& type);
			virtual ~BaseDeviceDriver();

			// overrides from IDeviceDriver
			std::string Name() const override final;
			std::string Type() const override final;
			void SetTaskQueue(Core::ITaskQueueSPtr pTaskQueue) override final;
			Core::ITaskQueueSPtr GetTaskQueue() const override final;

		protected:
			const std::string m_name;
			const std::string m_type;
			Core::ITaskQueueSPtr m_pTaskQueue;
		};
	}
}
