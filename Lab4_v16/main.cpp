#include <thread>
#include <vector>
#include <barrier>
#include <syncstream>
#include <iostream>

#include "config.h"
#include "worker.h"

int main()
{
    {
        std::osyncstream out(std::cout);
        out << "Обчислення розпочато\n";
    }

    std::barrier<> sync_point(Config::nt);

    std::vector<std::thread> threads;
    threads.reserve(Config::nt);

    for (int i = 0; i < Config::nt; ++i)
    {
        threads.emplace_back(workerFunc, i, std::ref(sync_point));
    }

    for (auto& t : threads)
    {
        if (t.joinable())
            t.join();
    }

    {
        std::osyncstream out(std::cout);
        out << "Обчислення завершено\n";
    }

    return 0;
}
