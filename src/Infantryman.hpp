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


#include "Warrior.hpp"


#pragma once


class Infantryman : public Warrior {
public:
    Infantryman();
    Infantryman(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    [[nodiscard]] Resources getCost() const override;
    [[nodiscard]] std::string getDescription() const override;
private:
    [[nodiscard]] const sf::SoundBuffer& getSelectSoundBuffer() const override;
    [[nodiscard]] const sf::Texture& getTexture() const override;
    [[nodiscard]] virtual float getDefense() const override;
    [[nodiscard]] virtual float getBuildingAttack() const override;
    [[nodiscard]] virtual float getWarriorAttack() const override;
    [[nodiscard]] virtual float getAttackRadius() const override;
    [[nodiscard]] virtual int32_t getAttackDelay() const override;
    [[nodiscard]] float getSpeed() const override;
    [[nodiscard]] float getBaseCapacity() const override;
};