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


#include "Weapon.hpp"


Weapon::Weapon() = default;
Weapon::~Weapon() = default;
Weapon::Weapon(sf::Vector2f position, Storage *storage, SoundQueue *soundQueue, Map *map, Player *player) {
    this->position = position;
    this->shots = 0;
    this->storage = storage;
    this->soundQueue = soundQueue;
    this->map = map;
    this->player = player;
}
void Weapon::update(std::list<Bullet> &bullets) {
    if (this->impossibleToShoot()) {
        return;
    }
    this->restartTimer();
    this->updateShotsCtr();

    float alpha = this->getAlpha();
    float maxVAbs = this->getMaxVAbs(alpha);
    float bestVAbs = this->getBestVAbs(alpha, maxVAbs);

    this->addBullet(alpha, bestVAbs, bullets);
    this->playSound();
}
float Weapon::getPlayerCenterX() const {
    return this->player->getCenterX();
}
float Weapon::getPositionX() const {
    return this->position.x;
}
bool Weapon::impossibleToShoot() const {
    return (!this->player->isAlive() or
        this->player->isObservingSpheres() or
        (this->shots % this->getShotsInRow() == 0 and this->timer.getElapsedTime().asSeconds() < this->getLongDelay()) or
        (this->shots % this->getShotsInRow() != 0 and this->timer.getElapsedTime().asSeconds() < this->getShortDelay()) or
        std::abs(player->getCenterX() - this->position.x) > this->getMaximalLength() or
        std::abs(player->getCenterX() - this->position.x) < this->getMinimalLength());
}
void Weapon::restartTimer() {
    this->timer.restart();
}
void Weapon::updateShotsCtr() {
    this->shots = this->shots + 1;
}
float Weapon::getMaxVAbs(float alpha) const {
    float maxVAbs;
    if (alpha >= 90) {
        maxVAbs = std::sqrt(this->getMaximalLength() * this->getBulletG() / std::sin(2 * (360 - alpha) * M_PIf / 180));
    }
    else {
        maxVAbs = std::sqrt(this->getMaximalLength() * this->getBulletG() / std::sin(2 * alpha * M_PIf / 180));
    }
    return maxVAbs;
}
float Weapon::getBestVAbs(float alpha, float maxVAbs) const {
    int32_t l = 0, r = (int32_t)maxVAbs;
    while (l <= r) {
        int32_t m = (l + r) / 2;
        auto bullet = Bullet(sf::FloatRect(this->position.x, this->position.y, this->getBulletSize().x, this->getBulletSize().y), (float)m, alpha, this->getBulletG(), this->player, this->storage, this->soundQueue, this->map);
        if (bullet.getFinalCenterPosition().x > this->player->getCenterX()) {
            if (alpha > 90) {
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        else {
            if (alpha > 90) {
                r = m - 1;
            }
            else {
                l = m + 1;
            }
        }
    }
    return (float)l;
}
void Weapon::addBullet(float alpha, float bestVAbs, std::list<Bullet> &bullets) const {
    bullets.emplace_back(sf::FloatRect(this->position.x, this->position.y, this->getBulletSize().x, this->getBulletSize().y), bestVAbs, alpha, this->getBulletG(), this->player, this->storage, this->soundQueue, this->map);
}
void Weapon::playSound() const {
    this->soundQueue->push(this->storage->getSoundBuffer("fire"), std::abs(this->position.x - this->player->getCenterX()), std::abs(this->position.y - this->player->getCenterY()));
}