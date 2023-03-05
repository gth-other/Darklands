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


#include "Camera.hpp"
#include "SoundQueue.hpp"
#include "Storage.hpp"


#pragma once


class GameObject : public sf::Drawable {
public:
    GameObject();
    GameObject(Camera *camera, SoundQueue *soundQueue, Storage *storage);

    void select(bool playSound = false);
    void unselect(bool playSound = false);
    [[nodiscard]] bool selected() const;
    [[nodiscard]] virtual bool alive() const = 0;
protected:
    Storage *storage;
    SoundQueue *soundQueue;
    Camera *camera;

    [[nodiscard]] virtual const sf::SoundBuffer& getSelectSoundBuffer() const = 0;
    [[nodiscard]] virtual const sf::Texture& getTexture() const = 0;
    [[nodiscard]] virtual sf::IntRect getTextureRect() const = 0;
private:
    bool _selected;
};