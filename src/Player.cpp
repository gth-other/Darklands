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


#include "Player.hpp"


Player::Player() = default;
Player::Player(sf::Color color, Resources resources, float dw, Storage *storage) {
    this->color = color;
    this->resources = resources;
    this->humanLimit = 0;
    this->dw = dw;
    this->storage = storage;
}
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape base;
    base.setSize(sf::Vector2f(this->dw, 64));
    base.setFillColor({0, 0, 0, 127});
    base.setPosition(0, 0);
    target.draw(base, states);

    this->drawResource(0 * this->dw / 6, "food", std::to_string((int32_t)this->resources.getFood()), (int32_t)this->resources.getFood() == 0, target, states);
    this->drawResource(1 * this->dw / 6, "wood", std::to_string((int32_t)this->resources.getWood()), (int32_t)this->resources.getWood() == 0, target, states);
    this->drawResource(2 * this->dw / 6, "stone", std::to_string((int32_t)this->resources.getStone()), (int32_t)this->resources.getStone() == 0, target, states);
    this->drawResource(3 * this->dw / 6, "iron", std::to_string((int32_t)this->resources.getIron()), (int32_t)this->resources.getIron() == 0, target, states);
    this->drawResource(4 * this->dw / 6, "gold", std::to_string((int32_t)this->resources.getGold()), (int32_t)this->resources.getGold() == 0, target, states);
    this->drawResource(5 * this->dw / 6, "human", std::to_string((int32_t)this->getHumanNumber()) + " / " + std::to_string((int32_t)this->getHumanLimit()), this->getHumanNumber() >= this->getHumanLimit(), target, states);
}
void Player::update(int32_t newHumanNumber, int32_t newHumanLimit) {
    this->humanNumber = newHumanNumber;
    this->humanLimit = newHumanLimit;
    this->addFreeResources();
}
bool Player::canBuy(const Resources& cost) const {
    return this->resources >= cost;
}
void Player::buy(const Resources& cost) {
    this->resources = this->resources - cost;
}
void Player::addResources(Resources newResources) {
    this->resources = this->resources + newResources;
}
int32_t Player::getHumanNumber() const {
    return this->humanNumber;
}
int32_t Player::getHumanLimit() const {
    return this->humanLimit;
}
sf::Color Player::getColor() const {
    return this->color;
}
void Player::addFreeResources() {
    if (this->freeResourcesTimer.getElapsedTime().asSeconds() >= 1) {
        this->resources = this->resources + Resources(0, 0, 0, 0, 5);
        this->freeResourcesTimer.restart();
    }
}
void Player::drawResource(float x, const std::string& iconName, const std::string& value, bool red, sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite iconDrawable;
    iconDrawable.setPosition(x, 0);
    iconDrawable.setTexture(this->storage->getTexture(iconName));

    sf::Text valueDrawable;
    valueDrawable.setFont(this->storage->getFont("main"));
    valueDrawable.setString(value);
    valueDrawable.setCharacterSize(14);
    valueDrawable.setOutlineThickness(1);
    valueDrawable.setFillColor({255, (uint8_t)(255 * !red), (uint8_t)(255 * !red), 255});
    valueDrawable.setOutlineColor({0, 0, 0, 255});
    valueDrawable.setPosition(x + iconDrawable.getLocalBounds().width + 10, iconDrawable.getLocalBounds().height / 2 - valueDrawable.getLocalBounds().height);

    target.draw(iconDrawable, states);
    target.draw(valueDrawable, states);
}