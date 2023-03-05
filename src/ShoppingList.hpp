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


#include <vector>
#include "Player.hpp"
#include "Cursor.hpp"


#pragma once


class ShoppingList : public sf::Drawable {
public:
    ShoppingList();
    ShoppingList(int32_t x, int32_t y, int32_t w, int32_t h, int32_t delay, Player *player, Storage *storage);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void addGood(const sf::Texture& texture, std::string message, Resources cost, int32_t place = 0);
    [[nodiscard]] bool clicked(int32_t i);
    [[nodiscard]] Resources getCost(int32_t i);
private:
    int32_t x, y;
    int32_t w, h;
    int32_t delay;
    Player *player;
    Storage *storage;

    std::vector<sf::RectangleShape> rects;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> texts;
    std::vector<Resources> costs;
    std::vector<int32_t> places;
};