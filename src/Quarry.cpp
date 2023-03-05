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


#include "Quarry.hpp"


Quarry::Quarry() = default;
Quarry::Quarry(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : ResourceBuilding(cx, cy, player, camera, soundQueue, storage) {}
Resources Quarry::getCost() const {
    return {0, 100, 0, 0, 0};
}
std::string Quarry::getDescription() const {
    return "Каменоломни используются для добычи камня.";
}
const sf::Texture &Quarry::getTexture() const {
    return this->storage->getTexture("quarry", this->player->getColor());
}
sf::IntRect Quarry::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Quarry::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("stone");
}
float Quarry::getMaxHP() const {
    return 800 * (1 + this->player->researched(Science::Keys::Buildings));
}
float Quarry::getRepairSpeed() const {
    return 25;
}