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


#include "Cursor.hpp"
#include "Screen.hpp"


#pragma once


class Menu : public Screen {
public:
    Menu();
    Menu(Storage *storage, SoundQueue *soundQueue, sf::RenderWindow *window);

    int32_t open() override;
private:
    sf::RectangleShape newGameRect;
    sf::Text newGameText;

    sf::Text title;
    sf::Text copyright;
    sf::Sprite logotype;
    Cursor cursor;

    sf::Clock animationClock;

    void updateLogotypeTexture();
};