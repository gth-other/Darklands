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


#include "Archer.hpp"


Archer::Archer() = default;
Archer::Archer(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Warrior(x, y, player, camera, soundQueue, storage) {}
Resources Archer::getCost() const {
    return {10, 10, 0, 0, 0};
}
std::string Archer::getDescription() const {
    return "Лучники имеют слабую защиту, средний урон и малую грузоподъемность.";
}
const sf::SoundBuffer &Archer::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("archery");
}
const sf::Texture &Archer::getTexture() const {
    if (this->alive()) {
        if (this->attackStarted()) return this->storage->getTexture("archerAttack" + this->calcAttackDirection());
        if (this->targetReached()) return this->storage->getTexture("archerRest" + this->calcMovementDirection());
        return this->storage->getTexture("archerWalk" + this->calcMovementDirection());
    }
    if (this->targetReached()) return this->storage->getTexture("archerDie" + this->calcMovementDirection());
    return this->storage->getTexture("archerDie" + this->calcMovementDirection());
}
float Archer::getDefense() const {
    return 2;
}
float Archer::getBuildingAttack() const {
    return 5;
}
float Archer::getWarriorAttack() const {
    return 1;
}
float Archer::getAttackRadius() const {
    return 2 * 64;
}
int32_t Archer::getAttackDelay() const {
    return 1000;
}
float Archer::getSpeed() const {
    return 32;
}
float Archer::getBaseCapacity() const {
    return 1;
}