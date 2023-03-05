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


#include "Building.hpp"


Building::Building() = default;
Building::Building(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Unit(player), Stationary(cx, cy, camera, soundQueue, storage) {}
void Building::update() {
    this->updateRepairing();
}
void Building::refreshRepairTimer() {
    this->repairTimer.restart();
}
void Building::updateRepairing() {
    float t = (float)this->repairTimer.getElapsedTime().asMilliseconds() / 1000;
    this->repairTimer.restart();

    this->setHP(std::min(this->getMaxHP(), this->getHP() + this->getRepairSpeed() * t));
}