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


#include <cmath>
#include <vector>
#include "Plant.hpp"
#include "Tree.hpp"
#include "Mountain.hpp"
#include "RedMountain.hpp"
#include "Windmill.hpp"
#include "Sawmill.hpp"
#include "Quarry.hpp"
#include "Smelter.hpp"
#include "House.hpp"
#include "Caravan.hpp"
#include "Academy.hpp"
#include "Wall.hpp"
#include "Tower.hpp"
#include "Obelisk.hpp"
#include "Fort.hpp"


#pragma once


class Warrior : public Unit, public GameObject {
public:
    Warrior();
    Warrior(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(std::vector<DefenseBuilding*> &defenseBuildings, std::vector<ResourceBuilding*> &rbs, std::vector<ResourcePoint*> &rps);

    void setTarget(float newTargetX, float newTargetY);
    void setTarget(int32_t newTargetCX, int32_t newTargetCY);

    void startFoodCollection(int32_t cx, int32_t cy);
    void startWoodCollection(int32_t cx, int32_t cy);
    void startStoneCollection(int32_t cx, int32_t cy);
    void startIronCollection(int32_t cx, int32_t cy);
    void stopCollection();

    void kill();

    [[nodiscard]] bool targetReached() const;
    [[nodiscard]] bool alive() const override;
    [[nodiscard]] std::string calcDirection() const;

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;

    void setX(float newX);
    void setY(float newY);
protected:
    [[nodiscard]] virtual float getDefense() const = 0;
    [[nodiscard]] virtual float getBuildingAttack() const = 0;
    [[nodiscard]] virtual float getWarriorAttack() const = 0;
    [[nodiscard]] virtual float getAttackRadius() const = 0;
    [[nodiscard]] virtual int32_t getAttackDelay() const = 0;
    [[nodiscard]] virtual float getSpeed() const = 0;
    [[nodiscard]] float getCapacity() const;
    [[nodiscard]] virtual float getBaseCapacity() const = 0;
    [[nodiscard]] sf::IntRect getTextureRect() const override;
private:
    float x, y;
    float targetX, targetY;
    bool _alive;
    bool foodCollectionInProgress;
    bool woodCollectionInProgress;
    bool stoneCollectionInProgress;
    bool ironCollectionInProgress;
    float bag;

    sf::Clock movementTimer;
    sf::Clock animationClock;
    sf::Clock deathAnimationClock;

    [[nodiscard]] std::pair<float, float> calcSpeed() const;
    [[nodiscard]] std::pair<int32_t, int32_t> tryToFindBestResourceBuilding(std::vector<ResourceBuilding*> &rbs) const;
    [[nodiscard]] std::pair<int32_t, int32_t> tryToFindBestResourcePoint(std::vector<ResourcePoint*> &rps) const;
    [[nodiscard]] bool correctResourceBuilding(ResourceBuilding *rb) const;
    [[nodiscard]] bool correctResourcePoint(ResourcePoint *rp) const;

    void updateMoving();
    void updateDefenseBuildings(std::vector<DefenseBuilding*> &defenseBuildings);
    void updateCollection(std::vector<ResourceBuilding*> &rbs, std::vector<ResourcePoint*> &rps);
};