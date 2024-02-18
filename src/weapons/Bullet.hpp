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


#include <cmath>
#include "../creatures/Player.hpp"
#include "../SoundQueue.hpp"
#include "../Map.hpp"


#pragma once


class Bullet : public sf::Drawable {
public:
    Bullet();
    Bullet(sf::FloatRect rect, float v, float alpha, float g);

    void update(const Map *map, const Player *player, float extraTime = 0);
    [[nodiscard]] bool isExist() const;
    [[nodiscard]] sf::FloatRect getRect() const;
    void remove(const Player *player);
    [[nodiscard]] sf::Vector2f getFinalCenterPosition(const Map *map, const Player *player) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::FloatRect rect;
    sf::Vector2f v;
    float g;
    bool exist;
    bool noSound;
    sf::Clock timer;
    sf::Clock animationClock;

    void collisionX(const Map *map, const Player *player);
    void collisionY(const Map *map, const Player *player);
};