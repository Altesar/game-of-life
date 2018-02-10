#include <QApplication>

#include "SimulationManager.h"

int main(int argc, char **argv) 
{

    QApplication a(argc, argv);

    SimulationManager* manager = new SimulationManager();

    return a.exec();
}
