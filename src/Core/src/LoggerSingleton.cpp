

#include <Gadgets/Core/LoggerSingleton.hpp>

#include <iostream>

namespace Gadgets
{
namespace Core
{

template <> std::shared_ptr<ILogger> Singleton<ILogger>::s_pSingleton = nullptr;

#if !defined( _MSC_VER )
template <>
#endif
std::mutex Singleton<ILogger>::s_mutex{};

template <>
std::shared_ptr<ILogger>
Singleton<ILogger>::Create()
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

std::string
LoggerSingleton::SimpleConsoleLogger::Type() const
{
    return "SimpleConsoleLogger";
}

void
LoggerSingleton::SimpleConsoleLogger::LogTrace( const std::string& component, const std::string& msg,
                                                const std::string& file, uint32_t line )
{
    Log( Level::Trace, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogDebug( const std::string& component, const std::string& msg,
                                                const std::string& file, uint32_t line )
{
    Log( Level::Debug, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogInfo( const std::string& component, const std::string& msg,
                                               const std::string& file, uint32_t line )
{
    Log( Level::Info, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogWarning( const std::string& component, const std::string& msg,
                                                  const std::string& file, uint32_t line )
{
    Log( Level::Warning, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogError( const std::string& component, const std::string& msg,
                                                const std::string& file, uint32_t line )
{
    Log( Level::Error, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogFatal( const std::string& component, const std::string& msg,
                                                const std::string& file, uint32_t line )
{
    Log( Level::Fatal, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::Log( Level level, const std::string& component, const std::string& msg,
                                           const std::string& file, uint32_t line )
{
    ( void )level;

    std::lock_guard<std::mutex> lock( m_mutex );

    if ( !component.empty() )
    {
        std::cout << " [" << component << "] ";
    }

    std::cout << msg << " [" << file << ":" << line << "]" << std::endl;
}
} // namespace Core
} // namespace Gadgets