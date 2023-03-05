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


#include "Camera.hpp"


Camera::Camera() = default;
Camera::Camera(float x, float y, float dw, float dh, int32_t cw, int32_t ch) {
    this->x = x;
    this->y = y;

    this->dw = dw;
    this->dh = dh;

    this->cw = cw;
    this->ch = ch;
}
void Camera::move(int32_t direction) {
    float t = (float)this->moveTimer.getElapsedTime().asMilliseconds() / 1000;
    this->moveTimer.restart();

    float dst = Camera::Speed * t;

    if (direction & Camera::Direction::North) this->y = std::max(0.f, this->y - dst);
    if (direction & Camera::Direction::West) this->x = std::max(0.f, this->x - dst);

    if (direction & Camera::Direction::South) this->y = std::min(64 * (float)this->ch - this->dh, this->y + dst);
    if (direction & Camera::Direction::East) this->x = std::min(64 * (float)this->cw - this->dw, this->x + dst);
}
bool Camera::contain(float objectX, float objectY, float objectW, float objectH) const {
    sf::FloatRect camera = {this->x, this->y, this->dw, this->dh};
    sf::FloatRect object = {objectX, objectY, objectW, objectH};

    return camera.intersects(object);
}
bool Camera::contain(int32_t objectCX, int32_t objectCY) const {
    return Camera::contain((float)objectCX * 64, (float)objectCY * 64, 64, 64);
}
float Camera::getX() const {
    return this->x;
}
float Camera::getY() const {
    return this->y;
}
float Camera::getMiddleX() const {
    return this->x + this->dw / 2;
}
float Camera::getMiddleY() const {
    return this->y + this->dh / 2;
}