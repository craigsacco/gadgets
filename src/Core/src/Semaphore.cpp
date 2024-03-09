

#include <Gadgets/Core/Semaphore.hpp>

namespace Gadgets
{
	namespace Core
	{
		Semaphore::Semaphore()
			: m_mutex()
			, m_cv()
			, m_acquired(false)
		{
		}

		Semaphore::~Semaphore()
		{
		}

		bool Semaphore::Acquire()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (!m_acquired)
			{
				m_acquired = true;
				return true;
			}
			else
			{
				return false;
			}
		}

		bool Semaphore::Release()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_acquired)
			{
				m_acquired = false;
				m_cv.notify_all();
				return true;
			}
			else
			{
				return false;
			}
		}

		bool Semaphore::Wait(std::chrono::milliseconds timeout_ms)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			if (m_acquired)
			{
				return (m_cv.wait_for(lock, timeout_ms) == std::cv_status::no_timeout);
			}
			else
			{
				return true;
			}
		}
	}
}