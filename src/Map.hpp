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


#include <vector>
#include <fstream>
#include <sstream>
#include "storages/TextureStorage.hpp"


#pragma once


class Map : public sf::Drawable {
public:
    Map();
    Map(const std::string &path, sf::View *view);
    [[nodiscard]] int32_t getID(int32_t x, int32_t y) const;
    [[nodiscard]] bool isSolid(int32_t x, int32_t y, bool checkAIBlocks) const;
    [[nodiscard]] int32_t getWidth() const;
    [[nodiscard]] int32_t getHeight() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    std::vector<std::vector<int32_t>> data;
    sf::View *view;
};