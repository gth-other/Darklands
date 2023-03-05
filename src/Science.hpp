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


#include <cstdint>


#pragma once


class Science {
public:
    Science();

    void conductResearch(uint8_t key);
    [[nodiscard]] bool researched(uint8_t key) const;

    struct Keys {
        static constexpr uint8_t Buildings = 0b1;
        static constexpr uint8_t WarriorsCapacity = 0b10;
        static constexpr uint8_t Walls = 0b100;
        static constexpr uint8_t DefenseBuildings = 0b1000;
    };
private:
    uint8_t data;
};