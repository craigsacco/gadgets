

#include <Gadgets/Core/TaskQueue.hpp>

namespace Gadgets
{
	namespace Core
	{
		TaskQueue::TaskQueue(const std::string& name)
			: Thread(name)
			, m_context()
			, m_workguard(boost::asio::make_work_guard(m_context))
		{
		}

		TaskQueue::~TaskQueue()
		{
		}

		std::string TaskQueue::Type() const
		{
			return "TaskQueue";
		}

		void TaskQueue::RunInternal()
		{
			for(;;)
			{
				m_context.run();
				if (IsStopping())
				{
					break;
				}
			}

			m_context.reset();
		}

		void TaskQueue::NotifyStopping()
		{
			m_context.stop();
		}

		void TaskQueue::Enqueue(std::function<void()> task)
		{
			boost::asio::post(m_context, task);
		}
	}
}