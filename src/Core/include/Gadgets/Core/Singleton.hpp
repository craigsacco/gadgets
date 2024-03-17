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

#include <Gadgets/Core/AssertionMacros.hpp>

#include <memory>
#include <mutex>

namespace Gadgets
{
namespace Core
{
template <typename TInterface> class Singleton
{
public:
    using TInterfaceSPtr = std::shared_ptr<TInterface>;

    static TInterfaceSPtr
    Get()
    {
        std::lock_guard<std::mutex> lock( s_mutex );

        if ( s_pSingleton == nullptr )
        {
            s_pSingleton = Create();
        }

        return s_pSingleton;
    }

    static TInterfaceSPtr Create();

    static void
    Register( TInterfaceSPtr pInstance )
    {
        ASSERT_MSG( s_pSingleton == nullptr, "Singleton instance already populated" );

        std::lock_guard<std::mutex> lock( s_mutex );

        s_pSingleton = pInstance;
    }

    static void
    Destroy()
    {
        std::lock_guard<std::mutex> lock( s_mutex );

        if ( s_pSingleton != nullptr )
        {
            s_pSingleton.reset();
            s_pSingleton = nullptr;
        }
    }

private:
    Singleton() = delete;
    ~Singleton() = delete;

    static TInterfaceSPtr s_pSingleton;
    static std::mutex s_mutex;
};
} // namespace Core
} // namespace Gadgets
