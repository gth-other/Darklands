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


#include "OldVampire.hpp"


OldVampire::OldVampire() = default;
OldVampire::OldVampire(sf::Vector2f position, Player *player, Storage *storage, SoundQueue *soundQueue) : Patroller(position, player, storage, soundQueue) {
    this->radius = 0;
}
void OldVampire::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Creature::draw(target, states);

    sf::CircleShape circle;
    circle.setFillColor(sf::Color(150, 0, 0, 63));
    circle.setOutlineColor(sf::Color(100, 0, 0, 255));
    circle.setOutlineThickness(2);
    circle.setPointCount(360);
    circle.setRadius(this->radius);
    circle.setPosition(this->getCenterX() - this->radius, this->getCenterY() - this->radius);
    target.draw(circle, states);
}
void OldVampire::update(const Map *map) {
    float dt = this->increaseTimer.getElapsedTime().asSeconds();
    this->increaseTimer.restart();

    if (this->delayTimer.getElapsedTime().asSeconds() >= DELAY) {
        this->radius = this->radius + INCREASE_SPEED * dt;
        if (this->radius >= MAXIMAL_RADIUS) {
            this->radius = 0;
            this->delayTimer.restart();
        }

        if (this->getPlayer()->isAlive()) {
            sf::FloatRect circle;
            circle.left = this->getCenterX() - this->radius;
            circle.top = this->getCenterY() - this->radius;
            circle.width = 2 * this->radius;
            circle.height = 2 * this->radius;
            if (circle.intersects(this->getPlayer()->getCompressedRect())) {
                this->getPlayer()->kill("darkMagick");
            }
        }
    }

    this->Patroller::update(map);
}
std::string OldVampire::getMurderSoundName() const {
    return "bite";
}
int32_t OldVampire::getID() const {
    return 319;
}
bool OldVampire::isBoss() const {
    return false;
}
float OldVampire::getMaximalMoveSpeed() const {
    return 32 * 7;
}
float OldVampire::getMoveAcceleration() const {
    return 32 * 7 * 4;
}
float OldVampire::getJumpSpeed() const {
    return 750;
}
float OldVampire::getG() const {
    return 750 * 3;
}
std::string OldVampire::getTextureName() const {
    return "oldVampire";
}
int32_t OldVampire::getMSPerFrame() const {
    return 75;
}