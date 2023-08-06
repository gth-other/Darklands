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


#include "SymmetricalWeapon.hpp"


#pragma once


class Mortar : public SymmetricalWeapon {
public:
    Mortar();
    Mortar(sf::Vector2f position, Storage *storage, SoundQueue *soundQueue, Map *map, Player *player);

    [[nodiscard]] float getMinimalLength() const override;
    [[nodiscard]] float getMaximalLength() const override;
    [[nodiscard]] float getDeltaAlpha() const override;
    [[nodiscard]] int32_t getShotsInRow() const override;
    [[nodiscard]] float getShortDelay() const override;
    [[nodiscard]] float getLongDelay() const override;
    [[nodiscard]] sf::Vector2f getBulletSize() const override;
    [[nodiscard]] float getBulletG() const override;
    [[nodiscard]] int32_t getMuzzleID() const override;
};