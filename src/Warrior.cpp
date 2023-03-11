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
Warrior::Warrior(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Unit(player), GameObject(camera, soundQueue, storage) {
    this->x = x;
    this->y = y;

    this->targetX = this->x;
    this->targetY = this->y;

    this->_alive = true;

    this->foodCollectionInProgress = false;
    this->woodCollectionInProgress = false;
    this->stoneCollectionInProgress = false;
    this->ironCollectionInProgress = false;

    this->bag = 0;
}
void Warrior::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!this->camera->contain(this->x, this->y, 32, 32)) {
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(this->getTexture());
    sprite.setTextureRect(this->getTextureRect());
    sprite.setPosition(this->x - this->camera->getX(), this->y - this->camera->getY());

    sf::Color playerColor = this->player->getColor();
    if (playerColor.r > playerColor.g and playerColor.r > playerColor.b) {
        playerColor.r = 200;
        playerColor.g = 180 - 50 * this->selected();
        playerColor.b = 180 - 50 * this->selected();
    }
    else if (playerColor.g > playerColor.r and playerColor.g > playerColor.b) {
        playerColor.r = 225 - 50 * this->selected();
        playerColor.g = 255;
        playerColor.b = 225 - 50 * this->selected();
    }
    else {
        playerColor.r = 150 - 50 * this->selected();
        playerColor.g = 150 - 50 * this->selected();
        playerColor.b = 255;
    }
    sprite.setColor(playerColor);

    target.draw(sprite, states);
}
void Warrior::update(std::vector<DefenseBuilding*> &defenseBuildings, std::vector<ResourceBuilding *> &rbs, std::vector<ResourcePoint *> &rps) {
    this->updateMoving();
    this->updateDefenseBuildings(defenseBuildings);
    this->updateCollection(rbs, rps);
}
void Warrior::setTarget(float newTargetX, float newTargetY) {
    this->targetX = newTargetX;
    this->targetY = newTargetY;
}
void Warrior::setTarget(int32_t newTargetCX, int32_t newTargetCY) {
    this->setTarget(64 * (float) newTargetCX + 16, 64 * (float) newTargetCY + 16);
}
void Warrior::startFoodCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->foodCollectionInProgress = true;
    this->bag = 0;
}
void Warrior::startWoodCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->woodCollectionInProgress = true;
    this->bag = 0;
}
void Warrior::startStoneCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->stoneCollectionInProgress = true;
    this->bag = 0;
}
void Warrior::startIronCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->ironCollectionInProgress = true;
    this->bag = 0;
}
void Warrior::stopCollection() {
    this->setTarget(this->getX(), this->getY());
    this->foodCollectionInProgress = false;
    this->woodCollectionInProgress = false;
    this->stoneCollectionInProgress = false;
    this->ironCollectionInProgress = false;
}
void Warrior::kill() {
    this->_alive = false;
    this->deathAnimationClock.restart();
}
bool Warrior::targetReached() const {
    bool dxZero = std::abs(this->x - this->targetX) < 16;
    bool dyZero = std::abs(this->y - this->targetY) < 16;

    return (dxZero and dyZero);
}
bool Warrior::alive() const {
    return this->_alive;
}
std::string Warrior::calcDirection() const {
    float vMedium = this->getSpeed() / 1.4142f;
    float vMediumPart = vMedium / 3;

    float vx, vy;
    std::tie(vx, vy) = this->calcSpeed();

    if (vy > vMediumPart) {
        if (vx > vMediumPart) return "SE";
        if (vx < -vMediumPart) return "SW";
        return "S";
    }

    if (vy < -vMediumPart) {
        if (vx > vMediumPart) return "NE";
        if (vx < -vMediumPart) return "NW";
        return "N";
    }

    if (vx < -vMediumPart) return "W";
    return "E";
}
float Warrior::getX() const {
    return this->x;
}
float Warrior::getY() const {
    return this->y;
}
void Warrior::setX(float newX) {
    this->x = newX;
}
void Warrior::setY(float newY) {
    this->y = newY;
}
float Warrior::getCapacity() const {
    return this->getBaseCapacity() * (1 + this->player->researched(Science::Keys::WarriorsCapacity));
}
sf::IntRect Warrior::getTextureRect() const {
    int32_t animations = (int32_t)this->getTexture().getSize().x / 32;
    int32_t ms = 1000 / animations;
    int32_t number;
    if (this->alive()) number = this->animationClock.getElapsedTime().asMilliseconds() / ms % animations;
    else number = std::min(animations - 1, this->deathAnimationClock.getElapsedTime().asMilliseconds() * 2 / ms);

    return {number * 32, 0, 32, 32};
}
std::pair<float, float> Warrior::calcSpeed() const {
    if (this->targetReached()) {
        return std::make_pair(0, 0);
    }

    float dstX = this->x - this->targetX;
    float dstY = this->y - this->targetY;

    auto vy = (float)std::sqrt(std::pow(dstY * this->getSpeed(), 2) / (std::pow(dstY, 2) + std::pow(dstX, 2)));
    auto vx = (float)std::sqrt(std::pow(this->getSpeed(), 2) - std::pow(vy, 2));

    if (dstX > 0) vx = -vx;
    if (dstY > 0) vy = -vy;

    return std::make_pair(vx, vy);
}
std::pair<int32_t, int32_t> Warrior::tryToFindBestResourceBuilding(std::vector<ResourceBuilding*> &rbs) const {
    auto closestDST = 1e+9;
    int32_t closestIndex = -1;
    for (int32_t i = 0; i < rbs.size(); i = i + 1) {
        if (!rbs[i]->alive() or rbs[i]->getPlayerPtr() != this->player) continue;
        if (this->correctResourceBuilding(rbs[i])) {
            auto dst = std::sqrt(std::pow(x - 64.f * (float)(rbs[i]->getCX()), 2) + std::pow(y - 64.f * (float)(rbs[i]->getCY()), 2));
            if (closestDST > dst) {
                closestDST = dst;
                closestIndex = i;
            }
        }
    }

    if (closestIndex == -1) throw std::exception();
    return std::make_pair(rbs[closestIndex]->getCX(), rbs[closestIndex]->getCY());
}
std::pair<int32_t, int32_t> Warrior::tryToFindBestResourcePoint(std::vector<ResourcePoint*> &rps) const {
    auto closestDST = 1e+9;
    int32_t closestIndex = -1;
    for (int32_t i = 0; i < rps.size(); i = i + 1) {
        if (!rps[i]->alive()) continue;
        if (this->correctResourcePoint(rps[i])) {
            auto dst = std::sqrt(std::pow(x - 64.f * (float)(rps[i]->getCX()), 2) + std::pow(y - 64.f * (float)(rps[i]->getCY()), 2));
            if (closestDST > dst) {
                closestDST = dst;
                closestIndex = i;
            }
        }
    }

    if (closestIndex == -1) throw std::exception();
    return std::make_pair(rps[closestIndex]->getCX(), rps[closestIndex]->getCY());
}
bool Warrior::correctResourceBuilding(ResourceBuilding *rb) const {
    return (this->foodCollectionInProgress and dynamic_cast<Windmill*>(rb)) or
           (this->woodCollectionInProgress and dynamic_cast<Sawmill*>(rb)) or
           (this->stoneCollectionInProgress and dynamic_cast<Quarry*>(rb)) or
           (this->ironCollectionInProgress and dynamic_cast<Smelter*>(rb));
}
bool Warrior::correctResourcePoint(ResourcePoint *rp) const {
    return (this->foodCollectionInProgress and dynamic_cast<Plant*>(rp)) or
           (this->woodCollectionInProgress and dynamic_cast<Tree*>(rp)) or
           (this->stoneCollectionInProgress and dynamic_cast<Mountain*>(rp)) or
           (this->ironCollectionInProgress and dynamic_cast<RedMountain*>(rp));
}
void Warrior::updateMoving() {
    float t = (float) this->movementTimer.getElapsedTime().asMilliseconds() / 1000;
    this->movementTimer.restart();

    float vx, vy;
    std::tie(vx, vy) = this->calcSpeed();

    this->x = this->x + vx * t;
    this->y = this->y + vy * t;
}
void Warrior::updateDefenseBuildings(std::vector<DefenseBuilding*> &defenseBuildings) {
    for (auto &db : defenseBuildings) {
        if (db->alive() and db->getPlayerPtr() != this->getPlayerPtr() and db->readyToShoot() and db->cover(this->x + 16, this->y + 16)) {
            db->shoot();
            this->kill();
            break;
        }
    }
}
void Warrior::updateCollection(std::vector<ResourceBuilding*> &rbs, std::vector<ResourcePoint*> &rps) {
    if ((!this->foodCollectionInProgress and !this->woodCollectionInProgress and !this->stoneCollectionInProgress and !this->ironCollectionInProgress) or !this->targetReached()) {
        return;
    }

    auto humanCX = (int32_t)this->getX() / 64;
    auto humanCY = (int32_t)this->getY() / 64;

    for (const auto& rb : rbs) {
        if (rb->getPlayerPtr() != this->getPlayerPtr() or humanCX != rb->getCX() or humanCY != rb->getCY()) continue;
        if (this->correctResourceBuilding(rb)) {
            if (rb->alive()) {
                rb->getPlayerPtr()->addResources({(float)this->foodCollectionInProgress * this->bag, (float)this->woodCollectionInProgress * this->bag, (float)this->stoneCollectionInProgress * this->bag, (float)this->ironCollectionInProgress * bag, 0});
                this->bag = 0;
                try {
                    auto p = this->tryToFindBestResourcePoint(rps);
                    this->setTarget(p.first, p.second);
                }
                catch (std::exception& e) {this->stopCollection();}
                return;
            }
            else {
                try {
                    auto p = this->tryToFindBestResourceBuilding(rbs);
                    this->setTarget(p.first, p.second);
                }
                catch (std::exception& e) {this->stopCollection();}
                return;
            }
        }
    }

    for (const auto& rp : rps) {
        if (humanCX != rp->getCX() or humanCY != rp->getCY()) continue;
        if (this->correctResourcePoint(rp)) {
            float get = std::min(this->getCapacity() - this->bag, rp->getHP());
            this->bag = this->bag + get;
            rp->setHP(rp->getHP() - get);
            break;
        }
    }

    if (this->bag == this->getCapacity()) {
        try {
            auto p = this->tryToFindBestResourceBuilding(rbs);
            this->setTarget(p.first, p.second);
        }
        catch (std::exception& e) {this->stopCollection();}
    }
    else {
        try {
            auto p = this->tryToFindBestResourcePoint(rps);
            this->setTarget(p.first, p.second);
        }
        catch (std::exception& e) {
            try {
                auto p = this->tryToFindBestResourceBuilding(rbs);
                this->setTarget(p.first, p.second);
            }
            catch (std::exception& e) {this->stopCollection();}
        }
    }
}