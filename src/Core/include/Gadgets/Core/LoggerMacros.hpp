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

#pragma once

#include <Gadgets/Core/CommonMacros.hpp>
#include <Gadgets/Core/LoggerSingleton.hpp>

#define LOG_IMPL( level, component, msg )                                                          \
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
