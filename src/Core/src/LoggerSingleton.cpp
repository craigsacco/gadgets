

#include <Gadgets/Core/LoggerSingleton.hpp>

#include <iostream>

namespace Gadgets
{
	namespace Core
	{
		std::shared_ptr<ILogger> Singleton<ILogger>::s_pSingleton = nullptr;
		std::mutex Singleton<ILogger>::s_mutex;

		std::shared_ptr<ILogger> Singleton<ILogger>::Create()
		{
			return std::make_shared<LoggerSingleton::SimpleConsoleLogger>();
		}

		LoggerSingleton::SimpleConsoleLogger::SimpleConsoleLogger()
			: m_mutex()
		{
		}

		LoggerSingleton::SimpleConsoleLogger::~SimpleConsoleLogger()
		{
		}

		std::string LoggerSingleton::SimpleConsoleLogger::Type() const
		{
			return "SimpleConsoleLogger";
		}

		void LoggerSingleton::SimpleConsoleLogger::LogTrace(const std::string& msg, const std::string& component, const std::string& file, uint32_t line)
		{
			Log(Level::Trace, msg, component, file, line);
		}

		void LoggerSingleton::SimpleConsoleLogger::LogDebug(const std::string& msg, const std::string& component, const std::string& file, uint32_t line)
		{
			Log(Level::Debug, msg, component, file, line);
		}
		
		void LoggerSingleton::SimpleConsoleLogger::LogInfo(const std::string& msg, const std::string& component, const std::string& file, uint32_t line)
		{
			Log(Level::Info, msg, component, file, line);
		}

		void LoggerSingleton::SimpleConsoleLogger::LogWarning(const std::string& msg, const std::string& component, const std::string& file, uint32_t line)
		{
			Log(Level::Warning, msg, component, file, line);
		}

		void LoggerSingleton::SimpleConsoleLogger::LogError(const std::string& msg, const std::string& component, const std::string& file, uint32_t line)
		{
			Log(Level::Error, msg, component, file, line);
		}

		void LoggerSingleton::SimpleConsoleLogger::LogFatal(const std::string& msg, const std::string& component, const std::string& file, uint32_t line)
		{
			Log(Level::Fatal, msg, component, file, line);
		}

		void LoggerSingleton::SimpleConsoleLogger::Log(Level level, const std::string& msg, const std::string& component, const std::string& file, uint32_t line)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			std::cout << msg;
			if (!component.empty())
			{
				std::cout << " [" << component << "]";
			}

			std::cout << " [" << file << ":" << line << "]" << std::endl;
		}
	}
}