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


#include "AreaController.hpp"


AreaController::AreaController() = default;
AreaController::AreaController(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Building(cx, cy, player, camera, soundQueue, storage) {}
void AreaController::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Stationary::draw(target, states);
    if (this->selected()) this->drawCircle(target, states);
}
bool AreaController::cover(float x, float y) const {
    float dstX = (float)this->getCX() * 64 + 32 - x;
    float dstY = (float)this->getCY() * 64 + 32 - y;
    auto dst = std::sqrt(std::pow(dstX, 2) + std::pow(dstY, 2));

    return dst < this->getRadius();
}
bool AreaController::cover(int32_t cx, int32_t cy) const {
    return this->cover(64 * (float)cx + 32, 64 * (float)cy + 32);
}
void AreaController::drawCircle(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape circle;
    circle.setPointCount(90);
    circle.setRadius(this->getRadius());
    circle.setPosition((float)this->getCX() * 64 + 32 - this->getRadius() - this->camera->getX(), (float)this->getCY() * 64 + 32 - this->getRadius() - this->camera->getY());
    circle.setFillColor({0, 0, 0, 0});
    circle.setOutlineThickness(4);
    circle.setOutlineColor({255, 255, 255, 255});

    target.draw(circle, states);
}