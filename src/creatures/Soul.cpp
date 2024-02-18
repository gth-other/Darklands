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


#include "Soul.hpp"


Soul::Soul() = default;
Soul::Soul(sf::Vector2f position, Player *player, Storage *storage, SoundQueue *soundQueue) : Patroller(position, player, storage, soundQueue) {}
void Soul::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    float dx = std::abs(this->getCenterX() - this->getPlayer()->getCenterX());
    float dy = std::abs(this->getCenterY() - this->getPlayer()->getCenterY());
    float d = std::sqrt(dx * dx + dy * dy);
    if (d < VISIBLE_DST) {
        this->Creature::draw(target, states);
    }
}
std::string Soul::getMurderSoundName() const {
    return "soul";
}
int32_t Soul::getID() const {
    return 318;
}
bool Soul::isBoss() const {
    return false;
}
float Soul::getMaximalMoveSpeed() const {
    return 32 * 7;
}
float Soul::getMoveAcceleration() const {
    return 32 * 7 * 4;
}
float Soul::getJumpSpeed() const {
    return 500;
}
float Soul::getG() const {
    return 500 * 3;
}
std::string Soul::getTextureName() const {
    return "soul";
}
int32_t Soul::getMSPerFrame() const {
    return 75;
}