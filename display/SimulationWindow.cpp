#include "SimulationWindow.h"

SimulationWindow::SimulationWindow(int width, int height, Grid *grid, int spriteSize) :
        sf::RenderWindow(sf::VideoMode(width, height), "Game of Life", sf::Style::Titlebar)
{
    this->refreshRate = refreshRate;
    this->spriteSize = spriteSize;

    if(grid != nullptr)
        buildSprites(grid);

    minSize = sf::Vector2f(width, height);
    camera = new sf::View(sf::Vector2f(width/2, height/2), minSize);
}

SimulationWindow::~SimulationWindow()
{
    delete camera;

    clearSprites();
}

void SimulationWindow::eventLoop()
{
    sf::Event evt;
    while(this->isOpen() && !shouldClose)
    {
        this->pollEvent(evt);
    }

    this->close();
}

void SimulationWindow::Start()
{
    eventLoop();
}

void SimulationWindow::ShouldClose()
{
    shouldClose = true;
}

void SimulationWindow::buildSprites(Grid *grid)
{
    sf::RectangleShape* temp;

    std::vector<ConwayCell*>* cells = grid->GetRawCells();

    for(ConwayCell* cell : *cells)
    {
        temp = new sf::RectangleShape( sf::Vector2f(spriteSize, spriteSize) );
        temp->setPosition(cell->posX * spriteSize, cell->posY*spriteSize);
        sprites[cell] = temp;
    }
}

void SimulationWindow::clearSprites()
{
    for(std::pair<ConwayCell*, sf::RectangleShape*> pair : sprites)
    {
        delete pair.second;
    }

    sprites.clear();
}

void SimulationWindow::Update()
{
    this->clear();

    this->setView(*camera);

    for(std::pair<ConwayCell*, sf::RectangleShape*> pair : sprites)
    {
        if(pair.first->alive)
            pair.second->setFillColor(sf::Color::White);
        else
            pair.second->setFillColor(sf::Color::Black);

        this->draw(*pair.second);
    }

    this->display();
}

void SimulationWindow::ReloadGrid(Grid* grid)
{
    clearSprites();
    buildSprites(grid);
}

void SimulationWindow::Zoom(int percent)
{
    if(percent == 100)
    {
        camera->setSize(minSize);
        return;
    }

    float factor = 100 - percent;

    sf::Vector2f size = minSize + sf::Vector2f(minSize.x * factor / 10.0f, minSize.y * factor / 10.0f);
    camera->setSize(size);
}

void SimulationWindow::MoveCamera(float deltaX, float deltaY)
{
    camera->move(deltaX, deltaY);
}










