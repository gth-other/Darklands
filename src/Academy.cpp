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


#include "Academy.hpp"


Academy::Academy() = default;
Academy::Academy(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Building(cx, cy, player, camera, soundQueue, storage) {}
Resources Academy::getCost() const {
    return {0, 0, 300, 0, 0};
}
std::string Academy::getDescription() const {
    return "Академии используются для развития науки.";
}
const sf::Texture &Academy::getTexture() const {
    return this->storage->getTexture("academy", this->player->getColor());
}
sf::IntRect Academy::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Academy::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("book");
}
float Academy::getMaxHP() const {
    return 2000;
}
float Academy::getRepairSpeed() const {
    return 25;
}