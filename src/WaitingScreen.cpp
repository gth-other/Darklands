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


#include "WaitingScreen.hpp"


WaitingScreen::WaitingScreen() = default;
WaitingScreen::WaitingScreen(Storage *storage, SoundQueue *soundQueue, sf::RenderWindow *window) : Screen(storage, soundQueue, window) {
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

    this->pressAnyKey.setString(L"Нажмите на любую клавишу для продолжения");
    this->pressAnyKey.setFont(this->storage->getFont("main"));
    this->pressAnyKey.setCharacterSize(24);
    this->pressAnyKey.setFillColor({255, 255, 255, 255});
    this->pressAnyKey.setOutlineColor({0, 0, 0, 255});
    this->pressAnyKey.setOutlineThickness(1);
    this->pressAnyKey.setPosition((this->dw - this->pressAnyKey.getLocalBounds().width) / 2, this->dh - this->pressAnyKey.getLocalBounds().height - 10);

    this->logotype.setTexture(this->storage->getTexture("plant13"));
    this->logotype.setPosition((this->dw - 128) / 2, this->pressAnyKey.getPosition().y - 128);
    this->updateLogotypeTexture();
}
int32_t WaitingScreen::open() {
    this->soundQueue->push(this->storage->getSoundBuffer("click"));
    this->storage->getMusic("intro").play();
    this->storage->getMusic("intro").setVolume(Screen::MusicVolume);
    this->storage->getMusic("intro").setLoop(true);

    sf::Event event{};

    for (; ;) {
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)) {
                this->storage->getMusic("intro").stop();
                return Screen::Status::Exit;
            }
            if (event.type == sf::Event::KeyPressed) {
                this->storage->getMusic("intro").stop();
                return Screen::Status::Continue;
            }
        }

        this->window->clear({20, 20, 20, 255});

        this->window->draw(this->title);
        this->window->draw(this->copyright);
        this->window->draw(this->pressAnyKey);
        this->window->draw(this->logotype);

        this->window->display();

        this->updateLogotypeTexture();
    }
}
void WaitingScreen::updateLogotypeTexture() {
    int32_t animation = this->animationClock.getElapsedTime().asMilliseconds() / (1000 / 30) % 30;
    this->logotype.setTextureRect({128 * animation, 0, 128, 128});
}