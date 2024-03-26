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
#include <Gadgets/Core/MockLogger.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <thread>

using namespace ::testing;

int
LoggerSingletonTests()
{
    return 0;
}

namespace Gadgets
{
namespace Core
{
class LoggerSingletonTests : public Test
{
public:
    void
    SetUp() override
    {
    }

    void
    TearDown() override
    {
        LoggerSingleton::Destroy();
    }
};

TEST_F( LoggerSingletonTests, UsingRegisteredObject )
{
    auto pLogger = std::make_shared<StrictMock<MockLogger>>();
    LoggerSingleton::Register( pLogger );

    {
        InSequence sequence;
        EXPECT_CALL( *pLogger, LogTrace( "Comp1", "Msg1", "File1", 1 ) ).Times( 1 );
        EXPECT_CALL( *pLogger, LogDebug( "Comp2", "Msg2", "File2", 2 ) ).Times( 1 );
        EXPECT_CALL( *pLogger, LogInfo( "Comp3", "Msg3", "File3", 3 ) ).Times( 1 );
        EXPECT_CALL( *pLogger, LogWarning( "Comp4", "Msg4", "File4", 4 ) ).Times( 1 );
        EXPECT_CALL( *pLogger, LogError( "Comp5", "Msg5", "File5", 5 ) ).Times( 1 );
        EXPECT_CALL( *pLogger, LogFatal( "Comp6", "Msg6", "File6", 6 ) ).Times( 1 );
    }

    LoggerSingleton::Get()->LogTrace( "Comp1", "Msg1", "File1", 1 );
    LoggerSingleton::Get()->LogDebug( "Comp2", "Msg2", "File2", 2 );
    LoggerSingleton::Get()->LogInfo( "Comp3", "Msg3", "File3", 3 );
    LoggerSingleton::Get()->LogWarning( "Comp4", "Msg4", "File4", 4 );
    LoggerSingleton::Get()->LogError( "Comp5", "Msg5", "File5", 5 );
    LoggerSingleton::Get()->LogFatal( "Comp6", "Msg6", "File6", 6 );
}

TEST_F( LoggerSingletonTests, CannotRegisterTwice )
{
    auto pLogger = std::make_shared<StrictMock<MockLogger>>();
    ASSERT_NO_THROW( LoggerSingleton::Register( pLogger ) );

    auto pLogger2 = std::make_shared<StrictMock<MockLogger>>();
    ASSERT_THROW( LoggerSingleton::Register( pLogger2 ), std::logic_error );
}

TEST_F( LoggerSingletonTests, UsingDefaultObject )
{
    LoggerSingleton::Get()->LogTrace( "Comp1", "Msg1", "File1", 1 );
    LoggerSingleton::Get()->LogDebug( "Comp2", "Msg2", "File2", 2 );
    LoggerSingleton::Get()->LogInfo( "Comp3", "Msg3", "File3", 3 );
    LoggerSingleton::Get()->LogWarning( "Comp4", "Msg4", "File4", 4 );
    LoggerSingleton::Get()->LogError( "Comp5", "Msg5", "File5", 5 );
    LoggerSingleton::Get()->LogFatal( "Comp6", "Msg6", "File6", 6 );
}

} // namespace Core
} // namespace Gadgets
