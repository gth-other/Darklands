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
#include "DefenseBuilding.hpp"


#pragma once


class Human : public Unit, public GameObject {
public:
    Human();
    Human(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setTarget(float newTargetX, float newTargetY);
    void setTarget(int32_t newTargetCX, int32_t newTargetCY);

    void kill();

    [[nodiscard]] bool targetReached() const;
    [[nodiscard]] bool alive() const override;
    [[nodiscard]] std::string calcMovementDirection() const;

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;

    void setX(float newX);
    void setY(float newY);
protected:
    sf::Clock animationClock;
    sf::Clock deathAnimationTimer;

    [[nodiscard]] virtual float getSpeed() const = 0;

    void updateMoving();
    void updateDefenseBuildings(std::vector<DefenseBuilding*> &defenseBuildings);
    [[nodiscard]] std::pair<float, float> calcSpeed() const;
private:
    float x, y;
    float targetX, targetY;
    bool _alive;

    sf::Clock movementTimer;
};