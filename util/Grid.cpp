#include <iostream>
#include "Grid.h"

Grid::Grid(int width, int height)
{
    this->width = width;
    this->height = height;

    srand(time(nullptr));

    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            cells.push_back(new ConwayCell(rollState(3), col, row));
        }
    }
}

Grid::~Grid()
{
    for(ConwayCell* cell : cells)
        delete cell;
}

bool Grid::rollState(int sides)
{    
    return (rand()%sides == 2);
}

ConwayCell* Grid::CellAt(int x, int y)
{
    int actualX, actualY;
    
    if(x == -1)
        actualX = width -1;
    else if(x == width)
        actualX = 0;
    else 
        actualX = x;
    
    if(y == -1)
        actualY = height -1;
    else if(y == height)
        actualY = 0;
    else 
        actualY = y;
    
    return cells[width*actualY + actualX];
}


std::vector<ConwayCell *> * Grid::Neighbours(int x, int y)
{   
    std::vector<ConwayCell*>* neighbours = new std::vector<ConwayCell*>();
    
    neighbours->push_back(CellAt(x, y+1));
    neighbours->push_back(CellAt(x+1, y+1));
    neighbours->push_back(CellAt(x+1, y));
    neighbours->push_back(CellAt(x+1, y-1));
    neighbours->push_back(CellAt(x, y-1));
    neighbours->push_back(CellAt(x-1, y-1));
    neighbours->push_back(CellAt(x-1, y));
    neighbours->push_back(CellAt(x-1, y+1));
    
    return neighbours;
}


void Grid::Update()
{
    for(ConwayCell* cell : cells)
    {
        cell->ApplyState();
    }
}

std::vector<ConwayCell*>* Grid::GetRows(int origin, int depth)
{
    std::vector<ConwayCell*>* range = new std::vector<ConwayCell*>();

    std::vector<ConwayCell*>::iterator start = cells.begin() + width*origin;
    std::vector<ConwayCell*>::iterator end   = start + width*depth;

    if(end > cells.end())
        end = cells.end();

    range->insert(range->begin(), start, end);

    return range;
}

int Grid::Width()  { return width; }
int Grid::Height() { return  height; }

std::vector<ConwayCell *> *Grid::GetRawCells()
{
    return &cells;
}

