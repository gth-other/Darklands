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


#include "Stationary.hpp"


Stationary::Stationary() = default;
Stationary::Stationary(int32_t cx, int32_t cy, Camera *camera, SoundQueue *soundQueue, Storage *storage) : GameObject(camera, soundQueue, storage) {
    this->cx = cx;
    this->cy = cy;

    this->hp = Stationary::MaxHP;
    this->camera = camera;
}
void Stationary::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!this->camera->contain(this->cx, this->cy)) return;

    sf::Sprite sprite;
    sprite.setTexture(this->getTexture());
    sprite.setTextureRect(this->getTextureRect());
    sprite.setPosition(64 * (float)this->cx - this->camera->getX(), 64 * (float)this->cy - this->camera->getY());

    StatusBar bar = {this->cx, this->cy, this->getHP(), this->getMaxHP(), this->camera, this->storage};

    target.draw(sprite, states);
    target.draw(bar, states);
}
bool Stationary::alive() const {
    return this->getHP() > 0;
}
int32_t Stationary::getCX() const {
    return this->cx;
}
int32_t Stationary::getCY() const {
    return this->cy;
}
float Stationary::getHP() const {
    if (this->hp == Stationary::MaxHP) return this->getMaxHP();
    return this->hp;
}
void Stationary::setCX(int32_t newCX) {
    this->cx = newCX;
}
void Stationary::setCY(int32_t newCY) {
    this->cy = newCY;
}
void Stationary::setHP(float newHP) {
    this->hp = newHP;
}