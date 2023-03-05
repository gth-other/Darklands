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


#include "Building.hpp"


#pragma once


class House : public Building {
public:
    House();
    House(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    [[nodiscard]] Resources getCost() const override;
    [[nodiscard]] std::string getDescription() const override;

    static constexpr int32_t People = 25;
private:
    [[nodiscard]] const sf::Texture& getTexture() const override;
    [[nodiscard]] sf::IntRect getTextureRect() const override;
    [[nodiscard]] const sf::SoundBuffer& getSelectSoundBuffer() const override;
    [[nodiscard]] float getMaxHP() const override;
    [[nodiscard]] float getRepairSpeed() const override;
};