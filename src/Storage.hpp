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


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>
#include "PathManager.hpp"


#pragma once


class Storage {
public:
    Storage();
    Storage(PathManager pm);

    void addTexture(std::string id, const std::string& shortPath, sf::Color color = sf::Color::Transparent);
    void addFont(const std::string& id, const std::string& shortPath);
    void addSoundBuffer(const std::string& id, const std::string& shortPath);
    void addMusic(const std::string& id, const std::string& shortPath);

    [[nodiscard]] const sf::Texture &getTexture(std::string id, sf::Color color = sf::Color::Transparent) const;
    [[nodiscard]] const sf::Font &getFont(const std::string& id) const;
    [[nodiscard]] const sf::SoundBuffer &getSoundBuffer(const std::string& id) const;
    [[nodiscard]] sf::Music &getMusic(const std::string& id);
private:
    PathManager pm;

    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Music> music;

    static void convert(sf::Image &image, sf::Color newColor);
    static void printError(const std::string& id);
};