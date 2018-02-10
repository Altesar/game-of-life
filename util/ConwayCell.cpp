#include "ConwayCell.h"

ConwayCell::ConwayCell(bool alive, int posX, int posY)
{
    this->alive = alive;
    this->posX = posX;
    this->posY = posY;
    this->pendingChange = false;
}

void ConwayCell::SetState(bool state)
{
    pendingChange = state;
}

void ConwayCell::ApplyState()
{
    alive = pendingChange;
}
