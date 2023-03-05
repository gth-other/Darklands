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


#include "StatusBar.hpp"


StatusBar::StatusBar() = default;
StatusBar::StatusBar(int32_t cx, int32_t cy, float current, float full, Camera *camera, Storage *storage) {
    float x = (float)cx * 64 + 4 - camera->getX();
    float y = (float)cy * 64 - camera->getY();

    this->rect0.setPosition(x, y);
    this->rect0.setSize(sf::Vector2f(56, 2));
    this->rect0.setOutlineThickness(1);
    this->rect0.setFillColor({20, 20, 20, 255});
    this->rect0.setOutlineColor({0, 0, 0, 255});

    this->rect1.setPosition(x, y);
    this->rect1.setSize(sf::Vector2f(56 * current / full, 2));
    this->rect1.setFillColor({(sf::Uint8)(255 - 255 * current / full), (sf::Uint8)(255 * current / full), 0, 255});

    this->text.setString(std::to_string((int32_t)current));
    this->text.setFont(storage->getFont("main"));
    this->text.setCharacterSize(10);
    this->text.setFillColor(this->rect1.getFillColor());
    this->text.setPosition(x + this->rect0.getSize().x - this->text.getLocalBounds().width, y + 4);
}
void StatusBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->rect0, states);
    target.draw(this->rect1, states);
    target.draw(this->text, states);
}