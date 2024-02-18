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


#include "Lord.hpp"


Lord::Lord() = default;
Lord::Lord(sf::Vector2f position, Player *player, std::vector<sf::Vector2f> *resPositions, std::list<std::unique_ptr<Enemy>> *enemies) : Patroller(position, player) {
    this->deathCtr = 0;
    this->resPositions = resPositions;
    this->enemies = enemies;
}
void Lord::kill(const std::string &reason) {
    this->deathCtr = this->deathCtr + 1;
    if (this->deathCtr == MAXIMAL_DEATHS) {
        this->Creature::kill(reason);
    }
    else {
        SoundQueue::get()->push(Storage::get()->getSoundBuffer("darkMagick"), 0, 0);
        this->teleport();
        this->callSouls();
    }
}
std::string Lord::getMurderSoundName() const {
    return "sword";
}
int32_t Lord::getID() const {
    return 320;
}
bool Lord::isBoss() const {
    return true;
}
float Lord::getMaximalMoveSpeed() const {
    return 32 * (float)(MAXIMAL_DEATHS - this->deathCtr) * 2;
}
float Lord::getMoveAcceleration() const {
    return this->getMaximalMoveSpeed() * 4;
}
float Lord::getJumpSpeed() const {
    return 750;
}
float Lord::getG() const {
    return 750 * 3;
}
std::string Lord::getTextureName() const {
    return "lord";
}
int32_t Lord::getMSPerFrame() const {
    return 125;
}
void Lord::teleport() {
    float maxDst = 0;
    int32_t id = 0;
    for (int32_t i = 0; i < this->resPositions->size(); i = i + 1) {
        float dst = std::abs(this->getPlayer()->getCenterX() - this->resPositions->at(i).x);
        if (dst > maxDst) {
            maxDst = dst;
            id = i;
        }
    }
    this->setPosition(this->resPositions->at(id));
}
void Lord::callSouls() {
    float minDst = 1e+9;
    int32_t id1 = 0;
    for (int32_t i = 0; i < this->resPositions->size(); i = i + 1) {
        float dst = std::abs(this->getPlayer()->getCenterX() - this->resPositions->at(i).x);
        if (dst < minDst) {
            minDst = dst;
            id1 = i;
        }
    }

    minDst = 1e+9;
    int32_t id2 = 0;
    for (int32_t i = 0; i < this->resPositions->size(); i = i + 1) {
        if (i == id1) {
            continue;
        }
        float dst = std::abs(this->getPlayer()->getCenterX() - this->resPositions->at(i).x);
        if (dst < minDst) {
            minDst = dst;
            id2 = i;
        }
    }

    for (int32_t i = 0; i < this->resPositions->size(); i = i + 1) {
        if (i == id1 or i == id2) {
            continue;
        }
        this->enemies->push_back(std::make_unique<Soul>(this->resPositions->at(i), this->getPlayer()));
    }
}