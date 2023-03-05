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


#include <vector>
#include <random>
#include <ctime>
#include "Plant.hpp"
#include "Tree.hpp"
#include "Mountain.hpp"
#include "RedMountain.hpp"
#include "LandscapeConf.hpp"


#pragma once


class LandscapeGenerator {
public:
    LandscapeGenerator();
    LandscapeGenerator(Storage *storage, Camera *camera, SoundQueue *soundQueue, LandscapeConf conf, int32_t seed);

    [[nodiscard]] std::vector<ResourcePoint*> generate() const;
    [[nodiscard]] int32_t getSeed() const;

    static int32_t generatePseudoRandomSeed();
private:
    Storage *storage;
    Camera *camera;
    SoundQueue *soundQueue;

    int32_t seed;
    LandscapeConf conf;

    template<class Type> void addGroup(int32_t n, std::pair<int32_t, int32_t> size, int32_t subspecN, bool saveSubspec, std::mt19937 &mersenne, std::vector<std::vector<bool>> &engaged, std::vector<ResourcePoint*> &result) const;
};