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


#include "Map.hpp"


Map::Map() = default;
Map::Map(const std::string &path, sf::View *view, Storage *storage) {
    std::ifstream file(path);
    std::string buff;
    while (std::getline(file, buff)) {
        if (buff[0] == ' ' or buff[0] == '<') {
            continue;
        }
        this->data.emplace_back();
        std::stringstream ss = std::stringstream(buff);
        while (ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            if (substr.empty()) {
                continue;
            }
            this->data.back().push_back(std::stoi(substr));
        }
    }
    file.close();
    this->view = view;
    this->storage = storage;
}
int32_t Map::getID(int32_t x, int32_t y) const {
    return this->data[y][x];
}
bool Map::isSolid(int32_t x, int32_t y, bool checkAIBlocks) const {
    int32_t type = this->data[y][x];
    return (type >= 1 and type < 129 and type != 82 or (checkAIBlocks and type == 315));
}
int32_t Map::getWidth() const {
    return (int32_t)this->data[0].size();
}
int32_t Map::getHeight() const {
    return (int32_t)this->data.size();
}
void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto center = this->view->getCenter();
    auto size = this->view->getSize();
    auto rect = sf::FloatRect(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);
    int32_t x1 = std::max(0, (int32_t)rect.left / 32 - 1);
    int32_t y1 = std::max(0, (int32_t)rect.top / 32 - 1);
    int32_t x2 = std::min(this->getWidth(), (int32_t)(rect.left + rect.width) / 32 + 1);
    int32_t y2 = std::min(this->getHeight(), (int32_t)(rect.top + rect.height) / 32 + 1);
    for (int32_t y = y1; y < y2; y = y + 1) {
        for (int32_t x = x1; x < x2; x = x + 1) {
            int32_t type = this->data[y][x];
            if (type == 0) {
                continue;
            }
            sf::Sprite sprite;
            sprite.setPosition((float)x * 32, (float)y * 32);
            if (type >= 1 and type < 129) {
                type = type - 1;
                sprite.setTexture(*this->storage->getTexture("tileset1"));
            }
            else if (type >= 129 and type < 289) {
                type = type - 129;
                sprite.setTexture(*this->storage->getTexture("tileset2"));
            }
            else if (type >= 289 and type < 307) {
                type = type - 289;
                sprite.setTexture(*this->storage->getTexture("tileset3"));
            }
            else if (type >= 307 and type < 313) {
                type = type - 307;
                sprite.setTexture(*this->storage->getTexture("tileset4"));
            }
            else if (type >= 313) {
                // Это спец-символы для обозначения существ - пропускаем.
                continue;
            }
            int32_t w = (int32_t)sprite.getTexture()->getSize().x / 32;
            sprite.setTextureRect(sf::IntRect(type % w * 32, type / w * 32, 32, 32));
            target.draw(sprite, states);
        }
    }
}