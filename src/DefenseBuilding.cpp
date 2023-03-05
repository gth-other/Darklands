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


#include "DefenseBuilding.hpp"


DefenseBuilding::DefenseBuilding() = default;
DefenseBuilding::DefenseBuilding(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : AreaController(cx, cy, player, camera, soundQueue, storage) {}
bool DefenseBuilding::readyToShoot() const {
    return this->shootingTimer.getElapsedTime().asMilliseconds() >= this->getShootingDelay();
}
void DefenseBuilding::shoot() {
    float dstX = (float)this->getCX() * 64 + 32 - this->camera->getMiddleX();
    float dstY = (float)this->getCY() * 64 + 32 - this->camera->getMiddleY();
    auto dst = (float)std::sqrt(std::pow(dstX, 2) + std::pow(dstY, 2));

    this->soundQueue->push(this->getShootingSoundBuffer(), dst);
    this->shootingTimer.restart();
}
int32_t DefenseBuilding::getShootingDelay() const {
    return this->getBaseShootingDelay() / (1 + this->player->researched(Science::Keys::DefenseBuildings));
}