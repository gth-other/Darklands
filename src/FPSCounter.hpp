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


#pragma once


class FPSCounter : public sf::Drawable {
public:
    FPSCounter();
    FPSCounter(bool visibility, float dw, Storage *storage);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
    void invertVisibility();
private:
    sf::Clock secondsTimer;
    int32_t frames;
    sf::Text text;

    bool visibility;
    float dw;

    Storage *storage;
};