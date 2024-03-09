#include <Gadgets/Core/TaskQueue.hpp>

int main(int argc, char **argv)
{
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
