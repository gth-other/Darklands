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


#include "Smelter.hpp"


Smelter::Smelter() = default;
Smelter::Smelter(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : ResourceBuilding(cx, cy, player, camera, soundQueue, storage) {}
Resources Smelter::getCost() const {
    return {0, 100, 0, 0, 0};
}
std::string Smelter::getDescription() const {
    return "Плавильни используются для добычи железа.";
}
const sf::Texture &Smelter::getTexture() const {
    return this->storage->getTexture("smelter", this->player->getColor());
}
sf::IntRect Smelter::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Smelter::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("steam");
}
float Smelter::getMaxHP() const {
    return 800;
}
float Smelter::getRepairSpeed() const {
    return 25;
}