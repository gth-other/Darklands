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


#include "Vampire.hpp"


Vampire::Vampire() = default;
Vampire::Vampire(sf::Vector2f position, Player *player, Storage *storage, SoundQueue *soundQueue, Map *map) : Patroller(position, player, storage, soundQueue, map) {}
std::string Vampire::getMurderSoundName() const {
    return "bite";
}
float Vampire::getMaximalMoveSpeed() const {
    return 32 * 13;
}
float Vampire::getMoveAcceleration() const {
    return 32 * 13 * 4;
}
float Vampire::getJumpSpeed() const {
    return 750;
}
float Vampire::getG() const {
    return 750 * 3;
}
std::string Vampire::getTextureName() const {
    return "vampire";
}
int32_t Vampire::getMSPerFrame() const {
    return 150;
}