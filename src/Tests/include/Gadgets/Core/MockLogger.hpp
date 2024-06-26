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

// SPDX-License-Identifier: MIT

#pragma once

#include <Gadgets/Core/ILogger.hpp>

#include <gmock/gmock.h>

namespace Gadgets
{
namespace Core
{

class MockLogger : public virtual ILogger
{
public:
    MockLogger() = default;
    virtual ~MockLogger() = default;

#pragma region "Overrides from IObject"
    std::string
    Type() const
    {
        return "MockLogger";
    }
#pragma endregion

#pragma region "Overrides from ILogger"
    MOCK_METHOD4( LogTrace, void( const std::string& component, const std::string& msg,
                                  const std::string& file, uint32_t line ) );
    MOCK_METHOD4( LogDebug, void( const std::string& component, const std::string& msg,
                                  const std::string& file, uint32_t line ) );
    MOCK_METHOD4( LogInfo, void( const std::string& component, const std::string& msg,
                                 const std::string& file, uint32_t line ) );
    MOCK_METHOD4( LogWarning, void( const std::string& component, const std::string& msg,
                                    const std::string& file, uint32_t line ) );
    MOCK_METHOD4( LogError, void( const std::string& component, const std::string& msg,
                                  const std::string& file, uint32_t line ) );
    MOCK_METHOD4( LogFatal, void( const std::string& component, const std::string& msg,
                                  const std::string& file, uint32_t line ) );
    MOCK_METHOD5( Log, void( Level level, const std::string& component, const std::string& msg,
                             const std::string& file, uint32_t line ) );
#pragma endregion
};
} // namespace Core
} // namespace Gadgets
