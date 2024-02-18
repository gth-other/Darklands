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


#include <memory>
#include <list>
#include "Soul.hpp"


#pragma once


class Lord : public Patroller {
public:
    Lord();
    Lord(sf::Vector2f position, Player *player, Storage *storage, SoundQueue *soundQueue, std::vector<sf::Vector2f> *resPositions, std::list<std::unique_ptr<Enemy>> *enemies);
    void kill(const std::string &reason) override;
    [[nodiscard]] std::string getMurderSoundName() const override;
    [[nodiscard]] int32_t getID() const override;
    [[nodiscard]] bool isBoss() const override;
private:
    int32_t deathCtr;
    std::vector<sf::Vector2f> *resPositions;
    std::list<std::unique_ptr<Enemy>> *enemies;

    static constexpr int32_t MAXIMAL_DEATHS = 10;

    [[nodiscard]] float getMaximalMoveSpeed() const override;
    [[nodiscard]] float getMoveAcceleration() const override;
    [[nodiscard]] float getJumpSpeed() const override;
    [[nodiscard]] float getG() const override;
    [[nodiscard]] std::string getTextureName() const override;
    [[nodiscard]] int32_t getMSPerFrame() const override;
    void teleport();
    void callSouls();
};