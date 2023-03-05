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


#include "FPSCounter.hpp"


FPSCounter::FPSCounter() = default;
FPSCounter::FPSCounter(bool visibility, float dw, Storage *storage) {
    this->frames = 0;

    this->visibility = visibility;
    this->dw = dw;

    this->storage = storage;
}
void FPSCounter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (this->visibility) target.draw(this->text, states);
}
void FPSCounter::update() {
    this->frames = this->frames + 1;
    if (this->secondsTimer.getElapsedTime().asSeconds() >= 1) {
        this->text.setString("FPS: " + std::to_string(this->frames));
        this->text.setFont(this->storage->getFont("main"));
        this->text.setCharacterSize(14);
        this->text.setOutlineThickness(1);
        this->text.setFillColor({255, 255, 255, 255});
        this->text.setOutlineColor({0, 0, 0, 255});
        this->text.setPosition(this->dw - this->text.getLocalBounds().width - 10, 10);

        this->frames = 0;
        this->secondsTimer.restart();
    }
}
void FPSCounter::invertVisibility() {
    this->visibility = !this->visibility;
}