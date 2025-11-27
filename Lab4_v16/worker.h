#pragma once

#include <barrier>

void workerFunc(int id, std::barrier<>& sync_point);
