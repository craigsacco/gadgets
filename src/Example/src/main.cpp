#include <Gadgets/Core/TaskQueue.hpp>
#include <Gadgets/Core/Semaphore.hpp>

void testTaskQueue()
{
    printf("Testing the task queue\n\n");

    Gadgets::Core::TaskQueue tq("main");

    printf("Starting\n");
    tq.Start();
    printf("Started\n");

    for (int i = 0; i < 50; i++)
    {
        tq.Enqueue([i] { printf("%i\n", i); });
    }

    printf("Stopping\n");
    tq.Stop();
    printf("Stopped\n");
}

void testSemaphore()
{
    printf("Testing the semaphore\n\n");

    Gadgets::Core::Semaphore semaphore;

    printf("Acquire: %d\n", semaphore.Acquire());
    std::thread thread1([&semaphore] {std::this_thread::sleep_for(std::chrono::seconds(1)); semaphore.Release(); });
    printf("Waiting: %d\n", semaphore.Wait(std::chrono::seconds(2)));
    thread1.join();

    printf("Release without acquire: %d\n", semaphore.Release());

    printf("Acquire2: %d\n", semaphore.Acquire());
    std::thread thread2([&semaphore] {std::this_thread::sleep_for(std::chrono::seconds(2)); semaphore.Release(); });
    printf("Waiting2: %d\n", semaphore.Wait(std::chrono::seconds(1)));
    printf("Overlap acquire: %d\n", semaphore.Acquire());
    thread2.join();

    printf("Acquire3: %d\n", semaphore.Acquire());
    printf("Release3: %d\n", semaphore.Release());
    printf("Waiting3: %d\n", semaphore.Wait(std::chrono::seconds(1)));
}

int main(int argc, char **argv)
{
    // testTaskQueue();
    // testSemaphore();

    return 0;
}
