#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
    simulationWindow = new SimulationWindow(640, 480);

    simWindowThread = new std::thread(&SimulationWindow::Start, simulationWindow);

    configuratorWindow = new ConfiguratorWindow();
    configuratorWindow->show();

    /*simulation flow*/
    connect(configuratorWindow, SIGNAL(simStart(Configuration*)), this, SLOT(simStart(Configuration*)));
    connect(configuratorWindow, SIGNAL(simPauseResume()), this, SLOT(simPauseResume()));
    connect(configuratorWindow, SIGNAL(simStop()), this, SLOT(simStop()));

    /*simulation config*/
    connect(configuratorWindow, SIGNAL(simSpeedChange(float)), this, SLOT(simSpeedChange(float)));

    /*window config*/
    connect(configuratorWindow, SIGNAL(zoomChanged(int)), this, SLOT(zoomChanged(int)));
    connect(configuratorWindow, SIGNAL(moveCam(int)), this, SLOT(moveCam(int)));

    connect(configuratorWindow, SIGNAL(closed()), this, SLOT(configWindowClosed()));
}

SimulationManager::~SimulationManager()
{
    shouldStop = true;
    simulationWindow->close();

    disconnect(configuratorWindow, SIGNAL(simStart(Configuration*)), this, SLOT(simStart(Configuration*)));
    disconnect(configuratorWindow, SIGNAL(simPauseResume()), this, SLOT(simPauseResume()));
    disconnect(configuratorWindow, SIGNAL(simStop(bool)), this, SLOT(simStop(bool)));

    disconnect(configuratorWindow, SIGNAL(simSpeedChange(float)), this, SLOT(simSpeedChange(float)));
    disconnect(configuratorWindow, SIGNAL(gridResize(int, int)), this, SLOT(gridResize(int,int)));
    disconnect(configuratorWindow, SIGNAL(threadCountChange(int)), this, SLOT(threadCountChange(int)));

    disconnect(configuratorWindow, SIGNAL(zoomChanged(int)), this, SLOT(zoomChanged(int)));
    disconnect(configuratorWindow, SIGNAL(moveCam(int)), this, SLOT(moveCam(int)));

    disconnect(configuratorWindow, SIGNAL(closed()), this, SLOT(configWindowClosed()));

    delete grid;
    delete gridProcessor;
    delete simulationThread;
}

void SimulationManager::simulationLoop()
{
    if(gridProcessor == nullptr || simulationWindow == nullptr)
        return;

    sf::Clock timer;
    float deltaTime = 0;

    while(!shouldStop)
    {
        if(!simPaused)
        {
            deltaTime += timer.restart().asSeconds();
            if(deltaTime >= simSpeed)
            {
                gridProcessor->Step();
                deltaTime = 0;
            }
        }

        simulationWindow->Update();
    }
}

//region Signals
void SimulationManager::simSpeedChange(float simSpeed)
{
    this->simSpeed = simSpeed;
}

void SimulationManager::simStart(Configuration* config)
{

    delete grid;

    grid = new Grid(config->gridWidth, config->gridHeight);
    simulationWindow->ReloadGrid(grid);

    simSpeed = config->simSpeed;

    if(gridProcessor == nullptr)
    {
        gridProcessor = new GridProcessor(grid, config->threadCount);
    }
    else
    {
        gridProcessor->ResetGrid(grid);
        gridProcessor->SetThreadCount(config->threadCount);
    }

    if(simulationThread == nullptr)
    {
        simulationThread = new std::thread(&SimulationManager::simulationLoop, this);
    }
    else if (shouldStop)
    {
        simulationThread->join();

        shouldStop = false;
        delete simulationThread;
        simulationThread = new std::thread(&SimulationManager::simulationLoop, this);
    }

    delete config;
}

void SimulationManager::simPauseResume()
{
    simPaused = !simPaused;
}

void SimulationManager::simStop()
{
    shouldStop = true;
}

void SimulationManager::configWindowClosed()
{
    simStop();
    if(simulationThread != nullptr)
        simulationThread->join();

    simulationWindow->ShouldClose();
    simWindowThread->join();

    disconnect(configuratorWindow, SIGNAL(simStart(Configuration*)), this, SLOT(simStart(Configuration*)));
    disconnect(configuratorWindow, SIGNAL(simPauseResume()), this, SLOT(simPauseResume()));
    disconnect(configuratorWindow, SIGNAL(simStop()), this, SLOT(simStop()));

    disconnect(configuratorWindow, SIGNAL(zoomChanged(int)), this, SLOT(zoomChanged(int)));
    disconnect(configuratorWindow, SIGNAL(moveCam(int)), this, SLOT(moveCam(int)));

    disconnect(configuratorWindow, SIGNAL(closed()), this, SLOT(configWindowClosed()));

    delete simWindowThread;
    delete simulationThread;

    delete simulationWindow;
    delete configuratorWindow;
    delete gridProcessor;
    delete grid;

    exit(0);
}

void SimulationManager::zoomChanged(int delta)
{
    simulationWindow->Zoom(delta);
}

void SimulationManager::moveCam(int direction)
{
    switch(direction)
    {
        case MOVE_UP:
            simulationWindow->MoveCamera(0, -camSpeed);
            break;

        case MOVE_DOWN:
            simulationWindow->MoveCamera(0, camSpeed);
            break;

        case MOVE_LEFT:
            simulationWindow->MoveCamera(-camSpeed, 0);
            break;

        case MOVE_RIGHT:
            simulationWindow->MoveCamera(camSpeed, 0);
            break;
    }
}

//endregion
