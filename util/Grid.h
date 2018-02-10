#ifndef GRID_H
#define GRID_H

#include <vector>
#include <random>
#include <ctime>

#include "ConwayCell.h"

class Grid
{
private:
    int width, height;
    std::vector<ConwayCell*> cells;

    bool rollState(int sides = 6);


public:
    Grid(int width, int height);
    ~Grid();
    
    ConwayCell* CellAt(int x, int y);
    std::vector<ConwayCell*>* Neighbours(int x, int y);

    std::vector<ConwayCell*>* GetRows(int origin, int depth);
    std::vector<ConwayCell*>* GetRawCells();
    
    void Update();

    int Width();
    int Height();
};

#endif //GRID_H
