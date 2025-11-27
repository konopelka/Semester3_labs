#include "worker.h"
#include "config.h"
#include <syncstream>
#include <iostream>
#include <algorithm>

static void doAction(char setName, int index)
{
    std::osyncstream out(std::cout);
    out << "З набору " << setName << " виконано дію " << index << "\n";
}

static void runSet(char setName, int totalCount, int threadId)
{
    if (totalCount <= 0)
        return;

    int base = totalCount / Config::nt;
    int rem = totalCount % Config::nt;

    int myCount = base + (threadId < rem ? 1 : 0);

    int startIndex = base * threadId + std::min(threadId, rem) + 1;
    int endIndex = startIndex + myCount - 1;

    for (int i = startIndex; i <= endIndex; ++i)
    {
        doAction(setName, i);
    }
}

void workerFunc(int id, std::barrier<>& sync_point)
{
    runSet('a', Config::a_count, id);
    sync_point.arrive_and_wait();

    runSet('b', Config::b_count, id);
    runSet('c', Config::c_count, id);
    runSet('d', Config::d_count, id);
    sync_point.arrive_and_wait();

    runSet('e', Config::e_count, id);
    runSet('f', Config::f_count, id);
    runSet('g', Config::g_count, id);
    runSet('h', Config::h_count, id);
    sync_point.arrive_and_wait();

    runSet('i', Config::i_count, id);
    runSet('j', Config::j_count, id);
    sync_point.arrive_and_wait();
}
