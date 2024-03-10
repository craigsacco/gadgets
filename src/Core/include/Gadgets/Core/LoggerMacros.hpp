

#pragma once

#include <Gadgets/Core/CommonMacros.hpp>
#include <Gadgets/Core/LoggerSingleton.hpp>

#define LOG_IMPL( level, component, msg )                                                                              \
    Gadgets::Core::LoggerSingleton::Get()->Log( level, component, msg, __FILE__, __LINE__ )

#define LOG_TRACE( msg ) LOG_IMPL( Gadgets::Core::ILogger::Trace, "", msg )

#define LOG_DEBUG( msg ) LOG_IMPL( Gadgets::Core::ILogger::Debug, "", msg )

#define LOG_INFO( msg ) LOG_IMPL( Gadgets::Core::ILogger::Info, "", msg )

#define LOG_WARNING( msg ) LOG_IMPL( Gadgets::Core::ILogger::Warning, "", msg )

#define LOG_ERROR( msg ) LOG_IMPL( Gadgets::Core::ILogger::Error, "", msg )

#define LOG_FATAL( msg ) LOG_IMPL( Gadgets::Core::ILogger::Fatal, "", msg )

#define LOG_TRACE_INTERNAL( msg ) LOG_IMPL( Gadgets::Core::ILogger::Trace, Type(), msg )

#define LOG_DEBUG_INTERNAL( msg ) LOG_IMPL( Gadgets::Core::ILogger::Debug, Type(), msg )

#define LOG_INFO_INTERNAL( msg ) LOG_IMPL( Gadgets::Core::ILogger::Info, Type(), msg )

#define LOG_WARNING_INTERNAL( msg ) LOG_IMPL( Gadgets::Core::ILogger::Warning, Type(), msg )

#define LOG_ERROR_INTERNAL( msg ) LOG_IMPL( Gadgets::Core::ILogger::Error, Type(), msg )

#define LOG_FATAL_INTERNAL( msg ) LOG_IMPL( Gadgets::Core::ILogger::Fatal, Type(), msg )
