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


#include "Plant.hpp"
#include "Tree.hpp"
#include "Mountain.hpp"
#include "RedMountain.hpp"
#include "Windmill.hpp"
#include "Sawmill.hpp"
#include "Quarry.hpp"
#include "Smelter.hpp"
#include "Human.hpp"


#pragma once


class Earner : public Human {
public:
    Earner();
    Earner(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage);

    void startFoodCollection(int32_t cx, int32_t cy);
    void startWoodCollection(int32_t cx, int32_t cy);
    void startStoneCollection(int32_t cx, int32_t cy);
    void startIronCollection(int32_t cx, int32_t cy);
    void stopCollection();
protected:
    float bag;

    [[nodiscard]] float getCapacity() const;
    [[nodiscard]] virtual float getBaseCapacity() const = 0;

    void updateCollection(std::vector<ResourceBuilding*> &rbs, std::vector<ResourcePoint*> &rps);
private:
    bool foodCollectionInProgress;
    bool woodCollectionInProgress;
    bool stoneCollectionInProgress;
    bool ironCollectionInProgress;

    [[nodiscard]] std::pair<int32_t, int32_t> tryToFindBestResourceBuilding(std::vector<ResourceBuilding*> &rbs) const;
    [[nodiscard]] std::pair<int32_t, int32_t> tryToFindBestResourcePoint(std::vector<ResourcePoint*> &rps) const;
    [[nodiscard]] bool correctResourceBuilding(ResourceBuilding *rb) const;
    [[nodiscard]] bool correctResourcePoint(ResourcePoint *rp) const;
};