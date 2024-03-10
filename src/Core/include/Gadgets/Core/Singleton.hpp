

#pragma once

#include <Gadgets/Core/AssertionMacros.hpp>

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

            static TInterfaceSPtr
            Create();

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
