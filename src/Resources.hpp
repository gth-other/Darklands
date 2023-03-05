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


#pragma once


class Resources {
public:
    Resources();
    Resources(float food, float wood, float stone, float iron, float gold);

    friend Resources operator+(Resources l, Resources r);
    friend Resources operator-(Resources l, Resources r);
    friend Resources operator*(Resources l, float r);
    friend Resources operator*(float l, Resources r);

    friend bool operator>(Resources l, Resources r);
    friend bool operator>=(Resources l, Resources r);
    friend bool operator<(Resources l, Resources r);
    friend bool operator<=(Resources l, Resources r);

    void setFood(float foodNew);
    void setWood(float woodNew);
    void setStone(float stoneNew);
    void setIron(float ironNew);
    void setGold(float goldNew);

    [[nodiscard]] float getFood() const;
    [[nodiscard]] float getWood() const;
    [[nodiscard]] float getStone() const;
    [[nodiscard]] float getIron() const;
    [[nodiscard]] float getGold() const;
private:
    float food;
    float wood;
    float stone;
    float iron;
    float gold;
};