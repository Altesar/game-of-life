#include "ConfiguratorWindow.h"


ConfiguratorWindow::ConfiguratorWindow() : QWidget()
{
    mainContainer = new QHBoxLayout();
    simulationControls = new QVBoxLayout();
    windowControls = new QVBoxLayout();

    buildSimControls();
    buildAuthorInfo();
    buildWindowControls();

    this->setLayout(mainContainer);
    this->setFixedSize(this->minimumSize());
    this->setWindowTitle("Configurator");
    this->show();
}

ConfiguratorWindow::~ConfiguratorWindow()
{
    disconnect(startStopBtn, SIGNAL(clicked()), this, SLOT(startStopBtn_click()));
    disconnect(pauseBtn, SIGNAL(clicked()), this, SLOT(pauseBtn_click()));
    disconnect(simSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(simSpeedSlider_valueChanged(int)));

    disconnect(moveCamUpBtn, SIGNAL(clicked()), this, SLOT(moveCamUpBtn_click()));
    disconnect(moveCamDownBtn, SIGNAL(clicked()), this, SLOT(moveCamDownBtn_click()));
    disconnect(moveCamLeftBtn, SIGNAL(clicked()), this, SLOT(moveCamLeftBtn_click()));
    disconnect(moveCamRightBtn, SIGNAL(clicked()), this, SLOT(moveCamRightBtn_click()));

    disconnect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomSlider_valueChanged(int)));

    delete startStopBtn;
    delete pauseBtn;
    delete simSpeedLabel;
    delete simSpeedSlider;
    delete flowControlButtons;
    delete flowControls;
    delete gridWidth;
    delete gridHeight;
    delete gridSizeLabel;
    delete threadCountLabel;
    delete threadCount;
    delete gridSettings;
    delete threadSettings;
    delete envSettings;
    delete simulationControls;
    delete zoomSlider;
    delete camControlsLabel;
    delete moveCamUpBtn;
    delete moveCamDownBtn;
    delete moveCamLeftBtn;
    delete moveCamRightBtn;
    delete camMoveButtons;
    delete camControls;
    delete windowControls;
    delete mainContainer;
}

void ConfiguratorWindow::buildSimControls()
{
    /*FLow controls*/
    startStopBtn = new QPushButton("start");
    startStopBtn->setMinimumWidth(150);
    connect(startStopBtn, SIGNAL(clicked()), this, SLOT(startStopBtn_click()));

    pauseBtn = new QPushButton("pause");
    pauseBtn->setMinimumWidth(150);
    pauseBtn->setEnabled(false);
    connect(pauseBtn, SIGNAL(clicked()), this, SLOT(pauseBtn_click()));

    simSpeedLabel = new QLabel("Simulation Speed", this);
    simSpeedLabel->setAlignment(Qt::AlignCenter);

    simSpeedSlider = new QSlider(Qt::Horizontal);
    simSpeedSlider->setMinimum(MIN_SIM_SPD_SLIDER);
    simSpeedSlider->setMaximum(MAX_SIM_SPD_SLIDER);
    simSpeedSlider->setValue(SIM_SPD_SLIDER);
    connect(simSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(simSpeedSlider_valueChanged(int)));

    flowControlButtons = new QHBoxLayout();
    flowControlButtons->addWidget(startStopBtn);
    flowControlButtons->addWidget(pauseBtn);

    flowControls = new QVBoxLayout();
    flowControls->addLayout(flowControlButtons);
    flowControls->addWidget(simSpeedLabel);
    flowControls->addWidget(simSpeedSlider);


/*Env settings*/
    gridSizeLabel = new QLabel("Grid Size");
    gridSizeLabel->setAlignment(Qt::AlignCenter);

    gridWidth = new QSpinBox();
    gridWidth->setValue(GRID_WIDTH);
    gridWidth->setMaximum(10000);

    gridHeight = new QSpinBox();
    gridHeight->setValue(GRID_HEIGHT);
    gridHeight->setMaximum(10000);

    gridSettings = new QVBoxLayout();
    gridSettings->addWidget(gridSizeLabel);
    gridSettings->addWidget(gridWidth);
    gridSettings->addWidget(gridHeight);

    envSettings = new QVBoxLayout();
    envSettings->addLayout(gridSettings);

    threadCountLabel = new QLabel("Thread count");
    threadCountLabel->setAlignment(Qt::AlignCenter);
    threadCount = new QSpinBox();
    threadCount->setValue(THREAD_COUNT);
    threadCount->setMinimum(1);
    threadCount->setBaseSize(50, threadCount->height());

    threadSettings = new QHBoxLayout();
    threadSettings->addWidget(threadCount);

    envSettings->addWidget(threadCountLabel);
    envSettings->addLayout(threadSettings);

    simulationControls->addLayout(flowControls);
    simulationControls->addLayout(envSettings);

    mainContainer->addLayout(simulationControls);
}

void ConfiguratorWindow::buildAuthorInfo()
{
    QFont font("Default", 8, QFont::Bold);

    madeByLabel = new QLabel("Made by:\nDmitriy Gorval\ndmitriygorval@gmail.com");
    madeByLabel->setAlignment(Qt::AlignRight);
    madeByLabel->setFont(font);

    madeByContainer = new QVBoxLayout();
    madeByContainer->addWidget(madeByLabel);

    windowControls->addLayout(madeByContainer);
}

void ConfiguratorWindow::buildWindowControls()
{


    /*Camera controls*/
    camControlsLabel = new QLabel("Camera controls");
    camControlsLabel->setAlignment(Qt::AlignCenter);

    moveCamUpBtn = new QPushButton("up");
    //moveCamUpBtn->setMinimumWidth(100);
    //moveCamUpBtn->setMaximumWidth(100);

    moveCamDownBtn = new QPushButton("down");
    //moveCamDownBtn->setMinimumWidth(100);
    //moveCamDownBtn->setMaximumWidth(100);

    moveCamLeftBtn = new QPushButton("left");
    //moveCamLeftBtn->setMinimumWidth(100);
    //moveCamLeftBtn->setMaximumWidth(100);

    moveCamRightBtn = new QPushButton("right");
    //moveCamRightBtn->setMinimumWidth(100);
    //moveCamRightBtn->setMaximumWidth(100);

    connect(moveCamUpBtn, SIGNAL(clicked()), this, SLOT(moveCamUpBtn_click()));
    connect(moveCamDownBtn, SIGNAL(clicked()), this, SLOT(moveCamDownBtn_click()));
    connect(moveCamLeftBtn, SIGNAL(clicked()), this, SLOT(moveCamLeftBtn_click()));
    connect(moveCamRightBtn, SIGNAL(clicked()), this, SLOT(moveCamRightBtn_click()));

    camMoveButtons = new QGridLayout();
    camMoveButtons->addWidget(moveCamUpBtn, 0, 1);
    camMoveButtons->addWidget(moveCamRightBtn, 1, 2);
    camMoveButtons->addWidget(moveCamDownBtn, 2, 1);
    camMoveButtons->addWidget(moveCamLeftBtn, 1, 0);

    camMoveButtons->addWidget(moveCamUpBtn);

    camMoveButtons->addWidget(moveCamDownBtn);

    camMoveButtons->setAlignment(moveCamUpBtn, Qt::AlignCenter);
    camMoveButtons->setAlignment(moveCamDownBtn, Qt::AlignCenter);

    zoomControls = new QVBoxLayout();
    zoomLabel = new QLabel("Zoom");
    zoomLabel->setAlignment(Qt::AlignCenter);
    zoomSlider = new QSlider(Qt::Horizontal);
    zoomSlider->setMaximum(100);
    zoomSlider->setValue(100);
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomSlider_valueChanged(int)));

    zoomControls->addWidget(zoomLabel);
    zoomControls->addWidget(zoomSlider);

    camControls = new QVBoxLayout();
    camControls->addWidget(camControlsLabel);
    camControls->addLayout(camMoveButtons);
    camControls->addLayout(zoomControls);
    toggleCamControls(false);

    windowControls->addLayout(camControls);

    mainContainer->addLayout(windowControls);
}

void ConfiguratorWindow::toggleCamControls(bool state)
{
    moveCamUpBtn->setEnabled(state);
    moveCamDownBtn->setEnabled(state);
    moveCamLeftBtn->setEnabled(state);
    moveCamRightBtn->setEnabled(state);
    zoomSlider->setEnabled(state);
}

//region Event handlers

void ConfiguratorWindow::startStopBtn_click()
{
    if(!started)
    {
        startStopBtn->setText("stop");

        Configuration* config = new Configuration;

        config->threadCount = threadCount->value();
        config->simSpeed = 1.1 - ((float)simSpeedSlider->value() / 10.0f);

        config->gridWidth = gridWidth->value();
        config->gridHeight = gridHeight->value();

        emit simStart(config);

        started = true;


        gridHeight->setEnabled(false);
        gridWidth->setEnabled(false);
        threadCount->setEnabled(false);
        toggleCamControls(true);

        pauseBtn->setEnabled(true);
    }
    else
    {
        startStopBtn->setText("start");
        emit simStop();
        started = false;

        gridHeight->setEnabled(true);
        gridWidth->setEnabled(true);
        threadCount->setEnabled(true);
        toggleCamControls(false);

        pauseBtn->setEnabled(false);

        if(paused)
        {
            pauseBtn->setText("pause");
            paused = false;
            emit simPauseResume();
        }
    }
}

void ConfiguratorWindow::pauseBtn_click()
{
    emit simPauseResume();

    if(paused)
    {
        pauseBtn->setText("pause");
        paused = false;
    }
    else
    {
        pauseBtn->setText("resume");
        paused = true;
    }
}

void ConfiguratorWindow::moveCamUpBtn_click()
{
    emit moveCam(MOVE_UP);
}

void ConfiguratorWindow::moveCamDownBtn_click()
{
    emit moveCam(MOVE_DOWN);
}

void ConfiguratorWindow::moveCamLeftBtn_click()
{
    emit moveCam(MOVE_LEFT);
}

void ConfiguratorWindow::moveCamRightBtn_click()
{
    emit moveCam(MOVE_RIGHT);
}

void ConfiguratorWindow::simSpeedSlider_valueChanged(int val)
{
    emit simSpeedChange(1.1 - (val / 10.0f));
}

void ConfiguratorWindow::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

void ConfiguratorWindow::zoomSlider_valueChanged(int val)
{
    emit zoomChanged( val );
}


//endregion