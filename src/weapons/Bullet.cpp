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


#include "Bullet.hpp"


Bullet::Bullet() = default;
Bullet::Bullet(sf::FloatRect rect, float v, float alpha, float g) {
    this->rect = rect;
    this->v.x = v * std::cos(alpha * M_PIf / 180);
    this->v.y = -std::abs(v * std::sin(alpha * M_PIf / 180));
    this->g = g;
    this->exist = true;
    this->noSound = false;
}
void Bullet::update(const Map *map, const Player *player, float artificialTime) {
    float fullTime = this->timer.getElapsedTime().asSeconds() + artificialTime;
    this->timer.restart();

    for (float i = 0; i < fullTime; i = i + 1.f / 30.f) {
        float dt = std::min(1.f / 30.f, fullTime - i);

        this->v.y = this->v.y + dt * this->g;
        this->rect.left = this->rect.left + dt * this->v.x;
        this->collisionX(map, player);
        this->rect.top = this->rect.top + dt * this->v.y;
        this->collisionY(map, player);
    }
}
bool Bullet::isExist() const {
    return this->exist;
}
sf::FloatRect Bullet::getRect() const {
    return {this->rect.left, this->rect.top, this->rect.width, this->rect.height};
}
void Bullet::remove(const Player *player) {
    this->exist = false;
    if (this->noSound) {
        return;
    }
    SoundQueue::get()->push(SoundStorage::get()->get("ground"),
                            std::abs(player->getCenterX() - this->rect.left),
                            std::abs(player->getCenterY() - this->rect.top));
}
sf::Vector2f Bullet::getFinalCenterPosition(const Map *map, const Player *player) const {
    sf::Vector2f result;
    Bullet copy = (*this);
    copy.noSound = true;
    for (; ;) {
        result = {copy.rect.left + copy.rect.width / 2, copy.rect.top + copy.rect.height / 2};
        copy.update(map, player, 1.f / 60);
        if (!copy.exist) {
            return result;
        }
    }
}
void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    float hyp = std::sqrt(this->v.x * this->v.x + this->v.y * this->v.y);
    float sin = this->v.y / hyp;
    float alpha;
    if (this->v.x > 0) {
        alpha = std::asin(sin) * 180 / M_PIf + 90;
    }
    else {
        alpha = -std::asin(sin) * 180 / M_PIf - 90;
    }

    sf::Sprite sprite;
    sprite.setPosition(this->rect.left, this->rect.top);
    sprite.setTexture(*TextureStorage::get()->get("bullet"));
    sprite.setTextureRect(sf::IntRect(((int32_t)this->animationClock.getElapsedTime().asMilliseconds() / 50) % 4 * 14, 0, 14, 22));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(this->rect.width / 14, this->rect.height / 22);
    sprite.setRotation(alpha);
    target.draw(sprite, states);
}
void Bullet::collisionX(const Map *map, const Player *player) {
    for (int32_t y = (int32_t)rect.top / 32; y <= (int32_t)(rect.top + rect.height) / 32; y = y + 1) {
        for (int32_t x = (int32_t)rect.left / 32; x <= (int32_t)(rect.left + rect.width) / 32; x = x + 1) {
            if (this->getRect().intersects(sf::FloatRect(32 * (float)x, 32 * (float)y, 32, 32))) {
                if (x < 0 or y < 0 or x >= map->getWidth() or y >= map->getHeight()) {
                    this->exist = false;
                    return;
                }
                if (map->isSolid(x, y, false)) {
                    this->remove(player);
                    return;
                }
            }
        }
    }
}
void Bullet::collisionY(const Map *map, const Player *player) {
    for (int32_t y = (int32_t)rect.top / 32; y <= (int32_t)(rect.top + rect.height) / 32; y = y + 1) {
        for (int32_t x = (int32_t)rect.left / 32; x <= (int32_t)(rect.left + rect.width) / 32; x = x + 1) {
            if (this->getRect().intersects(sf::FloatRect(32 * (float)x, 32 * (float)y, 32, 32))) {
                if (x < 0 or y < 0 or x >= map->getWidth() or y >= map->getHeight()) {
                    this->exist = false;
                    return;
                }
                if (map->isSolid(x, y, false)) {
                    this->remove(player);
                    return;
                }
            }
        }
    }
}