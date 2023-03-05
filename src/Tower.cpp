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


#include "Tower.hpp"


Tower::Tower() = default;
Tower::Tower(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : DefenseBuilding(cx, cy, player, camera, soundQueue, storage) {}
Resources Tower::getCost() const {
    return {0, 100, 100, 0, 0};
}
std::string Tower::getDescription() const {
    return "Башни обстреливают вражеские войска.";
}
const sf::Texture &Tower::getTexture() const {
    return this->storage->getTexture("tower", this->player->getColor());
}
sf::IntRect Tower::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Tower::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("archery");
}
float Tower::getMaxHP() const {
    return 1000 * (1 + this->player->researched(Science::Keys::Buildings));
}
float Tower::getRepairSpeed() const {
    return 50;
}
float Tower::getRadius() const {
    return 3 * 64;
}
int32_t Tower::getShootingDelay() const {
    return 1000 / (1 + this->player->researched(Science::Keys::DefenseBuildings));
}
const sf::SoundBuffer &Tower::getShootingSoundBuffer() const {
    return this->storage->getSoundBuffer("archery");
}