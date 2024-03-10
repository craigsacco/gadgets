

#pragma once

#include <Gadgets/Core/ITaskQueue.hpp>
#include <Gadgets/Core/Thread.hpp>

#include <boost/asio.hpp>

namespace Gadgets
{
namespace Core
{
class TaskQueue : public Thread, public virtual ITaskQueue
{
public:
    TaskQueue( const std::string& name );
    virtual ~TaskQueue();

    // overrides from IObject
    std::string Type() const final;

    // overrides from Thread
    void RunInternal() override final;
    void NotifyStopping() override final;

    // overrides from ITaskQueue
    void Enqueue( std::function<void()> task ) override final;

private:
    boost::asio::io_context m_context;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workguard;
};
} // namespace Core
} // namespace Gadgets
