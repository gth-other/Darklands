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


#include "AsymmetricalWeapon.hpp"


AsymmetricalWeapon::AsymmetricalWeapon() = default;
AsymmetricalWeapon::AsymmetricalWeapon(sf::Vector2f position, bool right) : Weapon(position) {
    this->right = right;
}
bool AsymmetricalWeapon::impossibleToShoot(const Player *player) const {
    if ((player->getCenterX() > this->getPositionX() and !this->right) or
        (player->getCenterX() < this->getPositionX() and this->right)) {
        return true;
    }
    return Weapon::impossibleToShoot(player);
}
float AsymmetricalWeapon::getAlpha(const Player *player) const {
    float alpha = this->getNormalAlpha();
    if (!this->right) {
        alpha = 180 - alpha;
    }
    return alpha;
}