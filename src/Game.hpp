/*
 *  Darklands
 *  Copyright (C) 2022 gth-other
 *
 *  Darklands is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Darklands is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Darklands.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <array>
#include "Screen.hpp"
#include "ShoppingList.hpp"
#include "Cursor.hpp"
#include "FPSCounter.hpp"
#include "Infantryman.hpp"
#include "Archer.hpp"
#include "LandscapeGenerator.hpp"
#include "Banner.hpp"


#pragma once


class Game : public Screen {
public:
    Game();
    Game(Storage *storage, SoundQueue *soundQueue, sf::RenderWindow *window);

    int32_t open() override;
private:
    LandscapeConf conf;
    Camera *camera;
    FPSCounter fps;
    Cursor cursor;
    Player *human;
    Player *computer;
    sf::RectangleShape selectionWindow;
    int32_t soundtrackNumber;
    Banner banner;

    sf::Sprite buildingListButton;
    bool showBuildingList;
    ShoppingList buildingList;
    Building* buildingLayout;

    sf::Sprite warriorsListButton;
    bool showWarriorsList;
    ShoppingList warriorsList;
    std::array<Warrior*, 25> warriorsLayout;

    ShoppingList tradingList;
    ShoppingList scienceList;

    std::vector<Academy*> academies;
    std::vector<Archer*> archers;
    std::vector<AreaController*> areaControllers;
    std::vector<Building*> buildings;
    std::vector<Caravan*> caravans;
    std::vector<DefenseBuilding*> defenseBuildings;
    std::vector<Fort*> forts;
    std::vector<GameObject*> gameObjects;
    std::vector<House*> houses;
    std::vector<Infantryman*> infantrymen;
    std::vector<Mountain*> mountains;
    std::vector<Obelisk*> obelisks;
    std::vector<Plant*> plants;
    std::vector<Quarry*> quarries;
    std::vector<RedMountain*> redMountains;
    std::vector<ResourceBuilding*> resourceBuildings;
    std::vector<ResourcePoint*> resourcePoints;
    std::vector<Sawmill*> sawmills;
    std::vector<Smelter*> smelters;
    std::vector<Stationary*> stationary;
    std::vector<Tower*> towers;
    std::vector<Tree*> trees;
    std::vector<Unit*> units;
    std::vector<Wall*> walls;
    std::vector<Warrior*> warriors;
    std::vector<Windmill*> windmills;

    void initUI();
    void initPlayersUnits();

    template<class Type> void push(Type *a);

    void drawEverything();
    void updateBuildings();
    void updateWarriors();
    void updatePlayers();
    void updateBuildingLayout();
    void updateWarriorsLayout();
    void updateSelectionWindow();
    void updateCamera();
    void updateSoundtrack();

    [[nodiscard]] bool tradingListVisible() const;
    void unselectCaravans();
    [[nodiscard]] bool scienceListVisible() const;
    void unselectAcademies();
    template<class Type> void buyBuildingButtonClick();
    template<class Type> void buyWarriorsButtonClick();
    void buildingListButtonClick();
    void warriorsListButtonClick();
    [[nodiscard]] bool possibleToPutBuilding() const;
    [[nodiscard]] bool possibleToPutWarriors() const;
    void addBuildingFromLayout();
    void addWarriorsFromLayout();
    void makeTrade(Resources cost);
    void updateStationarySelection();
    void unselectWarriors();
    void sendSelectedWarriors();
    void unselectEverything();
    void selectForts();
};