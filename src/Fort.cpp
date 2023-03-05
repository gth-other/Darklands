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


#include "Fort.hpp"


Fort::Fort() = default;
Fort::Fort(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : AreaController(cx, cy, player, camera, soundQueue, storage) {}
Resources Fort::getCost() const {
    return {0, 500, 500, 500, 0};
}
std::string Fort::getDescription() const {
    return "Крепости используются для расширения территории.";
}
const sf::Texture &Fort::getTexture() const {
    return this->storage->getTexture("fort", this->player->getColor());
}
sf::IntRect Fort::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Fort::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("stone");
}
float Fort::getMaxHP() const {
    return 3000;
}
float Fort::getRepairSpeed() const {
    return 50;
}
float Fort::getRadius() const {
    return 6 * 64;
}