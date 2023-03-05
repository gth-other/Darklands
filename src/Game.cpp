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


#include "Game.hpp"


Game::Game() = default;
Game::Game(Storage *storage, SoundQueue *soundQueue, sf::RenderWindow *window) : Screen(storage, soundQueue, window) {
    Resources start = {500, 500, 500, 500, 0};
    this->conf = {60, 33, 6, 2, 2, 2, 2, 67, 33, std::make_pair(10, 20), std::make_pair(1, 4)};
    this->camera = new Camera(0, 0, this->dw, this->dh, this->conf.cw, this->conf.ch);
    this->human = new Player(sf::Color(0, 0, 255), start, this->dw, this->storage);
    this->computer = new Player(sf::Color(0, 127, 0), start, this->dw, this->storage);

    LandscapeGenerator generator = {this->storage, this->camera, this->soundQueue, this->conf, LandscapeGenerator::generatePseudoRandomSeed()};
    std::vector<ResourcePoint*> generatedResourcePoints = generator.generate();
    for (const auto& rp : generatedResourcePoints) this->push(rp);

    this->initUI();
    this->initPlayersUnits();
}
int32_t Game::open() {
    this->soundQueue->push(this->storage->getSoundBuffer("click"));
    sf::Event event{};

    for (; ;) {
        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)) {
                this->storage->getMusic("game" + std::to_string(soundtrackNumber)).stop();
                return Screen::Status::Exit;
            }
            if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::F10) this->fps.invertVisibility();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    if (this->cursor.on(this->buildingListButton)) {
                        this->buildingListButtonClick();
                    }
                    else if (this->cursor.on(this->warriorsListButton)) {
                        this->warriorsListButtonClick();
                    }
                    else if (this->showBuildingList) {
                        if (this->buildingList.clicked(0) and this->human->canBuy(this->buildingList.getCost(0))) this->buyBuildingButtonClick<Windmill>();
                        else if (this->buildingList.clicked(1) and this->human->canBuy(this->buildingList.getCost(1))) this->buyBuildingButtonClick<Sawmill>();
                        else if (this->buildingList.clicked(2) and this->human->canBuy(this->buildingList.getCost(2))) this->buyBuildingButtonClick<Quarry>();
                        else if (this->buildingList.clicked(3) and this->human->canBuy(this->buildingList.getCost(3))) this->buyBuildingButtonClick<Smelter>();
                        else if (this->buildingList.clicked(4) and this->human->canBuy(this->buildingList.getCost(4))) this->buyBuildingButtonClick<House>();
                        else if (this->buildingList.clicked(5) and this->human->canBuy(this->buildingList.getCost(5))) this->buyBuildingButtonClick<Caravan>();
                        else if (this->buildingList.clicked(6) and this->human->canBuy(this->buildingList.getCost(6))) this->buyBuildingButtonClick<Academy>();
                        else if (this->buildingList.clicked(7) and this->human->canBuy(this->buildingList.getCost(7))) this->buyBuildingButtonClick<Wall>();
                        else if (this->buildingList.clicked(8) and this->human->canBuy(this->buildingList.getCost(8))) this->buyBuildingButtonClick<Tower>();
                        else if (this->buildingList.clicked(9) and this->human->canBuy(this->buildingList.getCost(9))) this->buyBuildingButtonClick<Obelisk>();
                        else if (this->buildingList.clicked(10) and this->human->canBuy(this->buildingList.getCost(10))) this->buyBuildingButtonClick<Fort>();
                        else if (this->buildingList.clicked(11)) {
                            this->showBuildingList = false;
                            this->soundQueue->push(this->storage->getSoundBuffer("click"));
                        }
                    }
                    else if (this->showWarriorsList) {
                        if (this->warriorsList.clicked(0) and this->human->getHumanNumber() + this->warriorsLayout.size() <= this->human->getHumanLimit() and this->human->canBuy(this->warriorsList.getCost(0))) this->buyWarriorsButtonClick<Infantryman>();
                        else if (this->warriorsList.clicked(1) and this->human->getHumanNumber() + this->warriorsLayout.size() <= this->human->getHumanLimit() and this->human->canBuy(this->warriorsList.getCost(1))) this->buyWarriorsButtonClick<Archer>();
                        else if (this->warriorsList.clicked(2)) {
                            this->showWarriorsList = false;
                            this->soundQueue->push(this->storage->getSoundBuffer("click"));
                        }
                    }
                    else if (this->tradingListVisible()) {
                        for (int32_t i = 0; i < 8; i = i + 1) {
                            if (this->tradingList.clicked(i) and this->human->canBuy(this->tradingList.getCost(i))) {
                                this->makeTrade(this->tradingList.getCost(i));
                            }
                        }
                        if (this->tradingList.clicked(8)) {
                            this->soundQueue->push(this->storage->getSoundBuffer("click"));
                            this->unselectCaravans();
                        }
                    }
                    else if (this->scienceListVisible()) {
                        if (this->scienceList.clicked(0)) {
                            this->soundQueue->push(this->storage->getSoundBuffer("click"));
                            this->unselectAcademies();
                        }
                    }
                    else if (this->buildingLayout != nullptr and this->possibleToPutBuilding()) {
                        this->addBuildingFromLayout();
                    }
                    else if (this->warriorsLayout[0] != nullptr and this->possibleToPutWarriors()) {
                        this->addWarriorsFromLayout();
                    }
                    else if (!this->showBuildingList and !this->showWarriorsList and !this->tradingListVisible() and !this->scienceListVisible() and buildingLayout == nullptr and warriorsLayout[0] == nullptr) {
                        this->updateStationarySelection();
                        this->unselectWarriors();
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Button::Right) {
                    if (!this->showBuildingList and !this->showWarriorsList and !this->tradingListVisible() and !this->scienceListVisible() and buildingLayout == nullptr and warriorsLayout[0] == nullptr) {
                        this->sendSelectedWarriors();
                    }
                }
            }
        }

        this->drawEverything();

        this->updateBuildings();
        this->updateWarriors();
        this->updatePlayers();
        this->updateBuildingLayout();
        this->updateWarriorsLayout();
        this->updateSelectionWindow();
        this->updateCamera();

        this->updateSoundtrack();

        this->fps.update();
    }
}
void Game::initUI() {
    this->fps = {false, this->dw, this->storage};
    this->cursor = {this->storage, this->camera};
    this->soundtrackNumber = (int32_t)(time(nullptr) % INT32_MAX) % 10;
    this->banner = {this->storage, this->soundQueue, this->camera};

    this->buildingLayout = nullptr;
    for (auto& rl : this->warriorsLayout) rl = nullptr;

    this->selectionWindow.setOutlineThickness(2);
    this->selectionWindow.setFillColor({0, 0, 0, 127});
    this->selectionWindow.setOutlineColor({0, 0, 0, 255});

    this->buildingListButton.setTexture(this->storage->getTexture("hammerButton"));
    this->buildingListButton.setPosition(this->dw - this->buildingListButton.getLocalBounds().width - 10, this->dh - this->buildingListButton.getLocalBounds().height - 10);
    this->showBuildingList = false;
    this->buildingList = {10, (int32_t)this->dh - 12 * 74, (int32_t)this->dw - 20, 64, 10, this->human, this->storage};
    this->buildingList.addGood(this->storage->getTexture("windmill", this->human->getColor()), Windmill().getDescription(), Windmill().getCost());
    this->buildingList.addGood(this->storage->getTexture("sawmill", this->human->getColor()), Sawmill().getDescription(), Sawmill().getCost());
    this->buildingList.addGood(this->storage->getTexture("quarry", this->human->getColor()), Quarry().getDescription(), Quarry().getCost());
    this->buildingList.addGood(this->storage->getTexture("smelter", this->human->getColor()), Smelter().getDescription(), Smelter().getCost());
    this->buildingList.addGood(this->storage->getTexture("house", this->human->getColor()), House().getDescription(), House().getCost());
    this->buildingList.addGood(this->storage->getTexture("caravan", this->human->getColor()), Caravan().getDescription(), Caravan().getCost());
    this->buildingList.addGood(this->storage->getTexture("academy", this->human->getColor()), Academy().getDescription(), Academy().getCost());
    this->buildingList.addGood(this->storage->getTexture("wall", this->human->getColor()), Wall().getDescription(), Wall().getCost());
    this->buildingList.addGood(this->storage->getTexture("tower", this->human->getColor()), Tower().getDescription(), Tower().getCost());
    this->buildingList.addGood(this->storage->getTexture("obelisk", this->human->getColor()), Obelisk().getDescription(), Obelisk().getCost());
    this->buildingList.addGood(this->storage->getTexture("fort", this->human->getColor()), Fort().getDescription(), Fort().getCost());
    this->buildingList.addGood(this->storage->getTexture("goBack"), "Вернуться назад.", Resources());

    this->warriorsListButton.setTexture(this->storage->getTexture("humanButton"));
    this->warriorsListButton.setPosition(this->buildingListButton.getPosition().x - this->buildingListButton.getLocalBounds().width - 10, this->buildingListButton.getPosition().y);
    this->showWarriorsList = false;
    this->warriorsList = {10, (int32_t)this->dh - 3 * 74, (int32_t)this->dw - 20, 64, 10, this->human, this->storage};
    this->warriorsList.addGood(this->storage->getTexture("infantryman"), Infantryman().getDescription(), (float)this->warriorsLayout.size() * Infantryman().getCost(), (int32_t)this->warriorsLayout.size());
    this->warriorsList.addGood(this->storage->getTexture("archer"), Archer().getDescription(), (float)this->warriorsLayout.size() * Archer().getCost(), (int32_t)this->warriorsLayout.size());
    this->warriorsList.addGood(this->storage->getTexture("goBack"), "Вернуться назад.", Resources());

    this->tradingList = {10, (int32_t)this->dh - 9 * 74, (int32_t)this->dw - 20, 64, 10, this->human, this->storage};
    this->tradingList.addGood(this->storage->getTexture("food"), "Сто единиц еды помогут накормить войска.", Resources(-100, 0, 0, 0, 200));
    this->tradingList.addGood(this->storage->getTexture("wood"), "Сто единиц древесины помогут возвести мирные здания.", Resources(0, -100, 0, 0, 200));
    this->tradingList.addGood(this->storage->getTexture("stone"), "Сто единиц камня помогут возвести защитные здания.", Resources(0, 0, -100, 0, 200));
    this->tradingList.addGood(this->storage->getTexture("iron"), "Сто единиц железа помогут снарядить войска.", Resources(0, 0, 0, -100, 200));
    this->tradingList.addGood(this->storage->getTexture("gold"), "Избыток еды можно обменять на сто золотых.", Resources(200, 0, 0, 0, -100));
    this->tradingList.addGood(this->storage->getTexture("gold"), "Избыток древесины можно обменять на сто золотых.", Resources(0, 200, 0, 0, -100));
    this->tradingList.addGood(this->storage->getTexture("gold"), "Избыток камня можно обменять на сто золотых.", Resources(0, 0, 200, 0, -100));
    this->tradingList.addGood(this->storage->getTexture("gold"), "Избыток железа можно обменять на сто золотых.", Resources(0, 0, 0, 200, -100));
    this->tradingList.addGood(this->storage->getTexture("goBack"), "Вернуться назад.", Resources());

    this->scienceList = {10, (int32_t)this->dh - 1 * 74, (int32_t)this->dw - 20, 64, 10, this->human, this->storage};
    this->scienceList.addGood(this->storage->getTexture("goBack"), "Вернуться назад.", Resources());
}
void Game::initPlayersUnits() {
    this->push(new Fort(5, 5, this->human, this->camera, this->soundQueue, this->storage));
    this->push(new Caravan(4, 5, this->human, this->camera, this->soundQueue, this->storage));

    this->push(new Fort(this->conf.cw - 1 - 5, this->conf.ch - 1 - 5, this->computer, this->camera, this->soundQueue, this->storage));
    this->push(new Caravan(this->conf.cw - 1 - 4, this->conf.ch - 1 - 5, this->computer, this->camera, this->soundQueue, this->storage));
}
template<class Type> void Game::push(Type *a) {
    if (auto *t = dynamic_cast<Academy*>(a)) this->academies.push_back(t);
    if (auto *t = dynamic_cast<Archer*>(a)) this->archers.push_back(t);
    if (auto *t = dynamic_cast<AreaController*>(a)) this->areaControllers.push_back(t);
    if (auto *t = dynamic_cast<Building*>(a)) this->buildings.push_back(t);
    if (auto *t = dynamic_cast<Caravan*>(a)) this->caravans.push_back(t);
    if (auto *t = dynamic_cast<DefenseBuilding*>(a)) this->defenseBuildings.push_back(t);
    if (auto *t = dynamic_cast<Fort*>(a)) this->forts.push_back(t);
    if (auto *t = dynamic_cast<GameObject*>(a)) this->gameObjects.push_back(t);
    if (auto *t = dynamic_cast<House*>(a)) this->houses.push_back(t);
    if (auto *t = dynamic_cast<Infantryman*>(a)) this->infantrymen.push_back(t);
    if (auto *t = dynamic_cast<Mountain*>(a)) this->mountains.push_back(t);
    if (auto *t = dynamic_cast<Obelisk*>(a)) this->obelisks.push_back(t);
    if (auto *t = dynamic_cast<Plant*>(a)) this->plants.push_back(t);
    if (auto *t = dynamic_cast<Quarry*>(a)) this->quarries.push_back(t);
    if (auto *t = dynamic_cast<RedMountain*>(a)) this->redMountains.push_back(t);
    if (auto *t = dynamic_cast<ResourceBuilding*>(a)) this->resourceBuildings.push_back(t);
    if (auto *t = dynamic_cast<ResourcePoint*>(a)) this->resourcePoints.push_back(t);
    if (auto *t = dynamic_cast<Sawmill*>(a)) this->sawmills.push_back(t);
    if (auto *t = dynamic_cast<Smelter*>(a)) this->smelters.push_back(t);
    if (auto *t = dynamic_cast<Stationary*>(a)) this->stationary.push_back(t);
    if (auto *t = dynamic_cast<Tower*>(a)) this->towers.push_back(t);
    if (auto *t = dynamic_cast<Tree*>(a)) this->trees.push_back(t);
    if (auto *t = dynamic_cast<Unit*>(a)) this->units.push_back(t);
    if (auto *t = dynamic_cast<Wall*>(a)) this->walls.push_back(t);
    if (auto *t = dynamic_cast<Warrior*>(a)) this->warriors.push_back(t);
    if (auto *t = dynamic_cast<Windmill*>(a)) this->windmills.push_back(t);
}
void Game::drawEverything() {
    this->window->clear({20, 20, 20, 255});

    for (const auto& w : this->warriors) {
        if (!w->alive()) {
            this->window->draw(*w); // Отображаются мертвые, так как после смерти необходимо отображать труп.
        }
    }
    for (const auto& w : this->warriors) {
        if (w->alive()) {
            this->window->draw(*w);;
        }
    }
    for (const auto& s : this->stationary) {
        if (s->alive()) {
            this->window->draw(*s);
        }
    }

    this->window->draw(this->banner);

    if (!this->showBuildingList and !this->showWarriorsList and !this->tradingListVisible() and !this->scienceListVisible() and this->buildingLayout == nullptr and this->warriorsLayout[0] == nullptr) {
        this->window->draw(this->selectionWindow);
    }

    if (this->showBuildingList) this->window->draw(this->buildingList);
    if (this->showWarriorsList) this->window->draw(this->warriorsList);
    if (this->tradingListVisible()) this->window->draw(this->tradingList);
    if (this->scienceListVisible()) this->window->draw(this->scienceList);

    if (this->buildingLayout != nullptr) this->window->draw(*this->buildingLayout);
    if (this->warriorsLayout[0] != nullptr) {
        for (const auto& rl : this->warriorsLayout) {
            this->window->draw(*rl);
        }
    }

    this->window->draw(this->buildingListButton);
    this->window->draw(this->warriorsListButton);

    this->window->draw(*this->human);

    this->window->draw(this->fps);

    this->window->draw(this->cursor);

    this->window->display();
}
void Game::updateBuildings() {
    for (auto &b : this->buildings) {
        if (b->alive()) {
            b->update();
        }
    }
}
void Game::updateWarriors() {
    for (const auto& w : this->warriors) {
        if (w->alive()) {
            w->update(defenseBuildings, resourceBuildings, resourcePoints);
        }
    }
}
void Game::updatePlayers() {
    this->human->update(
            (int32_t)std::count_if(this->warriors.begin(), this->warriors.end(), [*this](auto h){return h->alive() and h->getPlayerPtr() == this->human;}),
            House::People * (int32_t)std::count_if(this->houses.begin(), this->houses.end(), [*this](auto t){return t->alive() and t->getPlayerPtr() == this->human;})
    );
    this->computer->update(
            (int32_t)std::count_if(this->warriors.begin(), this->warriors.end(), [*this](auto h){return h->alive() and h->getPlayerPtr() == this->computer;}),
            House::People * (int32_t)std::count_if(this->houses.begin(), this->houses.end(), [*this](auto t){return t->alive() and t->getPlayerPtr() == this->computer;})
    );
}
void Game::updateBuildingLayout() {
    auto mouse_position = sf::Mouse::getPosition();

    if (this->buildingLayout != nullptr) {
        this->buildingLayout->setCX(((int32_t)this->camera->getX() + mouse_position.x) / 64);
        this->buildingLayout->setCY(((int32_t)this->camera->getY() + mouse_position.y) / 64);
    }
}
void Game::updateWarriorsLayout() {
    auto mouse_position = sf::Mouse::getPosition();

    if (this->warriorsLayout[0] != nullptr) {
        int32_t x = -3;
        int32_t y = -3;
        for (int32_t i = 0; i < 25; i = i + 1) {
            this->warriorsLayout[i]->setX(std::ceil((this->camera->getX() + (float)mouse_position.x) / 16) * 16 + 16 * (float)x);
            this->warriorsLayout[i]->setY(std::ceil((this->camera->getY() + (float)mouse_position.y) / 16) * 16 + 16 * (float)y);
            this->warriorsLayout[i]->setTarget(this->warriorsLayout[i]->getX(), this->warriorsLayout[i]->getY());
            x = x + 1;
            if (x >= 2) {
                x = -3;
                y = y + 1;
            }
        }
    }
}
void Game::updateSelectionWindow() {
    auto mouse_position = sf::Mouse::getPosition();

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (!this->showBuildingList and !this->showWarriorsList and !this->tradingListVisible() and !this->scienceListVisible() and this->buildingLayout == nullptr and this->warriorsLayout[0] == nullptr) {
            float x0 = std::min(this->selectionWindow.getPosition().x, this->selectionWindow.getPosition().x + this->selectionWindow.getSize().x) + this->camera->getX();
            float y0 = std::min(this->selectionWindow.getPosition().y, this->selectionWindow.getPosition().y + this->selectionWindow.getSize().y) + this->camera->getY();
            float x1 = std::max(this->selectionWindow.getPosition().x, this->selectionWindow.getPosition().x + this->selectionWindow.getSize().x) + this->camera->getX();
            float y1 = std::max(this->selectionWindow.getPosition().y, this->selectionWindow.getPosition().y + this->selectionWindow.getSize().y) + this->camera->getY();

            bool played = false;
            for (const auto& w : this->warriors) {
                if (w->alive() and w->getPlayerPtr() == this->human and w->getX() >= x0 and w->getY() >= y0 and w->getX() < x1 and w->getY() < y1) {
                    w->select(!played);
                    w->stopCollection();
                    played = true;
                }
            }
        }
        this->selectionWindow.setPosition((float)mouse_position.x, (float)mouse_position.y);
    }

    this->selectionWindow.setSize(sf::Vector2f((float)mouse_position.x - this->selectionWindow.getPosition().x, (float)mouse_position.y - this->selectionWindow.getPosition().y));
}
void Game::updateCamera() {
    auto mouse_position = sf::Mouse::getPosition();

    int32_t north_camera = Camera::Direction::North * (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or mouse_position.y < 20);
    int32_t west_camera = Camera::Direction::West * (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or mouse_position.x < 20);
    int32_t south_camera = Camera::Direction::South * (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or mouse_position.y > (int32_t)this->dh - 20);
    int32_t east_camera = Camera::Direction::East * (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or mouse_position.x > (int32_t)this->dw - 20);

    this->camera->move(north_camera | west_camera | south_camera | east_camera);
}
void Game::updateSoundtrack() {
    if (this->storage->getMusic("game" + std::to_string(this->soundtrackNumber)).getStatus() != sf::Music::Status::Playing) {
        this->soundtrackNumber = (this->soundtrackNumber + 1) % 10;
        this->storage->getMusic("game" + std::to_string(this->soundtrackNumber)).play();
        this->storage->getMusic("game" + std::to_string(this->soundtrackNumber)).setVolume(Screen::MusicVolume);
    }
}
bool Game::tradingListVisible() const {
    for (const auto &c : this->caravans) {
        if (c->alive() and c->getPlayerPtr() == this->human and c->selected()) {
            return true;
        }
    }

    return false;
}
void Game::unselectCaravans() {
    for (const auto &c : this->caravans) {
        c->unselect();
    }
}
bool Game::scienceListVisible() const {
    for (const auto &a : this->academies) {
        if (a->alive() and a->getPlayerPtr() == this->human and a->selected()) {
            return true;
        }
    }

    return false;
}
void Game::unselectAcademies() {
    for (const auto &a : this->academies) {
        a->unselect();
    }
}
template<class Type> void Game::buyBuildingButtonClick() {
    this->soundQueue->push(this->storage->getSoundBuffer("click"));
    this->selectForts();
    this->showBuildingList = false;
    this->buildingLayout = new Type(-1, -1, this->human, this->camera, this->soundQueue, this->storage);
    this->buildingLayout->setHP(1);
}
template<class Type> void Game::buyWarriorsButtonClick() {
    this->soundQueue->push(this->storage->getSoundBuffer("click"));
    this->selectForts();
    this->showWarriorsList = false;
    for (auto& rl : this->warriorsLayout) rl = new Type(-32, -32, this->human, this->camera, this->soundQueue, this->storage);
}
void Game::buildingListButtonClick() {
    this->soundQueue->push(this->storage->getSoundBuffer("click"));
    if (this->showBuildingList) this->showBuildingList = false;
    else {
        this->showBuildingList = true;
        this->showWarriorsList = false;
        this->unselectCaravans();
        this->unselectAcademies();
    }
    this->buildingLayout = nullptr;
    for (auto& rl : this->warriorsLayout) rl = nullptr;
    this->unselectEverything();
}
void Game::warriorsListButtonClick() {
    this->soundQueue->push(this->storage->getSoundBuffer("click"));
    if (this->showWarriorsList) this->showWarriorsList = false;
    else {
        this->showBuildingList = false;
        this->showWarriorsList = true;
        this->unselectCaravans();
        this->unselectAcademies();
    }
    this->buildingLayout = nullptr;
    for (auto& rl : this->warriorsLayout) rl = nullptr;
    this->unselectEverything();
}
bool Game::possibleToPutBuilding() const {
    for (const auto& s : this->stationary) {
        if (s->alive() and s->getCX() == this->buildingLayout->getCX() and s->getCY() == this->buildingLayout->getCY()) {
            return false;
        }
    }

    for (const auto& f : this->forts) {
        if (f->getPlayerPtr() == this->human and f->cover(this->buildingLayout->getCX(), this->buildingLayout->getCY())) {
            return true;
        }
    }
    return false;
}
bool Game::possibleToPutWarriors() const {
    std::array<bool, 25> coverage{};
    for (const auto& f : this->forts) {
        if (f->getPlayerPtr() == this->human) {
            for (int32_t i = 0; i < 25; i = i + 1) {
                if (f->cover(this->warriorsLayout[i]->getX() + 16, this->warriorsLayout[i]->getY() + 16)) {
                    coverage[i] = true;
                }
            }
        }
    }

    for (int32_t i = 0; i < 25; i = i + 1) {
        if (!coverage[i]) {
            return false;
        }
    }
    return true;
}
void Game::addBuildingFromLayout() {
    this->buildingLayout->select(true);
    this->buildingLayout->refreshRepairTimer();
    this->push(this->buildingLayout);
    this->human->buy(this->buildingLayout->getCost());
    this->buildingLayout = nullptr;
    this->unselectEverything();
}
void Game::addWarriorsFromLayout() {
    this->warriorsLayout[0]->select(true);
    for (const auto& rl : this->warriorsLayout) this->push(rl);
    this->human->buy((float)this->warriorsLayout.size() * this->warriorsLayout[0]->getCost());
    for (auto& rl : this->warriorsLayout) rl = nullptr;
    this->unselectEverything();
}
void Game::makeTrade(Resources cost) {
    this->soundQueue->push(this->storage->getSoundBuffer("glasses"));
    this->unselectCaravans();
    this->human->buy(cost);
}
void Game::updateStationarySelection() {
    for (auto& s : this->stationary) {
        if (auto* u = dynamic_cast<Unit*>(s)) if (u->getPlayerPtr() != this->human) continue;
        if (s->alive() and this->cursor.on(s->getCX(), s->getCY())) {
            if (s->selected()) s->unselect(true);
            else s->select(true);
        }
        else s->unselect();
    }
}
void Game::unselectWarriors() {
    for (const auto& w : this->warriors) {
        w->unselect();
    }
}
void Game::sendSelectedWarriors() {
    auto mouse_position = sf::Mouse::getPosition();

    float targetX = (float)(this->camera->getX()) + (float)(mouse_position.x);
    float targetY = (float)(this->camera->getY()) + (float)(mouse_position.y);

    int32_t targetCX = (int32_t)targetX / 64;
    int32_t targetCY = (int32_t)targetY / 64;

    for (auto& w : this->warriors) {
        if (!w->selected()) continue;

        w->setTarget(targetX, targetY);
        for (auto &p : this->plants) if (p->getCX() == targetCX and p->getCY() == targetCY) w->startFoodCollection(targetCX, targetCY);
        for (auto &t : this->trees) if (t->getCX() == targetCX and t->getCY() == targetCY) w->startWoodCollection(targetCX, targetCY);
        for (auto &m : this->mountains) if (m->getCX() == targetCX and m->getCY() == targetCY) w->startStoneCollection(targetCX, targetCY);
        for (auto &rm : this->redMountains) if (rm->getCX() == targetCX and rm->getCY() == targetCY) w->startIronCollection(targetCX, targetCY);
    }

    this->banner.setPosition(this->camera->getX() + (float)sf::Mouse::getPosition().x, this->camera->getY() + (float)sf::Mouse::getPosition().y, true);
}
void Game::selectForts() {
    for (auto& f : this->forts) {
        if (f->alive() and f->getPlayerPtr() == this->human) f->select();
    }
}
void Game::unselectEverything() {
    for (auto& go : this->gameObjects) {
        go->unselect();
    }
}