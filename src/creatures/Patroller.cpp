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


#include "Patroller.hpp"


Patroller::Patroller() = default;
Patroller::Patroller(sf::Vector2f position, Player *player, Storage *storage, SoundQueue *soundQueue) : Enemy(position, player, storage, soundQueue) {}
void Patroller::update(const Map* map) {
    if (this->isRight()) {
        this->Creature::update(Creature::Flags::Right, map);
    }
    else {
        this->Creature::update(Creature::Flags::Left, map);
    }
    if (this->getV().x == 0) {
        this->invertDirection();
    }
    this->Enemy::update(map);
}