

#pragma once

#include <Gadgets/Core/Thread.hpp>
#include <Gadgets/Core/ITaskQueue.hpp>

#include <boost/asio.hpp>

namespace Gadgets
{
	namespace Core
	{
		class TaskQueue : public Thread, public virtual ITaskQueue
		{
		public:
			TaskQueue(const std::string& name);
			virtual ~TaskQueue();

			// overrides from Thread
			void RunInternal() override;
			void NotifyStopping() override;

			// overrides from ITaskQueue
			void Enqueue(std::function<void()> task) override;

		private:
			boost::asio::io_context m_context;
			boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workguard;
		};
	}
}
