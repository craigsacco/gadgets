

#pragma once

#include <Gadgets/Core/IObject.hpp>

#include <mutex>
#include <thread>

namespace Gadgets
{
    namespace Core
    {
        class Thread : public virtual IObject
        {
          public:
            Thread( const std::string& name );
            virtual ~Thread();

            void
            Start();
            void
            Stop();
            void
            Run();
            std::string
            Name() const;

            virtual void
            RunInternal() = 0;
            virtual void
            NotifyStopping();

          protected:
            enum State
            {
                Stopped,
                Started,
                Stopping,
            };
            bool
            IsStopping() const;

          private:
            const std::string m_name;
            std::thread m_thread;
            std::atomic<State> m_state;
            std::mutex m_mutex;
        };
    } // namespace Core
} // namespace Gadgets