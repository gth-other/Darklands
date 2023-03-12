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


#include "Warrior.hpp"


Warrior::Warrior() = default;
Warrior::Warrior(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Earner(x, y, player, camera, soundQueue, storage) {
    this->attackTargetX = 0;
    this->attackTargetY = 0;

    std::random_device rd;
    this->mersenne = std::mt19937(rd());

    this->_attackStarted = false;
}
void Warrior::update(std::vector<DefenseBuilding*> &defenseBuildings, std::vector<ResourceBuilding*> &rbs, std::vector<ResourcePoint*> &rps, std::vector<Building*> &buildings, std::vector<Warrior*> &warriors) {
    this->updateMoving();
    this->updateDefenseBuildings(defenseBuildings);
    this->updateCollection(rbs, rps);
    this->updateAttack(buildings, warriors);
}
std::string Warrior::calcAttackDirection() const {
    double dstX = std::abs(this->getX() - this->attackTargetX);
    double dstY = std::abs(this->getY() - this->attackTargetY);
    double dst = std::sqrt(std::pow(dstX, 2) + std::pow(dstY, 2));

    double sin = dstX / dst;
    double degree = std::asin(sin) * 180 / M_PI;

    if (degree <= 30) {
        if (this->attackTargetY < this->getY()) return "N";
        return "S";
    }
    else if (degree <= 60) {
        std::string result;
        if (this->attackTargetY < this->getY()) result.append("N");
        else result.append("S");
        if (this->attackTargetX < this->getX()) result.append("W");
        else result.append("E");
        return result;
    }
    else {
        if (this->attackTargetX < this->getX()) return "W";
        return "E";
    }
}
sf::IntRect Warrior::getTextureRect() const {
    int32_t animations = (int32_t)this->getTexture().getSize().x / 32;
    int32_t number;
    if (this->alive()) {
        if (this->attackStarted()) {
            number = this->attackAnimationTimer.getElapsedTime().asMilliseconds() / (this->getAttackDelay() / animations) % animations;
        }
        else {
            number = this->animationClock.getElapsedTime().asMilliseconds() / (1000 / animations) % animations;
        }
    }
    else {
        number = std::min(animations - 1, this->deathAnimationTimer.getElapsedTime().asMilliseconds() * 2 / (1000 / animations)) % animations;
    }

    return {number * 32, 0, 32, 32};
}
bool Warrior::attackStarted() const {
    return this->_attackStarted;
}
Building* Warrior::tryToFindBuildingInAttackRadius(std::vector<Building*> &buildings) const {
    for (const auto& b : buildings) {
        if (!b->alive() or b->getPlayerPtr() == this->getPlayerPtr()) continue;

        float dstX1 = (this->getX() + 16) - (b->getCX() * 64);
        float dstY1 = (this->getY() + 16) - (b->getCY() * 64);
        auto dst1 = (float)std::sqrt(std::pow(dstX1, 2) + std::pow(dstY1, 2));

        float dstX2 = (this->getX() + 16) - (b->getCX() * 64 + 64);
        float dstY2 = (this->getY() + 16) - (b->getCY() * 64 + 64);
        auto dst2 = (float)std::sqrt(std::pow(dstX2, 2) + std::pow(dstY2, 2));

        float dstX3 = (this->getX() + 16) - (b->getCX() * 64 + 64);
        float dstY3 = (this->getY() + 16) - (b->getCY() * 64);
        auto dst3 = (float)std::sqrt(std::pow(dstX3, 2) + std::pow(dstY3, 2));

        float dstX4 = (this->getX() + 16) - (b->getCX() * 64);
        float dstY4 = (this->getY() + 16) - (b->getCY() * 64 + 64);
        auto dst4 = (float)std::sqrt(std::pow(dstX4, 2) + std::pow(dstY4, 2));

        if (std::min(std::min(dst1, dst2), std::min(dst3, dst4)) < this->getAttackRadius()) {
            return b;
        }
    }
    throw std::exception();
}
Warrior* Warrior::tryToFindWarriorInAttackRadius(std::vector<Warrior*> &warriors) const {
    for (const auto &w : warriors) {
        if (!w->alive() or w->getPlayerPtr() == this->getPlayerPtr()) continue;

        float dstX = (this->getX() + 16) - (w->getX() + 16);
        float dstY = (this->getY() + 16) - (w->getY() + 16);
        auto dst = (float)std::sqrt(std::pow(dstX, 2) + std::pow(dstY, 2));

        if (dst < this->getAttackRadius()) {
            return w;
        }
    }
    throw std::exception();
}
void Warrior::updateAttack(std::vector<Building*> &buildings, std::vector<Warrior*> &warriors) {
    if (this->_attackStarted and this->attackAnimationTimer.getElapsedTime().asMilliseconds() >= this->getAttackDelay()) {
        try {
            Warrior *w = this->tryToFindWarriorInAttackRadius(warriors);
            auto probability = (uint32_t)(this->getWarriorAttack() / w->getDefense() * 100.f);
            uint32_t random = mersenne() % 100;
            if (random < probability) {
                w->kill();;
            }
        }
        catch (std::exception &e) {
            try {
                Building *b = this->tryToFindBuildingInAttackRadius(buildings);
                b->setHP(std::max(0.f, b->getHP() - this->getBuildingAttack()));
            }
            catch (std::exception &e) {}
        }
        this->soundQueue->push(this->getSelectSoundBuffer());
        this->_attackStarted = false;
        return;
    } 

    if (!this->_attackStarted) {
        try {
            Warrior *w = this->tryToFindWarriorInAttackRadius(warriors);
            this->_attackStarted = true;
            this->setTarget(this->getX(), this->getY());
            this->attackAnimationTimer.restart();
            this->attackTargetX = w->getX() + 16;
            this->attackTargetY = w->getY() + 16;
        }
        catch (std::exception &e) {
            try {
                Building *b = this->tryToFindBuildingInAttackRadius(buildings);
                this->_attackStarted = true;
                this->setTarget(this->getX(), this->getY());
                this->attackAnimationTimer.restart();
                this->attackTargetX = (float)b->getCX() * 64 + 32;
                this->attackTargetY = (float)b->getCY() * 64 + 32;
            }
            catch (std::exception &e) {}
        }
    }
}