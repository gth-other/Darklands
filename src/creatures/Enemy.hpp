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


#include "Player.hpp"


#pragma once


class Enemy : public Creature {
public:
    Enemy();
    Enemy(sf::Vector2f position, Player *player);

    virtual void update(const Map *map);
    [[nodiscard]] virtual bool isBoss() const = 0;
protected:
    [[nodiscard]] Player *getPlayer() const;
private:
    Player *player;

    [[nodiscard]] bool isAI() const override;
};