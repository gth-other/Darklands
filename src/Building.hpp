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


#include "Stationary.hpp"
#include "Player.hpp"
#include "Unit.hpp"


#pragma once


class Building : public Unit, public Stationary {
public:
    Building();
    Building(int32_t cx, int32_t cy, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    void update();
    void refreshRepairTimer();
protected:
    [[nodiscard]] virtual float getRepairSpeed() const = 0;
private:
    sf::Clock repairTimer;

    void updateRepairing();
};