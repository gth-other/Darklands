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


#include "Caravan.hpp"


Caravan::Caravan() = default;
Caravan::Caravan(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Building(cx, cy, player, camera, soundQueue, storage) {}
Resources Caravan::getCost() const {
    return {0, 300, 0, 0, 0};
}
std::string Caravan::getDescription() const {
    return "Караваны используются для торговли.";
}
const sf::Texture &Caravan::getTexture() const {
    return this->storage->getTexture("caravan", this->player->getColor());
}
sf::IntRect Caravan::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Caravan::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("glasses");
}
float Caravan::getMaxHP() const {
    return 1500;
}
float Caravan::getRepairSpeed() const {
    return 25;
}