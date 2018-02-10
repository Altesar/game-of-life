#ifndef CONWAY_CELL_H
#define CONWAY_CELL_H

#include <cstring>


class ConwayCell
{
private:
    bool pendingChange;
    
public:
    bool alive;
    int posX;
    int posY;

    ConwayCell(bool alive, int posX, int posY);
    
    void SetState(bool state);
    void ApplyState();
};


#endif //CONWAY_CELL_H
