

#include <Gadgets/Drivers/BaseDeviceDriver.hpp>
#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Core/AssertionMacros.hpp>

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

		std::string BaseDeviceDriver::Type() const
		{
			return m_type;
		}

		std::string BaseDeviceDriver::Name() const
		{
			return m_name;
		}

		void BaseDeviceDriver::SetTaskQueue(Core::ITaskQueueSPtr pTaskQueue)
		{
			ASSERT_MSG(m_pTaskQueue == nullptr, "Task queue already set");

			m_pTaskQueue = pTaskQueue;
		}

		Core::ITaskQueueSPtr BaseDeviceDriver::GetTaskQueue() const
		{
			ASSERT_MSG(m_pTaskQueue != nullptr, "Task queue not set");

			return m_pTaskQueue;
		}
	}
}