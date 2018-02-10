#ifndef GRID_PROCESSOR_H
#define GRID_PROCESSOR_H

#include <thread>
#include <vector>
#include <mutex>
#include <cmath>

#include "util/Grid.h"

struct GPThreadInfo
{
    int origin;
    int depth;
    std::thread t;

    GPThreadInfo(int origin, int depth)
    {
        this->origin = origin;
        this->depth = depth;
    }
};

class GridProcessor
{
private:
    Grid* grid;
    int threadCount;

    void processChunk(int origin, int depth);
    void processCell(ConwayCell* cell);

    void finalize();

    std::vector<GPThreadInfo *> loadInfo;
    void splitLoad();
    void clearLoadInfo();

    int width, height;

public:
    GridProcessor(Grid* grid, int threads = 2);
    ~GridProcessor();

    Grid* GetRawGrid();

    void ResetGrid(Grid* grid);

    void Step();

    int Width();
    int Height();

    int ThreadCount();
    void SetThreadCount(int threadCount);
};

#endif //GRID_PROCESSOR_H
