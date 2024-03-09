

#include <Gadgets/Drivers/BaseDeviceDriver.hpp>
#include <Gadgets/Core/ITaskQueue.hpp>

namespace Gadgets
{
	namespace Drivers
	{
		BaseDeviceDriver::BaseDeviceDriver(const std::string& name, const std::string& type)
			: m_name(name)
			, m_type(type)
			, m_pTaskQueue(nullptr)
		{
		}

		BaseDeviceDriver::~BaseDeviceDriver()
		{
		}

		std::string BaseDeviceDriver::Name() const
		{
			return m_name;
		}

		std::string BaseDeviceDriver::Type() const
		{
			return m_type;
		}

		void BaseDeviceDriver::SetTaskQueue(Core::ITaskQueueSPtr pTaskQueue)
		{
			// TODO: check if already set

			m_pTaskQueue = pTaskQueue;
		}

		Core::ITaskQueueSPtr BaseDeviceDriver::GetTaskQueue() const
		{
			//TODO: check if not set

			return m_pTaskQueue;
		}
	}
}