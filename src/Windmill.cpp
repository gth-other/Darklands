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


#include "Windmill.hpp"


Windmill::Windmill() = default;
Windmill::Windmill(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : ResourceBuilding(cx, cy, player, camera, soundQueue, storage) {}
Resources Windmill::getCost() const {
    return {0, 100, 0, 0, 0};
}
std::string Windmill::getDescription() const {
    return "Ветряные мельницы используются для добычи еды.";
}
const sf::Texture &Windmill::getTexture() const {
    return this->storage->getTexture("windmill", this->player->getColor());
}
sf::IntRect Windmill::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Windmill::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("wind");
}
float Windmill::getMaxHP() const {
    return 800;
}
float Windmill::getRepairSpeed() const {
    return 25;
}