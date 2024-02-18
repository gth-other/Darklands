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


#include <list>
#include "../creatures/Player.hpp"
#include "Bullet.hpp"
#include "../SoundQueue.hpp"


#pragma once


class Weapon {
public:
    Weapon();
    virtual ~Weapon();
    Weapon(sf::Vector2f position);

    void update(std::list<Bullet> &bullets, const Map *map, const Player *player);
protected:
    [[nodiscard]] float getPositionX() const;
    [[nodiscard]] virtual bool impossibleToShoot(const Player *player) const;
    [[nodiscard]] virtual float getMinimalLength() const = 0;
    [[nodiscard]] virtual float getMaximalLength() const = 0;
    [[nodiscard]] virtual int32_t getShotsInRow() const = 0;
    [[nodiscard]] virtual float getShortDelay() const = 0;
    [[nodiscard]] virtual float getLongDelay() const = 0;
    [[nodiscard]] virtual sf::Vector2f getBulletSize() const = 0;
    [[nodiscard]] virtual float getBulletG() const = 0;
    [[nodiscard]] virtual float getAlpha(const Player *player) const = 0;
private:
    sf::Vector2f position;
    int32_t shots;
    sf::Clock timer;

    void restartTimer();
    void updateShotsCtr();
    [[nodiscard]] float getMaxVAbs(float alpha) const;
    [[nodiscard]] float getBestVAbs(float alpha, float maxVAbs, const Map *map, const Player *player) const;
    void addBullet(float alpha, float bestVAbs, std::list<Bullet> &bullets) const;
    void playSound(const Player *player) const;
};