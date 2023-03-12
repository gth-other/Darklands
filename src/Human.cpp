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


#include "Human.hpp"


Human::Human() = default;
Human::Human(float x, float y, Player *player, Camera *camera, SoundQueue *soundQueue, Storage *storage) : Unit(player), GameObject(camera, soundQueue, storage) {
    this->x = x;
    this->y = y;

    this->targetX = this->x;
    this->targetY = this->y;

    this->_alive = true;
}
void Human::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!this->camera->contain(this->x, this->y, 32, 32)) {
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(this->getTexture());
    sprite.setTextureRect(this->getTextureRect());
    sprite.setPosition(this->x - this->camera->getX(), this->y - this->camera->getY());

    sf::Color playerColor = this->player->getColor();
    if (playerColor.r > playerColor.g and playerColor.r > playerColor.b) {
        playerColor.r = 200;
        playerColor.g = 180 - 50 * this->selected();
        playerColor.b = 180 - 50 * this->selected();
    }
    else if (playerColor.g > playerColor.r and playerColor.g > playerColor.b) {
        playerColor.r = 225 - 50 * this->selected();
        playerColor.g = 255;
        playerColor.b = 225 - 50 * this->selected();
    }
    else {
        playerColor.r = 150 - 50 * this->selected();
        playerColor.g = 150 - 50 * this->selected();
        playerColor.b = 255;
    }
    sprite.setColor(playerColor);

    target.draw(sprite, states);
}
void Human::setTarget(float newTargetX, float newTargetY) {
    this->targetX = newTargetX;
    this->targetY = newTargetY;
}
void Human::setTarget(int32_t newTargetCX, int32_t newTargetCY) {
    this->setTarget(64 * (float)newTargetCX + 16, 64 * (float)newTargetCY + 16);
}
void Human::kill() {
    this->_alive = false;
    this->unselect();
    this->deathAnimationTimer.restart();
}
bool Human::targetReached() const {
    bool dxZero = std::abs(this->x - this->targetX) < 16;
    bool dyZero = std::abs(this->y - this->targetY) < 16;

    return (dxZero and dyZero);
}
bool Human::alive() const {
    return this->_alive;
}
std::string Human::calcMovementDirection() const {
    double dstX = std::abs(this->getX() - this->targetX);
    double dstY = std::abs(this->getY() - this->targetY);
    double dst = std::sqrt(std::pow(dstX, 2) + std::pow(dstY, 2));

    double sin = dstX / dst;
    double degree = std::asin(sin) * 180 / M_PI;

    if (degree <= 30) {
        if (this->targetY < this->getY()) return "N";
        return "S";
    }
    else if (degree <= 60) {
        std::string result;
        if (this->targetY < this->getY()) result.append("N");
        else result.append("S");
        if (this->targetX < this->getX()) result.append("W");
        else result.append("E");
        return result;
    }
    else {
        if (this->targetX < this->getX()) return "W";
        return "E";
    }
}
float Human::getX() const {
    return this->x;
}
float Human::getY() const {
    return this->y;
}
void Human::setX(float newX) {
    this->x = newX;
}
void Human::setY(float newY) {
    this->y = newY;
}
void Human::updateMoving() {
    float t = (float) this->movementTimer.getElapsedTime().asMilliseconds() / 1000;
    this->movementTimer.restart();

    float vx, vy;
    std::tie(vx, vy) = this->calcSpeed();

    this->x = this->x + vx * t;
    this->y = this->y + vy * t;
}
void Human::updateDefenseBuildings(std::vector<DefenseBuilding*> &defenseBuildings) {
    for (auto &db : defenseBuildings) {
        if (db->alive() and db->getPlayerPtr() != this->getPlayerPtr() and db->readyToShoot() and db->cover(this->x + 16, this->y + 16)) {
            db->shoot();
            this->kill();
            break;
        }
    }
}
std::pair<float, float> Human::calcSpeed() const {
    if (this->targetReached()) {
        return std::make_pair(0, 0);
    }

    float dstX = this->x - this->targetX;
    float dstY = this->y - this->targetY;

    auto vy = (float)std::sqrt(std::pow(dstY * this->getSpeed(), 2) / (std::pow(dstY, 2) + std::pow(dstX, 2)));
    auto vx = (float)std::sqrt(std::pow(this->getSpeed(), 2) - std::pow(vy, 2));

    if (dstX > 0) vx = -vx;
    if (dstY > 0) vy = -vy;

    return std::make_pair(vx, vy);
}