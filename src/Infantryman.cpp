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


#include "Infantryman.hpp"


Infantryman::Infantryman() = default;
Infantryman::Infantryman(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Warrior(x, y, player, camera, soundQueue, storage) {}
Resources Infantryman::getCost() const {
    return {10, 0, 0, 10, 0};
}
std::string Infantryman::getDescription() const {
    return "Пехотинцы имеют высокую защиту, средний урон и среднюю грузоподъемность.";
}
const sf::SoundBuffer &Infantryman::getSelectSoundBuffer() const {
    return this->storage->getSoundBuffer("sword");
}
const sf::Texture &Infantryman::getTexture() const {
    if (this->alive()) {
        if (this->targetReached()) return this->storage->getTexture("infantrymanRest" + this->calcDirection());
        return this->storage->getTexture("infantrymanWalk" + this->calcDirection());
    }
    if (this->targetReached()) return this->storage->getTexture("infantrymanDie" + this->calcDirection());
    return this->storage->getTexture("infantrymanDie" + this->calcDirection());
}
float Infantryman::getDefense() const {
    return 2;
}
float Infantryman::getBuildingAttack() const {
    return 5;
}
float Infantryman::getWarriorAttack() const {
    return 1;
}
float Infantryman::getAttackRadius() const {
    return 16;
}
int32_t Infantryman::getAttackDelay() const {
    return 1000;
}
float Infantryman::getSpeed() const {
    return 32;
}
float Infantryman::getBaseCapacity() const {
    return 2;
}