#include "GridProcessor.h"

GridProcessor::GridProcessor(Grid* grid, int threads)
{
    this->grid = grid;
    this->threadCount = threads;

    splitLoad();

    width = grid->Width();
    height = grid->Height();
}

GridProcessor::~GridProcessor()
{
    clearLoadInfo();
}

void GridProcessor::finalize()
{
    grid->Update();
}

void GridProcessor::Step()
{
    for(GPThreadInfo* info : loadInfo)
    {
        info->t = std::thread(&GridProcessor::processChunk, this, info->origin, info->depth);
    }

    for(GPThreadInfo* info : loadInfo)
    {
        info->t.join();
    }

    finalize();
}

void GridProcessor::processChunk(int origin, int depth)
{
    std::vector<ConwayCell*>* cells = grid->GetRows(origin, depth);

    for(ConwayCell* cell : *cells)
    {
        processCell(cell);
    }

    delete cells;
}

void GridProcessor::processCell(ConwayCell *cell)
{
    int living = 0;
    std::vector<ConwayCell*>* neighbours = grid->Neighbours(cell->posX, cell->posY);
    for(ConwayCell* neighbour : *neighbours)
    {
        if(neighbour->alive)
            living++;
    }

    if(!cell->alive && living == 3)
        cell->SetState(true);
    else if(cell->alive && (living < 2 || living > 3))
        cell->SetState(false);

    delete neighbours;
}

void GridProcessor::splitLoad()
{
    clearLoadInfo();

    if(threadCount > grid->Height())
        threadCount = grid->Height();

    int secLen = ceil( grid->Height() / threadCount );
    int origin = 0;

    for(int i = 0; i < threadCount; i++)
    {
        if(origin > grid->Height())
            break;

        if(origin + secLen >= grid->Height())
        {
            loadInfo.push_back(new GPThreadInfo(origin, grid->Height()));
            break;
        }
        else
            loadInfo.push_back(new GPThreadInfo(origin, secLen));

        origin += secLen;
    }

}

void GridProcessor::clearLoadInfo()
{
    for(GPThreadInfo* info : loadInfo)
        delete info;

    loadInfo.clear();
}

int GridProcessor::Width()  { return width; }
int GridProcessor::Height() { return  height; }

Grid* GridProcessor::GetRawGrid()
{
    return grid;
}

void GridProcessor::ResetGrid(Grid *grid)
{
    this->grid = grid;
    this->width = grid->Width();
    this->height = grid->Height();
    splitLoad();
}

int GridProcessor::ThreadCount() { return threadCount; }
void GridProcessor::SetThreadCount(int threadCount)
{
    this->threadCount = threadCount;
    splitLoad();
}