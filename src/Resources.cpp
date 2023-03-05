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


#include "Resources.hpp"


Resources::Resources() {
    this->setFood(0);
    this->setWood(0);
    this->setStone(0);
    this->setIron(0);
    this->setGold(0);
}
Resources::Resources(float food, float wood, float stone, float iron, float gold) {
    this->setFood(food);
    this->setWood(wood);
    this->setStone(stone);
    this->setIron(iron);
    this->setGold(gold);
}
Resources operator+(Resources l, Resources r) {
    return {l.getFood() + r.getFood(), l.getWood() + r.getWood(), l.getStone() + r.getStone(), l.getIron() + r.getIron(), l.getGold() + r.getGold()};
}
Resources operator-(Resources l, Resources r) {
    return l + (-1 * r);
}
Resources operator*(Resources l, float r) {
    return {l.getFood() * r, l.getWood() * r, l.getStone() * r, l.getIron() * r, l.getGold() * r};
}
Resources operator*(float l, Resources r) {
    return r * l;
}
bool operator>(Resources l, Resources r) {
    return (l.getFood() > r.getFood() and l.getWood() > r.getWood() and l.getStone() > r.getStone() and l.getIron() > r.getIron() and l.getGold() > r.getGold());
}
bool operator>=(Resources l, Resources r) {
    return (l.getFood() >= r.getFood() and l.getWood() >= r.getWood() and l.getStone() >= r.getStone() and l.getIron() >= r.getIron() and l.getGold() >= r.getGold());
}
bool operator<(Resources l, Resources r) {
    return !(l >= r);
}
bool operator<=(Resources l, Resources r) {
    return !(l > r);
}
void Resources::setFood(float foodNew) {
    this->food = foodNew;
}
void Resources::setWood(float woodNew) {
    this->wood = woodNew;
}
void Resources::setStone(float stoneNew) {
    this->stone = stoneNew;
}
void Resources::setIron(float ironNew) {
    this->iron = ironNew;
}
void Resources::setGold(float goldNew) {
    this->gold = goldNew;
}
float Resources::getFood() const {
    return this->food;
}
float Resources::getWood() const {
    return this->wood;
}
float Resources::getStone() const {
    return this->stone;
}
float Resources::getIron() const {
    return this->iron;
}
float Resources::getGold() const {
    return this->gold;
}