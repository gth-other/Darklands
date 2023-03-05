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


#include "Wall.hpp"


Wall::Wall() = default;
Wall::Wall(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Building(cx, cy, player, camera, soundQueue, storage) {}
Resources Wall::getCost() const {
    return {0, 0, 50, 0, 0};
}
std::string Wall::getDescription() const {
    return "Стены защищают территорию от захватчиков.";
}
const sf::Texture &Wall::getTexture() const {
    return this->storage->getTexture("wall", this->player->getColor());
}
sf::IntRect Wall::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Wall::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("stone");
}
float Wall::getMaxHP() const {
    return 9000 * (1 + this->player->researched(Science::Keys::Walls));
}
float Wall::getRepairSpeed() const {
    return 50;
}