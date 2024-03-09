

#pragma once

#include <chrono>
#include <mutex>
#include <condition_variable>

namespace Gadgets
{
	namespace Core
	{
		class Semaphore
		{
		public:
			Semaphore();
			virtual ~Semaphore();

			bool Acquire();
			bool Release();
			bool Wait(std::chrono::milliseconds timeout_ms);

		private:
			std::mutex m_mutex;
			std::condition_variable m_cv;
			bool m_acquired;
		};
	}
}
