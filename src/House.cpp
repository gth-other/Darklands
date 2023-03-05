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


#include "House.hpp"


House::House() = default;
House::House(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Building(cx, cy, player, camera, soundQueue, storage) {}
Resources House::getCost() const {
    return {0, 150, 0, 0, 0};
}
std::string House::getDescription() const {
    return "В домах проживают Ваши войска.";
}
const sf::Texture &House::getTexture() const {
    return this->storage->getTexture("house", this->player->getColor());
}
sf::IntRect House::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &House::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("glasses");
}
float House::getMaxHP() const {
    return 1200 * (1 + this->player->researched(Science::Keys::Buildings));
}
float House::getRepairSpeed() const {
    return 25;
}