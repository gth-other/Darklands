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


#include "Weapon.hpp"


#pragma once


class AsymmetricalWeapon : public Weapon {
public:
    AsymmetricalWeapon();
    AsymmetricalWeapon(sf::Vector2f position, bool right);
protected:
    [[nodiscard]] virtual float getNormalAlpha() const = 0;
    [[nodiscard]] virtual int32_t getLeftMuzzleID() const = 0;
    [[nodiscard]] virtual int32_t getRightMuzzleID() const = 0;
private:
    bool right;

    [[nodiscard]] bool impossibleToShoot(const Player *player) const override;
    [[nodiscard]] float getAlpha(const Player *player) const override;
};