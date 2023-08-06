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


#include "Mortar.hpp"


Mortar::Mortar() = default;
Mortar::Mortar(sf::Vector2f position, Storage *storage, SoundQueue *soundQueue, Map *map, Player *player) : SymmetricalWeapon(position, storage, soundQueue, map, player) {}
float Mortar::getMinimalLength() const {
    return 32 * 6;
}
float Mortar::getMaximalLength() const {
    return 32 * 60;
}
float Mortar::getDeltaAlpha() const {
    return 15;
}
int32_t Mortar::getShotsInRow() const {
    return 3;
}
float Mortar::getShortDelay() const {
    return 0.5;
}
float Mortar::getLongDelay() const {
    return 2;
}
sf::Vector2f Mortar::getBulletSize() const {
    return {14, 22};
}
float Mortar::getBulletG() const {
    return 1250;
}
int32_t Mortar::getMuzzleID() const {
    return 307;
}