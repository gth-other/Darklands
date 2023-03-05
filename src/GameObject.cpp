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


#include "GameObject.hpp"


GameObject::GameObject() = default;
GameObject::GameObject(Camera *camera, SoundQueue *soundQueue, Storage *storage) {
    this->_selected = false;
    this->camera = camera;
    this->soundQueue = soundQueue;
    this->storage = storage;
}
void GameObject::select(bool playSound) {
    this->_selected = true;
    if (playSound) this->soundQueue->push(this->getSelectSoundBuffer());
}
void GameObject::unselect(bool playSound) {
    this->_selected = false;
    if (playSound) this->soundQueue->push(this->getSelectSoundBuffer());
}
bool GameObject::selected() const {
    return this->_selected;
}