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


#include "Plant.hpp"


Plant::Plant() = default;
Plant::Plant(int32_t cx, int32_t cy, int32_t subspec, Camera *camera, SoundQueue *soundQueue, Storage *storage) : ResourcePoint(cx, cy, subspec, camera, soundQueue, storage) {}
const sf::Texture &Plant::getTexture() const {
    return this->storage->getTexture("plant" + std::to_string(this->getSubspec()));
}
sf::IntRect Plant::getTextureRect() const {
    int32_t animations = (int32_t)this->getTexture().getSize().x / 64;
    int32_t ms = 1000 / animations;

    return {this->animationClock.getElapsedTime().asMilliseconds() / ms % animations * 64, 0, 64, 64};
}
const sf::SoundBuffer &Plant::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("leaves");
}
float Plant::getMaxHP() const {
    return 100;
}