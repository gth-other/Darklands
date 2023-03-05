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


#include "Banner.hpp"


Banner::Banner() = default;
Banner::Banner(Storage *storage, SoundQueue *soundQueue, Camera *camera) {
    this->storage = storage;
    this->soundQueue = soundQueue;
    this->camera = camera;

    this->setPosition(-100, -100);
}
void Banner::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sprite.setPosition(this->x - this->camera->getX(), this->y - this->camera->getY());
    sprite.setTexture(this->storage->getTexture("banner"));

    target.draw(sprite, states);
}
void Banner::setPosition(float newX, float newY, bool playSound) {
    this->x = newX;
    this->y = newY;

    if (playSound) this->soundQueue->push(this->storage->getSoundBuffer("click"));
}