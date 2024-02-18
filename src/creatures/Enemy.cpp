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


#include "Enemy.hpp"


Enemy::Enemy() = default;
Enemy::Enemy(sf::Vector2f position) : Creature(position) {}
void Enemy::update(const Map *map, Player *player) {
    if (player->isAlive() and this->getRect().intersects(player->getCompressedRect())) {
        if (player->isAbandonedLives() or player->getV().y > 0) {
            this->kill(player->getMurderSoundName());
        }
        else {
            player->kill(this->getMurderSoundName());
        }
    }
}
bool Enemy::isAI() const {
    return true;
}