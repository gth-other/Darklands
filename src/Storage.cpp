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


#include "Storage.hpp"


Storage::Storage() = default;
Storage::Storage(PathManager pm) {
    this->pm = std::move(pm);
}
void Storage::addTexture(std::string id, const std::string& shortPath, sf::Color color) {
    sf::Image image;
    image.loadFromFile(this->pm.getFullPath(shortPath));
    if (color != sf::Color::Transparent) {
        Storage::convert(image, color);
        id.append(std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b) + std::to_string(color.a));
    }
    this->textures[id].loadFromImage(image);
}
void Storage::addFont(const std::string& id, const std::string& shortPath) {
    this->fonts[id].loadFromFile(this->pm.getFullPath(shortPath));
}
void Storage::addSoundBuffer(const std::string& id, const std::string& shortPath) {
    this->soundBuffers[id].loadFromFile(this->pm.getFullPath(shortPath));
}
void Storage::addMusic(const std::string& id, const std::string& shortPath) {
    this->music[id].openFromFile(this->pm.getFullPath(shortPath));
}
const sf::Texture &Storage::getTexture(std::string id, sf::Color color) const {
    if (color != sf::Color::Transparent) id.append(std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b) + std::to_string(color.a));
    auto it = this->textures.find(id);
    if (it == this->textures.end()) Storage::printError(id);
    return it->second;
}
const sf::Font &Storage::getFont(const std::string& id) const {
    auto it = this->fonts.find(id);
    if (it == this->fonts.end()) Storage::printError(id);
    return it->second;
}
const sf::SoundBuffer &Storage::getSoundBuffer(const std::string& id) const {
    auto it = this->soundBuffers.find(id);
    if (it == this->soundBuffers.end()) Storage::printError(id);
    return it->second;
}
sf::Music &Storage::getMusic(const std::string& id){
    auto it = this->music.find(id);
    if (it == this->music.end()) Storage::printError(id);
    return it->second;
}
void Storage::convert(sf::Image &image, sf::Color newColor) {
    for (uint32_t x = 0; x < image.getSize().x; x = x + 1) {
        for (uint32_t y = 0; y < image.getSize().y; y = y + 1) {
            if (image.getPixel(x, y) == sf::Color(255, 0, 255, 255)) {
                image.setPixel(x, y, newColor);
            }
        }
    }
}
void Storage::printError(const std::string& id) {
    std::cerr << "Could not find '" << id << "'." << std::endl;
    throw -1;
}