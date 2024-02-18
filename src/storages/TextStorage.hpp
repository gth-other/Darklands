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


#include <unordered_map>
#include <cstdint>
#include <string>
#include <vector>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <SFML/System/String.hpp>
#include "Root.hpp"


#pragma once


class TextStorage {
public:
    static TextStorage *get() {
        if (TextStorage::singletone == nullptr) {
            TextStorage::singletone = new TextStorage();
        }
        return TextStorage::singletone;
    }

    void add(const std::vector<std::string>& names, const std::string& path);
    [[nodiscard]] sf::String *get(const std::string& name);
private:
    TextStorage() = default;
    TextStorage(const TextStorage& copy);
    static TextStorage *singletone;

    std::unordered_map<std::string, sf::String> texts;
};