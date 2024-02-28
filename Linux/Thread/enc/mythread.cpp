#include "thread.hpp"
#include <string>
#include <unistd.h>

void *routine(void *args)
{
    while (true)
    {
        std::string str = static_cast<const char *>(args);
        std::cout << str << std::endl;
        sleep(1);
    }
    return nullptr;
}

int main()
{
    Thread thread(routine, (void *)"demo", 0);

    thread.join();
}