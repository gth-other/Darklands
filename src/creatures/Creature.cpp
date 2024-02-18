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


#include "Creature.hpp"


Creature::Creature() = default;
Creature::Creature(sf::Vector2f position, Storage *storage, SoundQueue *soundQueue) {
    this->position = position;
    this->alive = true;
    this->onGround = false;
    this->right = true;
    this->storage = storage;
    this->soundQueue = soundQueue;
}
void Creature::update(uint8_t flag, const Map *map) {
    float fullTime = this->movementTimer.getElapsedTime().asSeconds();
    this->movementTimer.restart();

    for (float i = 0; i < fullTime; i = i + 1.f / 30.f) {
        float dt = std::min(1.f / 30.f, fullTime - i);

        if ((flag & Flags::Left) and (flag & Flags::Right)) {
            flag = flag & (~Flags::Left);
            flag = flag & (~Flags::Right);
        }

        if (flag & Flags::Left) {
            this->v.x = std::max(-this->getMaximalMoveSpeed(), this->v.x - dt * this->getMoveAcceleration());
            this->right = false;
        }
        if (flag & Flags::Right) {
            this->v.x = std::min(this->getMaximalMoveSpeed(), this->v.x + dt * this->getMoveAcceleration());
            this->right = true;
        }
        if (!(flag & Flags::Left) and !(flag & Flags::Right)) {
            if (this->v.x > 0) {
                this->v.x = std::max(0.f, this->v.x - dt * this->getMoveAcceleration());
            }
            else if (this->v.x < 0) {
                this->v.x = std::min(0.f, this->v.x + dt * this->getMoveAcceleration());
            }
        }
        if (this->onGround and (flag & Flags::Jump)) {
            this->v.y = -this->getJumpSpeed();
            this->onGround = false;
        }
        if (!this->onGround) {
            this->v.y = this->v.y + dt * this->getG();
        }

        this->position.x = this->position.x + dt * this->v.x;
        this->collisionX(map);
        this->position.y = this->position.y + dt * this->v.y;
        this->collisionY(map);
    }
}
float Creature::getCenterX() const {
    return this->position.x + this->getRect().width / 2;
}
float Creature::getCenterY() const {
    return this->position.y + this->getRect().height / 2;
}
sf::FloatRect Creature::getRect() const {
    return {this->position.x, this->position.y, (float)this->storage->getTexture(this->getTextureName() + "Base")->getSize().x, (float)this->storage->getTexture(this->getTextureName() + "Base")->getSize().y};
}
sf::FloatRect Creature::getCompressedRect() const {
    sf::FloatRect defaultRect = this->getRect();
    return {defaultRect.left + defaultRect.width / 4, defaultRect.top + defaultRect.height / 4, defaultRect.width / 2, defaultRect.height / 2};
}
bool Creature::isAlive() const {
    return this->alive;
}
void Creature::kill(const std::string &reason) {
    this->alive = false;
    if (!reason.empty()) {
        this->getSoundQueue()->push(this->getStorage()->getSoundBuffer(reason), 0, 0);
    }
}
sf::Vector2f Creature::getV() const {
    return this->v;
}
void Creature::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sprite.setPosition(this->position);
    if (this->v.x == 0) {
        sprite.setTexture(*this->storage->getTexture(this->getTextureName() + "Base"));
    }
    else {
        sprite.setTexture(*this->storage->getTexture(this->getTextureName() + "Run"));
        sprite.setTextureRect(sf::IntRect(((int32_t)animationClock.getElapsedTime().asMilliseconds() /
                this->getMSPerFrame()) % ((int32_t)this->storage->getTexture(this->getTextureName() + "Run")->getSize().x / (int32_t)this->getRect().width) * (int32_t)this->getRect().width, 0, (int32_t)this->getRect().width, (int32_t)this->getRect().height));
    }
    if (!this->right) {
        sprite.setScale(-1, 1);
        sprite.setPosition(sprite.getPosition().x + this->getRect().width, sprite.getPosition().y);
    }

    target.draw(sprite, states);
}
bool Creature::isRight() const {
    return this->right;
}
void Creature::invertDirection() {
    this->right = !this->right;
}
void Creature::setPosition(sf::Vector2f newPosition) {
    this->position = newPosition;
    this->onGround = false;
}
Storage *Creature::getStorage() const {
    return this->storage;
}
SoundQueue *Creature::getSoundQueue() {
    return this->soundQueue;
}
void Creature::collisionX(const Map *map) {
    if (this->v.x == 0) {
        return;
    }
    for (int32_t y = (int32_t)this->position.y / 32; y <= (int32_t)(this->position.y + this->getRect().height) / 32; y = y + 1) {
        for (int32_t x = (int32_t)this->position.x / 32; x <= (int32_t)(this->position.x + this->getRect().width) / 32; x = x + 1) {
            if (this->getRect().intersects(sf::FloatRect(32 * (float)x, 32 * (float)y, 32, 32))) {
                if (x < 0 or y < 0 or x >= map->getWidth() or y >= map->getHeight()) {
                    this->kill("");
                    return;
                }
                if (map->isSolid(x, y, this->isAI())) {
                    if (this->v.x > 0) {
                        this->position.x = (float)x * 32 - this->getRect().width;
                    }
                    else {
                        this->position.x = (float)(x + 1) * 32;
                    }
                    this->v.x = 0;
                }
            }
            else if (y == (int32_t)(this->position.y + this->getRect().height) / 32) {
                this->onGround = false;
            }
        }
    }
}
void Creature::collisionY(const Map *map) {
    if (this->v.y == 0) {
        return;
    }
    for (int32_t y = (int32_t)this->position.y / 32; y <= (int32_t)(this->position.y + this->getRect().height) / 32; y = y + 1) {
        for (int32_t x = (int32_t)this->position.x / 32; x <= (int32_t)(this->position.x + this->getRect().width) / 32; x = x + 1) {
            if (this->getRect().intersects(sf::FloatRect(32 * (float)x, 32 * (float)y, 32, 32))) {
                if (x < 0 or y < 0 or x >= map->getWidth() or y >= map->getHeight()) {
                    this->kill("");
                    return;
                }
                if (map->isSolid(x, y, this->isAI())) {
                    if (this->v.y > 0) {
                        this->position.y = (float)y * 32 - this->getRect().height;
                        this->onGround = true;
                    }
                    else {
                        this->position.y = (float)(y + 1) * 32;
                    }
                    this->v.y = 0;
                }
            }
        }
    }
}