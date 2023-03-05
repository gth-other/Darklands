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


#include "ShoppingList.hpp"


ShoppingList::ShoppingList() = default;
ShoppingList::ShoppingList(int32_t x, int32_t y, int32_t w, int32_t h, int32_t delay, Player *player, Storage *storage) {
    this->x = x;
    this->y = y;

    this->w = w;
    this->h = h;

    this->delay = delay;
    this->player = player;
    this->storage = storage;
}
void ShoppingList::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int32_t i = 0; i < costs.size(); i = i + 1) {
        sf::RectangleShape rect = this->rects[i];
        sf::Sprite sprite = this->sprites[i];
        sf::Text text = this->texts[i];
        if (this->player->canBuy(this->costs[i]) and (this->places[i] == 0 or this->player->getHumanNumber() + this->places[i] <= this->player->getHumanLimit())) text.setFillColor({255, 255, 255, 255});
        else text.setFillColor({255, 0, 0, 255});

        target.draw(rect, states);
        target.draw(sprite, states);
        target.draw(text, states);
    }
}
void ShoppingList::addGood(const sf::Texture& texture, std::string message, Resources cost, int32_t place) {
    message.push_back('\n');
    if (cost.getFood() > 0) message.append("Еда: " + std::to_string((int32_t)cost.getFood()) + ". ");
    if (cost.getWood() > 0) message.append("Дерево: " + std::to_string((int32_t)cost.getWood()) + ". ");
    if (cost.getStone() > 0) message.append("Камень: " + std::to_string((int32_t)cost.getStone()) + ". ");
    if (cost.getIron() > 0) message.append("Железо: " + std::to_string((int32_t)cost.getIron()) + ". ");
    if (cost.getGold() > 0) message.append("Золото: " + std::to_string((int32_t)cost.getGold()) + ". ");
    if (place > 0) message.append("Необходимое пространство: " + std::to_string(place) + ". ");

    sf::RectangleShape rect;
    rect.setPosition((float)this->x, (float)this->y);
    rect.setSize(sf::Vector2f((float)this->w, (float)this->h));
    rect.setOutlineThickness(2);
    rect.setFillColor({0, 0, 0, 127});
    rect.setOutlineColor({0, 0, 0, 255});

    sf::Sprite sprite;
    sprite.setPosition((float)this->x, (float)this->y);
    sprite.setTexture(texture);

    sf::Text text;
    text.setPosition((float)this->x + sprite.getLocalBounds().width + 10, (float)this->y + 10);
    text.setFont(this->storage->getFont("main"));
    text.setCharacterSize(14);
    text.setOutlineThickness(1);
    text.setFillColor({255, 255, 255, 255});
    text.setOutlineColor({0, 0, 0, 255});

    std::string buff;
    for (int32_t i = 0; i < message.size(); i = i + 1) {
        buff.push_back(message[i]);
        if (buff.back() == ' ' or i == message.size() - 1) {
            text.setString(sf::String::fromUtf8(buff.begin(), buff.end()));
            if (text.getPosition().x + text.getLocalBounds().width + 10 > rect.getPosition().x + rect.getSize().x) {
                for (int32_t j = i - 1; j >= 0; j = j - 1) {
                    if (buff[j] == ' ') {
                        buff[j] = '\n';
                        break;
                    }
                }
            }
        }
    }
    text.setString(sf::String::fromUtf8(buff.begin(), buff.end()));

    this->y = this->y + this->h + this->delay;

    this->rects.push_back(rect);
    this->sprites.push_back(sprite);
    this->texts.push_back(text);
    this->costs.push_back(cost);
    this->places.push_back(place);
}
bool ShoppingList::clicked(int32_t i) {
    return Cursor().on(this->rects[i]);
}
Resources ShoppingList::getCost(int32_t i) {
    return this->costs[i];
}