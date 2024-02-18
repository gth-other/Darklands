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


#include "../SoundQueue.hpp"
#include "../Map.hpp"


#pragma once


class Creature : public sf::Drawable {
public:
    Creature();
    Creature(sf::Vector2f position);

    void update(uint8_t flag, const Map *map);
    [[nodiscard]] float getCenterX() const;
    [[nodiscard]] float getCenterY() const;
    [[nodiscard]] sf::FloatRect getRect() const;
    [[nodiscard]] sf::FloatRect getCompressedRect() const;
    [[nodiscard]] bool isAlive() const;
    virtual void kill(const std::string &reason);
    [[nodiscard]] sf::Vector2f getV() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    [[nodiscard]] virtual std::string getMurderSoundName() const = 0;
    [[nodiscard]] virtual int32_t getID() const = 0;

    struct Flags {
        static constexpr uint8_t Left = 0b1;
        static constexpr uint8_t Right = 0b10;
        static constexpr uint8_t Jump = 0b100;
    };
protected:
    [[nodiscard]] bool isRight() const;
    void invertDirection();
    void setPosition(sf::Vector2f newPosition);
    [[nodiscard]] virtual float getMaximalMoveSpeed() const = 0;
    [[nodiscard]] virtual float getMoveAcceleration() const = 0;
    [[nodiscard]] virtual float getJumpSpeed() const = 0;
    [[nodiscard]] virtual float getG() const = 0;
    [[nodiscard]] virtual std::string getTextureName() const = 0;
    [[nodiscard]] virtual int32_t getMSPerFrame() const = 0;
    [[nodiscard]] virtual bool isAI() const = 0;
private:
    sf::Vector2f position;
    sf::Vector2f v;
    bool alive;
    bool onGround;
    bool right;
    sf::Clock animationClock;
    sf::Clock movementTimer;

    void collisionX(const Map *map);
    void collisionY(const Map *map);
};