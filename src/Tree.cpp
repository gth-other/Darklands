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


#include "Tree.hpp"


Tree::Tree() = default;
Tree::Tree(int32_t cx, int32_t cy, int32_t subspec, Camera *camera, SoundQueue *soundQueue, Storage *storage) : ResourcePoint(cx, cy, subspec, camera, soundQueue, storage) {}
const sf::Texture &Tree::getTexture() const {
    return this->storage->getTexture("tree" + std::to_string(this->getSubspec()));
}
sf::IntRect Tree::getTextureRect() const {
    return {0, 0, 64, 64};
}
const sf::SoundBuffer &Tree::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("leaves");
}
float Tree::getMaxHP() const {
    return 100;
}