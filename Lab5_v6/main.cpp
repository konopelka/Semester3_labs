#include <iostream>
#include <string>
#include <chrono>
#include <future>
#include <thread>
#include <syncstream>

using namespace std::chrono_literals;

void do_step(const std::string& name, int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::osyncstream out(std::cout);
    out << name << '\n';
}

void quick(const std::string& name)
{
    do_step(name, 1);
}

void slow(const std::string& name)
{
    do_step(name, 7);
}

void work()
{
    using Clock = std::chrono::steady_clock;

    auto startTime = Clock::now();

    std::promise<void> b1FinishedPromise;
    std::shared_future<void> b1Finished = b1FinishedPromise.get_future().share();

    auto firstWorker = std::async(std::launch::async,
        [p = std::move(b1FinishedPromise)]() mutable
        {
            quick("A1");
            slow("A2");
            quick("B1");

            p.set_value();
        });

    auto secondWorker = std::async(std::launch::async,
        [b1Finished]()
        {
            quick("A3");
            slow("B2");
            quick("C2");

            b1Finished.wait();
            quick("C1");
        });

    firstWorker.get();
    secondWorker.get();

    auto finishTime = Clock::now();
    auto elapsedSeconds =
        std::chrono::duration_cast<std::chrono::seconds>(finishTime - startTime).count();

    std::osyncstream out(std::cout);
    out << "Time: " << elapsedSeconds << " seconds\n";
    out << "Work is done!";
}

int main()
{
    work();
    return 0;
}
