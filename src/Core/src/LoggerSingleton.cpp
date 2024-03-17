/*
 * Copyright (c) 2024 Craig Sacco
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Gadgets/Core/LoggerSingleton.hpp>

#include <iostream>

namespace Gadgets
{
namespace Core
{

template <> std::shared_ptr<ILogger> Singleton<ILogger>::s_pSingleton = nullptr;

#if !defined( _MSC_VER )
// fails to link with undefined reference - do not add declaration for MSVC
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
LoggerSingleton::SimpleConsoleLogger::LogTrace( const std::string& component,
                                                const std::string& msg, const std::string& file,
                                                uint32_t line )
{
    Log( Level::Trace, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogDebug( const std::string& component,
                                                const std::string& msg, const std::string& file,
                                                uint32_t line )
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
LoggerSingleton::SimpleConsoleLogger::LogWarning( const std::string& component,
                                                  const std::string& msg, const std::string& file,
                                                  uint32_t line )
{
    Log( Level::Warning, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogError( const std::string& component,
                                                const std::string& msg, const std::string& file,
                                                uint32_t line )
{
    Log( Level::Error, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::LogFatal( const std::string& component,
                                                const std::string& msg, const std::string& file,
                                                uint32_t line )
{
    Log( Level::Fatal, component, msg, file, line );
}

void
LoggerSingleton::SimpleConsoleLogger::Log( Level level, const std::string& component,
                                           const std::string& msg, const std::string& file,
                                           uint32_t line )
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