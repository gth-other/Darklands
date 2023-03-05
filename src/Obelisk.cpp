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


#include "Obelisk.hpp"


Obelisk::Obelisk() = default;
Obelisk::Obelisk(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : DefenseBuilding(cx, cy, player, camera, soundQueue, storage) {}
Resources Obelisk::getCost() const {
    return {0, 0, 200, 0, 0};
}
std::string Obelisk::getDescription() const {
    return "Обелиски защищают огромную территорию молниями от вражеских войск.";
}
const sf::Texture &Obelisk::getTexture() const {
    return this->storage->getTexture("obelisk", this->player->getColor());
}
sf::IntRect Obelisk::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Obelisk::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("thunder");
}
float Obelisk::getMaxHP() const {
    return 1000;
}
float Obelisk::getRepairSpeed() const {
    return 50;
}
float Obelisk::getRadius() const {
    return 6 * 64;
}
int32_t Obelisk::getBaseShootingDelay() const {
    return 4000;
}
const sf::SoundBuffer &Obelisk::getShootingSoundBuffer() const {
    return this->storage->getSoundBuffer("thunder");
}