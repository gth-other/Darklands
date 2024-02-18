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


#include "Creature.hpp"


#pragma once


class Player : public Creature {
public:
    Player();
    Player(sf::Vector2f position, Storage *storage, SoundQueue *soundQueue);
    [[nodiscard]] bool wasObservingSpheresUsed() const;
    void useObservingSpheres();
    [[nodiscard]] bool isObservingSpheres() const;
    [[nodiscard]] bool wasAbandonedLivesUsed() const;
    void useAbandonedLives();
    [[nodiscard]] bool isAbandonedLives() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    [[nodiscard]] std::string getMurderSoundName() const override;
    [[nodiscard]] int32_t getID() const override;
private:
    bool observingSpheresUsed;
    sf::Clock observingSpheresClock;
    bool abandonedLivesUsed;
    sf::Clock abandonedLivesClock;

    static constexpr float OBSERVING_SPHERES_LENGTH = 5;
    static constexpr float ABANDONED_LIVES_LENGTH = 5;

    [[nodiscard]] float getMaximalMoveSpeed() const override;
    [[nodiscard]] float getMoveAcceleration() const override;
    [[nodiscard]] float getJumpSpeed() const override;
    [[nodiscard]] float getG() const override;
    [[nodiscard]] std::string getTextureName() const override;
    [[nodiscard]] int32_t getMSPerFrame() const override;
    [[nodiscard]] bool isAI() const override;
};