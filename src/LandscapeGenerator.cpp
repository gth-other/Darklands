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


#include "LandscapeGenerator.hpp"


LandscapeGenerator::LandscapeGenerator() = default;
LandscapeGenerator::LandscapeGenerator(Storage *storage, Camera *camera, SoundQueue *soundQueue, LandscapeConf conf, int32_t seed) {
    this->storage = storage;
    this->camera = camera;
    this->soundQueue = soundQueue;

    this->seed = seed;
    this->conf = conf;
}
std::vector<ResourcePoint*> LandscapeGenerator::generate() const {
    std::vector<std::vector<bool>> engaged(this->conf.cw, std::vector<bool>(this->conf.ch));
    std::mt19937 mersenne(this->seed);
    std::vector<ResourcePoint*> result;

    int32_t square = this->conf.cw * this->conf.ch - 4 * this->conf.engagedCornersSize * this->conf.engagedCornersSize;
    int32_t plantsNumber = square * this->conf.plantsPercent / 100;
    int32_t treesNumber = square * this->conf.treesPercent / 100;
    int32_t mountainsNumber = square * this->conf.mountainsPercent / 100;
    int32_t redMountainsNumber = square * this->conf.redMountainsPercent / 100;

    this->addGroup<Plant>(plantsNumber * this->conf.bigGroupsPercent / 100, this->conf.bigGroupSize, 13, true, mersenne, engaged, result);
    this->addGroup<Plant>(plantsNumber * this->conf.smallGroupsPercent / 100, this->conf.smallGroupSize, 13, true, mersenne, engaged, result);

    this->addGroup<Tree>(treesNumber * this->conf.bigGroupsPercent / 100, this->conf.bigGroupSize, 5, false, mersenne, engaged, result);
    this->addGroup<Tree>(treesNumber * this->conf.smallGroupsPercent / 100, this->conf.smallGroupSize, 5, false, mersenne, engaged, result);

    this->addGroup<Mountain>(mountainsNumber * this->conf.bigGroupsPercent / 100, this->conf.bigGroupSize, 7, false, mersenne, engaged, result);
    this->addGroup<Mountain>(mountainsNumber * this->conf.smallGroupsPercent / 100, this->conf.smallGroupSize, 7, false, mersenne, engaged, result);

    this->addGroup<RedMountain>(redMountainsNumber * this->conf.bigGroupsPercent / 100, this->conf.bigGroupSize, 7, false, mersenne, engaged, result);
    this->addGroup<RedMountain>(redMountainsNumber * this->conf.smallGroupsPercent / 100, this->conf.smallGroupSize, 7, false, mersenne, engaged, result);

    std::cout << "Debug info: seed " << this->getSeed() << std::endl;

    return result;
}
int32_t LandscapeGenerator::getSeed() const {
    return this->seed;
}
int32_t LandscapeGenerator::generatePseudoRandomSeed() {
    return (int32_t)(time(nullptr) % INT32_MAX);
}
template<class Type> void LandscapeGenerator::addGroup(int32_t n, std::pair<int32_t, int32_t> size, int32_t subspecN, bool saveSubspec, std::mt19937 &mersenne, std::vector<std::vector<bool>> &engaged, std::vector<ResourcePoint*> &result) const {
    while (n) {
        uint32_t cx, cy;
        do {
            cx = mersenne() % this->conf.cw;
            cy = mersenne() % this->conf.ch;
        }
        while (engaged[cx][cy] or cx < this->conf.engagedCornersSize or cy < this->conf.engagedCornersSize or cx >= this->conf.cw - this->conf.engagedCornersSize or cy >= this->conf.ch - this->conf.engagedCornersSize);

        uint32_t subspec = mersenne() % subspecN;

        n = n - 1;
        engaged[cx][cy] = true;
        result.push_back(new Type(cx, cy, subspec, this->camera, this->soundQueue, this->storage));

        int32_t groupSize = std::min(n, size.first + (int32_t)mersenne() % (size.second - size.first));
        for (int32_t i = 0; i < groupSize; i = i + 1) {
            std::vector<std::pair<int32_t, int32_t>> possibleDirections;
            if (cx > this->conf.engagedCornersSize and !engaged[cx - 1][cy]) possibleDirections.emplace_back(-1, 0);
            if (cy > this->conf.engagedCornersSize and !engaged[cx][cy - 1]) possibleDirections.emplace_back(0, -1);
            if (cx < this->conf.cw - this->conf.engagedCornersSize - 1 and !engaged[cx + 1][cy]) possibleDirections.emplace_back(1, 0);
            if (cy < this->conf.ch - this->conf.engagedCornersSize - 1 and !engaged[cx][cy + 1]) possibleDirections.emplace_back(0, 1);

            if (possibleDirections.empty()) break;

            uint32_t possibleDirectionN = mersenne() % possibleDirections.size();

            cx = cx + possibleDirections[possibleDirectionN].first;
            cy = cy + possibleDirections[possibleDirectionN].second;

            n = n - 1;
            engaged[cx][cy] = true;
            result.push_back(new Type(cx, cy, saveSubspec * subspec + !saveSubspec * (mersenne() % subspecN), this->camera, this->soundQueue, this->storage));
        }
    }
}