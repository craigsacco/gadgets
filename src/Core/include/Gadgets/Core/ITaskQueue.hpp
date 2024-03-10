

#pragma once

#include <functional>

namespace Gadgets
{
namespace Core
{
class ITaskQueue
{
public:
    virtual void Enqueue( std::function<void()> task ) = 0;

protected:
    ITaskQueue() = default;
    ~ITaskQueue() = default;
};
} // namespace Core
} // namespace Gadgets
