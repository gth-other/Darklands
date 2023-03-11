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
#include "WaitingScreen.hpp"
#include "Menu.hpp"
#include "Game.hpp"


int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    PathManager pm = {"../data"};
    Storage storage = {pm};
    SoundQueue soundQueue;
    sf::RenderWindow window = {sf::VideoMode::getDesktopMode(), "Darklands", sf::Style::Fullscreen, settings};
    LoadingScreen loadingScreen;
    WaitingScreen waitingScreen;
    Menu menu;
    Game game;

    storage.addFont("main", "fonts/bitterProMedium.ttf");
    storage.addTexture("logotype", "images/logotype.png");
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);
    window.setIcon(128, 128, storage.getTexture("logotype").copyToImage().getPixelsPtr());

    loadingScreen = {&storage, &soundQueue, &window};
    if (loadingScreen.open() == Screen::Status::Exit) return 0;

    for (std::string s: {"fort", "smelter", "windmill", "wall", "house", "sawmill", "quarry", "tower", "obelisk", "caravan", "academy"}) {
        for (sf::Color c: {sf::Color(0, 0, 120), sf::Color(0, 60, 0)}) {
            storage.addTexture(s, "images/buildings/" + s + ".png", c);
        }
    }
    for (std::string s: {"cursor", "food", "hammer", "iron", "human", "infantryman", "banner", "archer", "hammerButton", "humanButton", "wood", "stone", "gold", "goBack"}) {
        storage.addTexture(s, "images/icons/" + s + ".png");
    }
    for (std::pair<std::string, int32_t> p: {std::make_pair("plant", 14), std::make_pair("mountain", 7), std::make_pair("redMountain", 7), std::make_pair("tree", 5)}) {
        for (int32_t i = 0; i < p.second; i = i + 1) {
            storage.addTexture(p.first + std::to_string(i), "images/resourcePoints/" + p.first + "s/" + std::to_string(i + 1) + ".png");
        }
    }
    for (int32_t i = 0; i < 10; i = i + 1) {
        storage.addMusic("game" + std::to_string(i), "music/game/" + std::to_string(i + 1) + ".ogg");
    }
    for (std::string s: {"intro", "menu"}) {
        storage.addMusic(s, "music/" + s + ".ogg");
    }
    for (std::string s: {"glasses", "click", "leaves", "steam", "stone", "sword", "archery", "saw", "wind", "thunder", "book"}) {
        storage.addSoundBuffer(s, "sounds/" + s + ".ogg");
    }
    for (std::string s0: {"infantryman", "archer"}) {
        for (std::string s1: {"N", "S", "W", "E", "NW", "NE", "SW", "SE"}) {
            storage.addTexture(s0 + "Attack" + s1, "images/warriors/" + s0 + "/attack/" + s1 + ".png");
            storage.addTexture(s0 + "Die" + s1, "images/warriors/" + s0 + "/die/" + s1 + ".png");
            storage.addTexture(s0 + "Rest" + s1, "images/warriors/" + s0 + "/rest/" + s1 + ".png");
            storage.addTexture(s0 + "Walk" + s1, "images/warriors/" + s0 + "/walk/" + s1 + ".png");
        }
    }

    waitingScreen = {&storage, &soundQueue, &window};
    if (waitingScreen.open() == Screen::Status::Exit) return 0;

    menu = {&storage, &soundQueue, &window};
    if (menu.open() == Screen::Status::Exit) return 0;

    game = {&storage, &soundQueue, &window};
    if (game.open() == Screen::Status::Exit) return 0;

    return 0;
}