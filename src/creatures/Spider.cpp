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


#include "Spider.hpp"


Spider::Spider() = default;
Spider::Spider(sf::Vector2f position, Player *player) : Patroller(position, player) {}
std::string Spider::getMurderSoundName() const {
    return "bite";
}
int32_t Spider::getID() const {
    return 317;
}
bool Spider::isBoss() const {
    return false;
}
float Spider::getMaximalMoveSpeed() const {
    return 32 * 30;
}
float Spider::getMoveAcceleration() const {
    return 32 * 30 * 0.5;
}
float Spider::getJumpSpeed() const {
    return 1500;
}
float Spider::getG() const {
    return 1500 * 3;
}
std::string Spider::getTextureName() const {
    return "spider";
}
int32_t Spider::getMSPerFrame() const {
    return 15;
}