#ifndef GAME_OF_LIFE_CONFIGURATORWINDOW_H
#define GAME_OF_LIFE_CONFIGURATORWINDOW_H

#include <thread>

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include "../GridProcessor.h"
#include "../display/SimulationWindow.h"
#include "../util/Configuration.h"

#define GRID_WIDTH 64
#define GRID_HEIGHT 48

#define SIM_SPD_SLIDER 5
#define MIN_SIM_SPD_SLIDER 1
#define MAX_SIM_SPD_SLIDER 10
#define THREAD_COUNT 2

#define MOVE_UP    0
#define MOVE_DOWN  1
#define MOVE_LEFT  2
#define MOVE_RIGHT 3

class ConfiguratorWindow : public QWidget
{
    Q_OBJECT
private:

    //region Simulation controls

    /*Simulation flow*/
    QPushButton* startStopBtn;
    QPushButton* pauseBtn;

    QLabel* simSpeedLabel;
    QSlider* simSpeedSlider;

    QHBoxLayout* flowControlButtons;
    QVBoxLayout* flowControls;

    /*Env settings*/
    QSpinBox* gridWidth;
    QSpinBox* gridHeight;
    QLabel* gridSizeLabel;

    QLabel* threadCountLabel;
    QSpinBox* threadCount;

    QVBoxLayout* gridSettings;
    QHBoxLayout* threadSettings;
    QVBoxLayout* envSettings;


    QVBoxLayout* simulationControls;

    //endregion

    //region Simulation window controls

    /*Display settings*/
    QVBoxLayout* zoomControls;
    QLabel* zoomLabel;
    QSlider* zoomSlider;

    QLabel* camControlsLabel;
    QPushButton* moveCamUpBtn;
    QPushButton* moveCamDownBtn;
    QPushButton* moveCamLeftBtn;
    QPushButton* moveCamRightBtn;

    QGridLayout* camMoveButtons;

    QVBoxLayout* camControls;

    QVBoxLayout* windowControls;

    //endregion

    //region Author info

    QLabel* madeByLabel;
    QLabel* authorName;
    QLabel* authorMail;
    QVBoxLayout* madeByContainer;

    QPushButton* infoBtn;

    //endregion

    QHBoxLayout* mainContainer;

    bool started = false;
    bool paused = false;

    void buildSimControls();
    void buildWindowControls();
    void buildAuthorInfo();
    void toggleCamControls(bool state);

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    ConfiguratorWindow();
    ~ConfiguratorWindow();

public slots:
    /*Button handlers*/
    void startStopBtn_click();
    void pauseBtn_click();

    void moveCamUpBtn_click();
    void moveCamDownBtn_click();
    void moveCamLeftBtn_click();
    void moveCamRightBtn_click();

    /*Slider handlers*/
    void simSpeedSlider_valueChanged(int val);
    void zoomSlider_valueChanged(int val);

signals:
    void simSpeedChange(float simSpeed);

    void simStart(Configuration* config);
    void simPauseResume();
    void simStop();

    void closed();

    void zoomChanged(int);
    void moveCam(int direction);
};


#endif //GAME_OF_LIFE_CONFIGURATORWINDOW_H
