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


#include "Cannon.hpp"


Cannon::Cannon() = default;
Cannon::Cannon(sf::Vector2f position, bool right) : AsymmetricalWeapon(position, right) {}
float Cannon::getMinimalLength() const {
    return 32 * 4;
}
float Cannon::getMaximalLength() const {
    return 32 * 30;
}
float Cannon::getNormalAlpha() const {
    return 30;
}
int32_t Cannon::getShotsInRow() const {
    return 1;
}
float Cannon::getShortDelay() const {
    return 1;
}
float Cannon::getLongDelay() const {
    return 1;
}
sf::Vector2f Cannon::getBulletSize() const {
    return {14, 22};
}
float Cannon::getBulletG() const {
    return 750;
}
int32_t Cannon::getLeftMuzzleID() const {
    return 301;
}
int32_t Cannon::getRightMuzzleID() const {
    return 294;
}