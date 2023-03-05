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


#include <cstdint>
#include "Storage.hpp"
#include "Camera.hpp"


#pragma once


class Cursor : public sf::Drawable {
public:
    Cursor();
    Cursor(Storage *storage, Camera *camera = nullptr);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool on(int32_t x, int32_t y, int32_t w, int32_t h);
    bool on(int32_t cx, int32_t cy);
    bool on(const sf::RectangleShape &rect);
    bool on(const sf::Sprite& sprite);
private:
    Storage *storage;
    Camera *camera;

    static bool pressed();
};