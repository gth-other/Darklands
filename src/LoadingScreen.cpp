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


#include "LoadingScreen.hpp"


LoadingScreen::LoadingScreen() = default;
LoadingScreen::LoadingScreen(Storage *storage, SoundQueue *soundQueue, sf::RenderWindow *window) : Screen(storage, soundQueue, window) {
    this->title.setString("Darklands");
    this->title.setFont(this->storage->getFont("main"));
    this->title.setCharacterSize(40);
    this->title.setFillColor({255, 255, 255, 255});
    this->title.setOutlineColor({0, 0, 0, 255});
    this->title.setOutlineThickness(2);
    this->title.setStyle(sf::Text::Style::Bold);
    this->title.setPosition(10, 10);

    this->copyright.setString(L"(C) 2022 gth-other\n"
                                "\n"
                                "Распространяется на основе\n"
                                "лицензии GNU General Public\n"
                                "License V3.0");
    this->copyright.setFont(this->storage->getFont("main"));
    this->copyright.setCharacterSize(14);
    this->copyright.setFillColor({255, 255, 255, 255});
    this->copyright.setOutlineColor({0, 0, 0, 255});
    this->copyright.setOutlineThickness(1);
    this->copyright.setPosition(this->dw - this->copyright.getLocalBounds().width - 10, this->dh - this->copyright.getLocalBounds().height - 10);

    this->pleaseWait.setString(L"Пожалуйста, подождите...");
    this->pleaseWait.setFont(this->storage->getFont("main"));
    this->pleaseWait.setCharacterSize(24);
    this->pleaseWait.setFillColor({255, 255, 255, 255});
    this->pleaseWait.setOutlineColor({0, 0, 0, 255});
    this->pleaseWait.setOutlineThickness(1);
    this->pleaseWait.setPosition((this->dw - this->pleaseWait.getLocalBounds().width) / 2, this->dh - this->pleaseWait.getLocalBounds().height - 10);

    this->logotype.setTexture(this->storage->getTexture("logotype"));
    this->logotype.setPosition((this->dw - this->logotype.getLocalBounds().width) / 2, this->pleaseWait.getPosition().y - this->logotype.getLocalBounds().height);
}
int32_t LoadingScreen::open() {
    this->window->clear({20, 20, 20, 255});

    this->window->draw(this->title);
    this->window->draw(this->copyright);
    this->window->draw(this->pleaseWait);
    this->window->draw(this->logotype);

    this->window->display();

    return Screen::Status::Continue;
}