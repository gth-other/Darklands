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


#include "Storage.hpp"


Storage *Storage::singletone = nullptr;


void Storage::addTexture(const std::string& name, const std::string& path) {
    this->textures[name].loadFromFile(std::string(ROOT) + "/" + path);
}
void Storage::addFont(const std::string& name, const std::string& path) {
    this->fonts[name].loadFromFile(std::string(ROOT) + "/" + path);
}
void Storage::addSoundBuffer(const std::string& name, const std::string& path) {
    this->soundbuffers[name].loadFromFile(std::string(ROOT) + "/" + path);
}
void Storage::addMusic(const std::string& name, const std::string& path) {
    this->music[name].openFromFile(std::string(ROOT) + "/" + path);
}
void Storage::addTexts(const std::vector<std::string> &names, const std::string &path) {
    std::ifstream file(std::string(ROOT) + "/" + path);
    if (!file.is_open()) {
        std::cerr << "Invalid file" << std::endl;
        return;
    }
    std::string current;
    int32_t index = 0;
    for (; ;) {
        std::string buff;
        std::getline(file, buff);
        if (buff == "[sep]" or buff == "[end]") {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wCurrent = converter.from_bytes(current);
            this->texts[names[index]] = wCurrent;
            current = "";
            index = index + 1;
            if (buff == "[end]") {
                break;
            }
        }
        else {
            current = current + buff + '\n';
        }
    }
    file.close();
}
sf::Texture *Storage::getTexture(const std::string& name) {
    return &this->textures[name];
}
sf::Font *Storage::getFont(const std::string& name) {
    return &this->fonts[name];
}
sf::SoundBuffer *Storage::getSoundBuffer(const std::string& name) {
    return &this->soundbuffers[name];
}
sf::Music *Storage::getMusic(const std::string& name) {
    return &this->music[name];
}
sf::String *Storage::getText(const std::string &name) {
    return &this->texts[name];
}