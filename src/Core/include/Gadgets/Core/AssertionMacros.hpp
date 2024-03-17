

#pragma once

#include <Gadgets/Core/ExceptionMacros.hpp>

#define ASSERT_MSG( eval, msg )                                                                    \
    if ( !( eval ) )                                                                               \
    {                                                                                              \
        THROW_LOGIC_ERROR( "Assertion failed: " msg );                                             \
    }

#define ASSERT( eval ) ASSERT_MSG( eval, (##eval ) )
