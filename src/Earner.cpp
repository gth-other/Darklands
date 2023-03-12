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


#include "Earner.hpp"


Earner::Earner() = default;
Earner::Earner(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Human(x, y, player, camera, soundQueue, storage) {
    this->bag = 0;

    this->foodCollectionInProgress = false;
    this->woodCollectionInProgress = false;
    this->stoneCollectionInProgress = false;
    this->ironCollectionInProgress = false;
}
void Earner::startFoodCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->foodCollectionInProgress = true;
    this->bag = 0;
}
void Earner::startWoodCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->woodCollectionInProgress = true;
    this->bag = 0;
}
void Earner::startStoneCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->stoneCollectionInProgress = true;
    this->bag = 0;
}
void Earner::startIronCollection(int32_t cx, int32_t cy) {
    this->setTarget(cx, cy);
    this->ironCollectionInProgress = true;
    this->bag = 0;
}
void Earner::stopCollection() {
    this->setTarget(this->getX(), this->getY());
    this->foodCollectionInProgress = false;
    this->woodCollectionInProgress = false;
    this->stoneCollectionInProgress = false;
    this->ironCollectionInProgress = false;
}
float Earner::getCapacity() const {
    return this->getBaseCapacity() * (1 + this->player->researched(Science::Keys::WarriorsCapacity));
}
void Earner::updateCollection(std::vector<ResourceBuilding*> &rbs, std::vector<ResourcePoint*> &rps) {
    if ((!this->foodCollectionInProgress and !this->woodCollectionInProgress and !this->stoneCollectionInProgress and !this->ironCollectionInProgress) or !this->targetReached()) {
        return;
    }

    auto humanCX = (int32_t)this->getX() / 64;
    auto humanCY = (int32_t)this->getY() / 64;

    for (const auto& rb : rbs) {
        if (rb->getPlayerPtr() != this->getPlayerPtr() or humanCX != rb->getCX() or humanCY != rb->getCY()) {
            continue;
        }
        if (this->correctResourceBuilding(rb)) {
            if (rb->alive()) {
                rb->getPlayerPtr()->addResources({(float)this->foodCollectionInProgress * this->bag, (float)this->woodCollectionInProgress * this->bag, (float)this->stoneCollectionInProgress * this->bag, (float)this->ironCollectionInProgress * bag, 0});
                this->bag = 0;
                try {
                    auto p = this->tryToFindBestResourcePoint(rps);
                    this->setTarget(p.first, p.second);
                }
                catch (std::exception& e) {
                    this->stopCollection();
                }
                return;
            }
            else {
                try {
                    auto p = this->tryToFindBestResourceBuilding(rbs);
                    this->setTarget(p.first, p.second);
                }
                catch (std::exception& e) {
                    this->stopCollection();
                }
                return;
            }
        }
    }

    for (const auto& rp : rps) {
        if (humanCX != rp->getCX() or humanCY != rp->getCY()) {
            continue;
        }
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
        catch (std::exception& e) {
            this->stopCollection();
        }
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
            catch (std::exception& e) {
                this->stopCollection();
            }
        }
    }
}
std::pair<int32_t, int32_t> Earner::tryToFindBestResourceBuilding(std::vector<ResourceBuilding*> &rbs) const {
    auto closestDST = 1e+9;
    int32_t closestIndex = -1;
    for (int32_t i = 0; i < rbs.size(); i = i + 1) {
        if (!rbs[i]->alive() or rbs[i]->getPlayerPtr() != this->player) {
            continue;
        }
        if (this->correctResourceBuilding(rbs[i])) {
            auto dst = std::sqrt(std::pow(this->getX() - 64.f * (float)(rbs[i]->getCX()), 2) + std::pow(this->getY() - 64.f * (float)(rbs[i]->getCY()), 2));
            if (closestDST > dst) {
                closestDST = dst;
                closestIndex = i;
            }
        }
    }

    if (closestIndex == -1) throw std::exception();
    return std::make_pair(rbs[closestIndex]->getCX(), rbs[closestIndex]->getCY());
}
std::pair<int32_t, int32_t> Earner::tryToFindBestResourcePoint(std::vector<ResourcePoint*> &rps) const {
    auto closestDST = 1e+9;
    int32_t closestIndex = -1;
    for (int32_t i = 0; i < rps.size(); i = i + 1) {
        if (!rps[i]->alive()) {
            continue;
        }
        if (this->correctResourcePoint(rps[i])) {
            auto dst = std::sqrt(std::pow(this->getX() - 64.f * (float)(rps[i]->getCX()), 2) + std::pow(this->getY() - 64.f * (float)(rps[i]->getCY()), 2));
            if (closestDST > dst) {
                closestDST = dst;
                closestIndex = i;
            }
        }
    }

    if (closestIndex == -1) throw std::exception();
    return std::make_pair(rps[closestIndex]->getCX(), rps[closestIndex]->getCY());
}
bool Earner::correctResourceBuilding(ResourceBuilding *rb) const {
    return (this->foodCollectionInProgress and dynamic_cast<Windmill*>(rb)) or
           (this->woodCollectionInProgress and dynamic_cast<Sawmill*>(rb)) or
           (this->stoneCollectionInProgress and dynamic_cast<Quarry*>(rb)) or
           (this->ironCollectionInProgress and dynamic_cast<Smelter*>(rb));
}
bool Earner::correctResourcePoint(ResourcePoint *rp) const {
    return (this->foodCollectionInProgress and dynamic_cast<Plant*>(rp)) or
           (this->woodCollectionInProgress and dynamic_cast<Tree*>(rp)) or
           (this->stoneCollectionInProgress and dynamic_cast<Mountain*>(rp)) or
           (this->ironCollectionInProgress and dynamic_cast<RedMountain*>(rp));
}