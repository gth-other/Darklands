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


#include "SoundQueue.hpp"


SoundQueue::SoundQueue() = default;
void SoundQueue::push(const sf::SoundBuffer &buffer) {
    this->removeOld();

    this->sounds.emplace();
    this->sounds.back().setBuffer(buffer);
    this->sounds.back().play();
}
void SoundQueue::removeOld() {
    while (!this->sounds.empty() and this->sounds.front().getStatus() == sf::Sound::Status::Stopped) {
        this->sounds.pop();
    }
    std::cout << "Debug info: " << this->sounds.size() << " sounds in sound queue" << std::endl;
}