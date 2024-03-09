

#include <Gadgets/Core/Thread.hpp>

namespace Gadgets
{
	namespace Core
	{
		Thread::Thread(const std::string& name)
			: m_name(name)
			, m_thread()
			, m_state(Stopped)
			, m_mutex()
		{
		}

		Thread::~Thread()
		{
			Stop();
		}

		void Thread::Start()
		{
			std::lock_guard lock(m_mutex);

			if (m_state == Stopped)
			{
				m_state = Started;
				m_thread = std::thread([this]() { this->Run(); });
			}
		}

		void Thread::Stop()
		{
			std::lock_guard lock(m_mutex);

			if (m_state == Started)
			{
				m_state = Stopping;
				NotifyStopping();
				m_thread.join();
				m_thread = std::thread();
			}
		}

		void Thread::Run()
		{
			RunInternal();
			m_state = Stopped;
		}

		void Thread::NotifyStopping()
		{
			// by default, do nothing
		}

		std::string Thread::Name() const
		{
			return m_name;
		}

		bool Thread::IsStopping() const
		{
			return (m_state == Stopping);
		}
	}
}