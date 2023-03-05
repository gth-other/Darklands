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


#include "GameObject.hpp"
#include "StatusBar.hpp"


#pragma once


class Stationary : public GameObject {
public:
    Stationary();
    Stationary(int32_t cx, int32_t cy, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    [[nodiscard]] bool alive() const override;

    [[nodiscard]] int32_t getCX() const;
    [[nodiscard]] int32_t getCY() const;
    [[nodiscard]] float getHP() const;

    void setCX(int32_t newCX);
    void setCY(int32_t newCY);
    void setHP(float newHP);
protected:
    [[nodiscard]] virtual float getMaxHP() const = 0;
private:
    int32_t cx, cy;
    float hp;

    static constexpr float MaxHP = -1;
};