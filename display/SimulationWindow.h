#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <map>

#include <SFML/Graphics.hpp>

#include "../GridProcessor.h"

class SimulationWindow : public sf::RenderWindow
{
private:
    sf::View* camera;

    bool shouldClose = false;

    void eventLoop();
    float refreshRate;

    std::map<ConwayCell*, sf::RectangleShape*> sprites;
    int spriteSize;

    sf::Vector2f minSize;

    void buildSprites(Grid *grid);
    void clearSprites();

public:
    SimulationWindow(int width, int height, Grid *grid = nullptr, int spriteSize = 10);
    ~SimulationWindow();

    void Update();

    void Start();
    void ReloadGrid(Grid* grid);
    void ShouldClose();

    void Zoom(int percent);
    void MoveCamera(float deltaX, float deltaY);
};

#endif //MAIN_WINDOW_H
