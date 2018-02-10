cmake_minimum_required(VERSION 2.6)
project(game_of_life)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

set(UTIL_SRC
        util/ConwayCell.h
        util/ConwayCell.cpp

        util/Grid.h
        util/Grid.cpp

        util/Configuration.h
)

set(DISPLAY_SRC
        display/SimulationWindow.h
        display/SimulationWindow.cpp
)

set(QT_UI_SRC
        qt_ui/ConfiguratorWindow.h
        qt_ui/ConfiguratorWindow.cpp
)

add_executable(gol main.cpp

               GridProcessor.h
               GridProcessor.cpp

               SimulationManager.h
               SimulationManager.cpp
               
               ${UTIL_SRC}
               ${DISPLAY_SRC}
               ${QT_UI_SRC}
)

set(SFML_LIB -lsfml-window -lsfml-system -lsfml-graphics)

target_link_libraries(gol Qt5::Widgets -lpthread ${SFML_LIB})