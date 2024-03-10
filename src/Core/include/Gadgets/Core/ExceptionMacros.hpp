

#pragma once

#include <Gadgets/Core/CommonMacros.hpp>

#include <stdexcept>

#define THROW_EXCEPTION_IMPL( exception_type, msg )                                                                    \
    throw exception_type( msg " [" __FILE__ ":" STRINGIZE(__LINE__) "]" )

#define THROW_LOGIC_ERROR( msg ) THROW_EXCEPTION_IMPL( std::logic_error, msg )

#define THROW_RUNTIME_ERROR( msg ) THROW_EXCEPTION_IMPL( std::runtime_error, msg )

#define THROW_OUT_OF_RANGE_ERROR( msg ) THROW_EXCEPTION_IMPL( std::out_of_range, msg )
