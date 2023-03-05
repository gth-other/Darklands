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


#include "Storage.hpp"
#include "Resources.hpp"
#include "Science.hpp"


#pragma once


class Player : public sf::Drawable, public Science {
public:
    Player();
    Player(sf::Color color, Resources resources, float dw, Storage *storage);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(int32_t newHumanNumber, int32_t newHumanLimit);

    [[nodiscard]] bool canBuy(const Resources& cost) const;
    void buy(const Resources& cost);

    void addResources(Resources newResources);

    [[nodiscard]] int32_t getHumanNumber() const;
    [[nodiscard]] int32_t getHumanLimit() const;
    [[nodiscard]] sf::Color getColor() const;
private:
    sf::Color color;
    Resources resources;
    sf::Clock freeResourcesTimer;
    int32_t humanNumber;
    int32_t humanLimit;

    float dw;
    Storage *storage;

    void addFreeResources();
    void drawResource(float x, const std::string& iconName, const std::string& value, bool red, sf::RenderTarget &target, sf::RenderStates states) const;
};