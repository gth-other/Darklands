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


#include "Player.hpp"


Player::Player() = default;
Player::Player(sf::Vector2f position, Storage *storage, SoundQueue *soundQueue, Map *map) : Creature(position, storage, soundQueue, map) {
    this->observingSpheresUsed = false;
    this->abandonedLivesUsed = false;
}
bool Player::wasObservingSpheresUsed() const {
    return this->observingSpheresUsed;
}
void Player::useObservingSpheres() {
    this->observingSpheresUsed = true;
    this->observingSpheresClock.restart();
    this->getSoundQueue()->push(this->getStorage()->getSoundBuffer("blackBook"), 0, 0);
}
bool Player::isObservingSpheres() const {
    return (this->wasObservingSpheresUsed() and this->observingSpheresClock.getElapsedTime().asSeconds() < Player::OBSERVING_SPHERES_LENGTH);
}
bool Player::wasAbandonedLivesUsed() const {
    return this->abandonedLivesUsed;
}
void Player::useAbandonedLives() {
    this->abandonedLivesUsed = true;
    this->abandonedLivesClock.restart();
    this->getSoundQueue()->push(this->getStorage()->getSoundBuffer("blackBook"), 0, 0);
}
bool Player::isAbandonedLives() const {
    return (this->wasAbandonedLivesUsed() and this->abandonedLivesClock.getElapsedTime().asSeconds() < Player::ABANDONED_LIVES_LENGTH);
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    this->Creature::draw(target, states);

    sf::Sprite blackBook;
    blackBook.setScale(0.5, 0.5);
    if (this->isObservingSpheres()) {
        blackBook.setTexture(*this->getStorage()->getTexture("observingSpheres"));
    }
    else if (this->isAbandonedLives()) {
        blackBook.setTexture(*this->getStorage()->getTexture("abandonedLives"));
    }
    blackBook.setPosition(this->getRect().left, this->getRect().top);
    target.draw(blackBook, states);
}
std::string Player::getMurderSoundName() const {
    return "sword";
}
float Player::getMaximalMoveSpeed() const {
    return 32 * 10;
}
float Player::getMoveAcceleration() const {
    return 32 * 10 * 4;
}
float Player::getJumpSpeed() const {
    return 750;
}
float Player::getG() const {
    return 750 * 3;
}
std::string Player::getTextureName() const {
    return "player";
}
int32_t Player::getMSPerFrame() const {
    return 75;
}
bool Player::isAI() const {
    return false;
}