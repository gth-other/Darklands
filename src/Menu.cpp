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


#include "Menu.hpp"


Menu::Menu() = default;
Menu::Menu(Storage *storage, SoundQueue *soundQueue, sf::RenderWindow *window) : Screen(storage, soundQueue, window) {
    this->newGameRect.setSize(sf::Vector2f(400, 64));
    this->newGameRect.setOutlineThickness(2);
    this->newGameRect.setFillColor({15, 15, 15, 255});
    this->newGameRect.setOutlineColor({0, 0, 0, 255});
    this->newGameRect.setPosition(10, 10);

    this->newGameText.setFont(this->storage->getFont("main"));
    this->newGameText.setString(L"Новая игра");
    this->newGameText.setCharacterSize(24);
    this->newGameText.setOutlineThickness(1);
    this->newGameText.setFillColor({255, 255, 255, 255});
    this->newGameText.setOutlineColor({0, 0, 0, 255});
    this->newGameText.setPosition(10 + (this->newGameRect.getLocalBounds().width - this->newGameText.getLocalBounds().width) / 2, 10 + (this->newGameRect.getLocalBounds().height - this->newGameText.getLocalBounds().height) / 2);

    this->title.setFont(this->storage->getFont("main"));
    this->title.setString("Darklands");
    this->title.setCharacterSize(40);
    this->title.setOutlineThickness(2);
    this->title.setFillColor({255, 255, 255, 255});
    this->title.setOutlineColor({0, 0, 0, 255});
    this->title.setPosition(this->dw - this->title.getLocalBounds().width - 10, 10);

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

    this->logotype.setTexture(this->storage->getTexture("plant13"));
    this->updateLogotypeTexture();
    this->logotype.setPosition(0, this->dh - this->logotype.getLocalBounds().height);

    this->cursor = {this->storage};
}
int32_t Menu::open() {
    this->soundQueue->push(this->storage->getSoundBuffer("click"));
    this->storage->getMusic("menu").play();
    this->storage->getMusic("menu").setLoop(true);
    this->storage->getMusic("menu").setVolume(Screen::MusicVolume);

    sf::Event event{};

    for (; ;) {
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)) {
                this->storage->getMusic("menu").stop();
                return Screen::Status::Exit;
            }
            else if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left) {
                if (this->cursor.on(this->newGameRect)) {
                    this->storage->getMusic("menu").stop();
                    return Screen::Status::Continue;
                }
            }
        }

        this->window->clear({20, 20, 20, 255});

        this->window->draw(this->newGameRect);
        this->window->draw(this->newGameText);
        this->window->draw(this->title);
        this->window->draw(this->copyright);
        this->window->draw(this->logotype);
        this->window->draw(this->cursor);

        this->window->display();

        this->updateLogotypeTexture();
    }
}
void Menu::updateLogotypeTexture() {
    int32_t animation = this->animationClock.getElapsedTime().asMilliseconds() / (1000 / 30) % 30;
    this->logotype.setTextureRect({128 * animation, 0, 128, 128});
}