cmake_minimum_required(VERSION 3.0)
project(Darklands)
set(CMAKE_CXX_STANDARD 20)
add_executable(Darklands src/main.cpp src/PathManager.hpp src/PathManager.cpp src/Storage.hpp src/Storage.cpp src/Screen.hpp src/Screen.cpp src/LoadingScreen.hpp src/LoadingScreen.cpp src/WaitingScreen.hpp src/WaitingScreen.cpp src/Cursor.hpp src/Cursor.cpp src/Menu.hpp src/Menu.cpp src/FPSCounter.hpp src/FPSCounter.cpp src/Camera.hpp src/Camera.cpp src/StatusBar.hpp src/StatusBar.cpp src/Stationary.hpp src/Stationary.cpp src/ResourcePoint.hpp src/ResourcePoint.cpp src/RedMountain.hpp src/RedMountain.cpp src/Plant.hpp src/Plant.cpp src/Game.hpp src/Game.cpp src/Resources.hpp src/Resources.cpp src/Player.hpp src/Player.cpp src/Building.hpp src/Building.cpp src/Fort.hpp src/Fort.cpp src/AreaController.hpp src/AreaController.cpp src/Warrior.hpp src/Warrior.cpp src/Infantryman.hpp src/Infantryman.cpp src/ResourceBuilding.hpp src/ResourceBuilding.cpp src/Windmill.hpp src/Windmill.cpp src/Smelter.hpp src/Smelter.cpp src/ShoppingList.hpp src/ShoppingList.cpp src/LandscapeGenerator.hpp src/LandscapeGenerator.cpp src/LandscapeConf.hpp src/Banner.hpp src/Banner.cpp src/Wall.hpp src/Wall.cpp src/GameObject.hpp src/GameObject.cpp src/Unit.hpp src/Unit.cpp src/SoundQueue.hpp src/SoundQueue.cpp src/Archer.hpp src/Archer.cpp src/House.hpp src/House.cpp src/Tree.hpp src/Tree.cpp src/Sawmill.hpp src/Sawmill.cpp src/Mountain.hpp src/Mountain.cpp src/Quarry.hpp src/Quarry.cpp src/Tower.hpp src/Tower.cpp src/DefenseBuilding.hpp src/DefenseBuilding.cpp src/Obelisk.hpp src/Obelisk.cpp src/Caravan.hpp src/Caravan.cpp src/Academy.hpp src/Academy.cpp src/Science.hpp src/Science.cpp)
include(FindPkgConfig)
add_definitions(-Werror)
add_definitions(-O3)
add_definitions(-flto)


target_link_libraries(Darklands sfml-system sfml-window sfml-graphics sfml-audio)