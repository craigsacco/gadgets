

#pragma once

#include <Gadgets/Core/Singleton.hpp>
#include <Gadgets/Core/ILogger.hpp>

#include <memory>

namespace Gadgets
{
	namespace Core
	{
		class LoggerSingleton : public Singleton<ILogger>
		{
		public:
			class SimpleConsoleLogger : public virtual ILogger
			{
			public:
				SimpleConsoleLogger();
				virtual ~SimpleConsoleLogger();

				// overrides fron IObject
				std::string Type() const override final;

				// overrides from ILogger
				void LogTrace(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) override final;
				void LogDebug(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) override final;
				void LogInfo(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) override final;
				void LogWarning(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) override final;
				void LogError(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) override final;
				void LogFatal(const std::string& msg, const std::string& component, const std::string& file, uint32_t line) override final;
				void Log(Level level, const std::string& msg, const std::string& component, const std::string& file, uint32_t line) override final;
			
			private:
				std::mutex m_mutex;
			};

			static std::shared_ptr<ILogger> Create();

		private:
			LoggerSingleton() = delete;
			~LoggerSingleton() = delete;
		};
	}
}
