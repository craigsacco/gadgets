

#pragma once

#include <Gadgets/Core/IObject.hpp>

#include <chrono>
#include <mutex>
#include <condition_variable>

namespace Gadgets
{
	namespace Core
	{
		class Semaphore : public virtual IObject
		{
		public:
			Semaphore();
			virtual ~Semaphore();

			// overrides from IObject
			std::string Type() const final;

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
