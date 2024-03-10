

#pragma once

#include <Gadgets/Core/IObject.hpp>

#include <string>

namespace Gadgets
{
	namespace Core
	{
		class ILogger : public virtual IObject
		{
		public:
			virtual void LogTrace(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) = 0;
			virtual void LogDebug(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) = 0;
			virtual void LogInfo(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) = 0;
			virtual void LogWarning(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) = 0;
			virtual void LogError(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) = 0;
			virtual void LogFatal(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) = 0;
			
			enum Level
			{
				Trace,
				Debug,
				Info,
				Warning,
				Error,
				Fatal,
			};
			virtual void Log(Level level, const std::string& msg, const std::string& component, const std::string& file, uint32_t line) = 0;

		protected:
			ILogger() = default;
			~ILogger() = default;
		};
	}
}
