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


#include <SFML/Graphics.hpp>
#include <cstdint>


#pragma once


class Camera {
public:
    Camera();
    Camera(float x, float y, float dw, float dh, int32_t cw, int32_t ch);

    void move(int32_t direction);
    [[nodiscard]] bool contain(float objectX, float objectY, float objectW, float objectH) const;
    [[nodiscard]] bool contain(int32_t objectCX, int32_t objectCY) const;

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;

    [[nodiscard]] float getMiddleX() const;
    [[nodiscard]] float getMiddleY() const;

    enum Direction {
        North = 0b1,
        South = 0b10,
        West = 0b100,
        East = 0b1000
    };
private:
    float x, y;
    float dw, dh;
    int32_t cw, ch;

    sf::Clock moveTimer;

    static constexpr float Speed = 256;
};