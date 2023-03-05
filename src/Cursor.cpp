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


Cursor::Cursor() = default;
Cursor::Cursor(Storage *storage, Camera *camera) {
    this->storage = storage;
    this->camera = camera;
}
void Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sprite.setTexture(this->storage->getTexture("cursor"));
    sprite.setPosition((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);

    if (Cursor::pressed()) sprite.setTextureRect({38, 0, 38, 41});
    else sprite.setTextureRect({0, 0, 38, 41});

    target.draw(sprite, states);
}
bool Cursor::on(int32_t x, int32_t y, int32_t w, int32_t h) {
    int32_t mouseCornerX = sf::Mouse::getPosition().x;
    int32_t mouseCornerY = sf::Mouse::getPosition().y;

    return (mouseCornerX >= x and mouseCornerY >= y and mouseCornerX < x + w and mouseCornerY < y + h);
}
bool Cursor::on(int32_t cx, int32_t cy) {
    return this->on(64 * cx - (int32_t)this->camera->getX(), 64 * cy - (int32_t)this->camera->getY(), 64, 64);
}
bool Cursor::on(const sf::RectangleShape &rect) {
    return this->on((int32_t)rect.getPosition().x, (int32_t)rect.getPosition().y, (int32_t)rect.getSize().x, (int32_t)rect.getSize().y);
}
bool Cursor::on(const sf::Sprite& sprite) {
    return this->on((int32_t)sprite.getPosition().x, (int32_t)sprite.getPosition().y, (int32_t)sprite.getLocalBounds().width, (int32_t)sprite.getLocalBounds().height);
}
bool Cursor::pressed() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}