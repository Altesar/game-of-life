#ifndef GAME_OF_LIFE_SIMULATIONMANAGER_H
#define GAME_OF_LIFE_SIMULATIONMANAGER_H

#include <cstdlib>

#include <SFML/System.hpp>

#include <QtCore/QObject>

#include "GridProcessor.h"
#include "display/SimulationWindow.h"
#include "qt_ui/ConfiguratorWindow.h"
#include "util/Configuration.h"

class SimulationManager : public QObject
{
    Q_OBJECT
private:

    bool simStarted = false;
    bool simPaused = false;
    bool shouldStop = false;

    float simSpeed;

    SimulationWindow* simulationWindow;
    std::thread* simWindowThread = nullptr;

    ConfiguratorWindow* configuratorWindow;

    Grid* grid = nullptr;
    GridProcessor* gridProcessor = nullptr;

    std::thread* simulationThread = nullptr;
    void simulationLoop();

    int camSpeed = 100;

public:
    SimulationManager();
    ~SimulationManager();

public slots:
    void simStart(Configuration* config);
    void simStop();
    void simPauseResume();

    void simSpeedChange(float simSpeed);

    void configWindowClosed();

    void moveCam(int);
    void zoomChanged(int);
};


#endif //GAME_OF_LIFE_SIMULATIONMANAGER_H
