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


#include <random>
#include "Earner.hpp"
#include "House.hpp"
#include "Caravan.hpp"
#include "Academy.hpp"
#include "Wall.hpp"
#include "Tower.hpp"
#include "Obelisk.hpp"
#include "Fort.hpp"


#pragma once


class Warrior : public Earner {
public:
    Warrior();
    Warrior(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    void update(std::vector<DefenseBuilding*> &defenseBuildings, std::vector<ResourceBuilding*> &rbs, std::vector<ResourcePoint*> &rps, std::vector<Building*> &buildings, std::vector<Warrior*> &warriors);
    [[nodiscard]] std::string calcAttackDirection() const;
protected:
    [[nodiscard]] virtual float getDefense() const = 0;
    [[nodiscard]] virtual float getBuildingAttack() const = 0;
    [[nodiscard]] virtual float getWarriorAttack() const = 0;
    [[nodiscard]] virtual float getAttackRadius() const = 0;
    [[nodiscard]] virtual int32_t getAttackDelay() const = 0;
    [[nodiscard]] sf::IntRect getTextureRect() const override;

    [[nodiscard]] bool attackStarted() const;
private:
    float attackTargetX, attackTargetY;
    std::mt19937 mersenne;

    sf::Clock attackAnimationTimer;
    bool _attackStarted;

    void updateAttack(std::vector<Building*> &buildings, std::vector<Warrior*> &warriors);
    [[nodiscard]] Building* tryToFindBuildingInAttackRadius(std::vector<Building*> &buildings) const;
    [[nodiscard]] Warrior* tryToFindWarriorInAttackRadius(std::vector<Warrior*> &warriors) const;
};