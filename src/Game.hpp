/*
 *  Darklands
 *  Copyright (C) 2023 gth-other
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


#include <fstream>
#include <filesystem>
#include "weapons/Cannon.hpp"
#include "weapons/Mortar.hpp"
#include "creatures/Vampire.hpp"
#include "creatures/Spider.hpp"
#include "creatures/Soul.hpp"
#include "creatures/OldVampire.hpp"
#include "creatures/Lord.hpp"
#include "Playlist.hpp"


#pragma once


class Game {
public:
    Game();
    void start();
private:
    sf::RenderWindow window;
    sf::View playerView;
    sf::Event event{};
    Map map;
    Player player;
    sf::Sprite sun;
    sf::Sprite observingSpheres;
    sf::Sprite abandonedLives;
    sf::RectangleShape defeatRect;
    sf::Text defeatMessage;
    sf::RectangleShape finishRect;
    sf::Text finishMessageDefault;
    sf::Text finishMessageLast;
    sf::Text license;
    std::list<std::unique_ptr<Weapon>> weapons;
    std::list<Bullet> bullets;
    std::list<std::unique_ptr<Enemy>> enemies;
    float finishX;

    enum Flag {NEXT, EXIT};
    static constexpr int32_t LEVELS_NUMBER = 4;

    void initWindow();
    void initPlayerView();
    void loadData();
    void createSun();
    void createBlackBooks();
    void createEndingMsgs();
    void createLicenseTitle();

    void updatePhysics(bool lastLevel);
    void displayEverything(bool lastLevel);

    static int32_t getCurrentLevel();
    static void setCurrentLevel(int32_t level);
    [[nodiscard]] bool finish(bool lastLevel) const;

    uint8_t startLevel(const std::string &path, bool lastLevel);
};