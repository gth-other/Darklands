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


#include "Game.hpp"


Game::Game() {
    this->initWindow();
    this->initPlayerView();
    this->loadData();
    this->createSun();
    this->createBlackBooks();
    this->createEndingMsgs();
    this->createLicenseTitle();
}
void Game::start() {
    for (int32_t i = getCurrentLevel(); i <= LEVELS_NUMBER; i = i + 1) {
        setCurrentLevel(i);
        if (this->startLevel("levels/" + std::to_string(i) + ".tmx", i == LEVELS_NUMBER) == Game::Flag::EXIT) {
            break;
        }
    }
}
void Game::initWindow() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    this->window.create(sf::VideoMode::getDesktopMode(), "Darklands", sf::Style::Fullscreen, settings);
    this->window.setVerticalSyncEnabled(true);
    this->window.setFramerateLimit(60);
    this->window.setMouseCursorVisible(false);
}
void Game::initPlayerView() {
    this->playerView = sf::View(sf::FloatRect(0,
                                              0,
                                              (float)this->window.getSize().x,
                                              (float)this->window.getSize().y));
}
void Game::loadData() {
    TextureStorage::get()->add("playerBase", "images/creatures/player/base.png");
    TextureStorage::get()->add("playerRun", "images/creatures/player/run.png");
    TextureStorage::get()->add("vampireBase", "images/creatures/vampire/base.png");
    TextureStorage::get()->add("vampireRun", "images/creatures/vampire/run.png");
    TextureStorage::get()->add("spiderBase", "images/creatures/spider/base.png");
    TextureStorage::get()->add("spiderRun", "images/creatures/spider/run.png");
    TextureStorage::get()->add("soulBase", "images/creatures/soul/base.png");
    TextureStorage::get()->add("soulRun", "images/creatures/soul/run.png");
    TextureStorage::get()->add("oldVampireBase", "images/creatures/oldVampire/base.png");
    TextureStorage::get()->add("oldVampireRun", "images/creatures/oldVampire/run.png");
    TextureStorage::get()->add("lordBase", "images/creatures/lord/base.png");
    TextureStorage::get()->add("lordRun", "images/creatures/lord/run.png");
    TextureStorage::get()->add("bullet", "images/bullet.png");
    TextureStorage::get()->add("tileset1", "images/tilesets/1.png");
    TextureStorage::get()->add("tileset2", "images/tilesets/2.png");
    TextureStorage::get()->add("tileset3", "images/tilesets/3.png");
    TextureStorage::get()->add("tileset4", "images/tilesets/4.png");
    TextureStorage::get()->add("sun", "images/sun.png");
    TextureStorage::get()->add("background", "images/background.png");
    TextureStorage::get()->add("observingSpheres", "images/blackBooks/observingSpheres.png");
    TextureStorage::get()->add("abandonedLives", "images/blackBooks/abandonedLives.png");
    FontStorage::get()->add("font1", "fonts/1.ttf");
    SoundStorage::get()->add("bite", "sounds/bite.ogg");
    SoundStorage::get()->add("blackBook", "sounds/blackBook.ogg");
    SoundStorage::get()->add("soul", "sounds/soul.ogg");
    SoundStorage::get()->add("ground", "sounds/ground.ogg");
    SoundStorage::get()->add("sword", "sounds/sword.ogg");
    SoundStorage::get()->add("fire", "sounds/fire.ogg");
    SoundStorage::get()->add("cannonBall", "sounds/cannonBall.ogg");
    SoundStorage::get()->add("darkMagick", "sounds/darkMagick.ogg");
    for (int32_t i = 0; i < Playlist::SOUNDTRACKS_N; i = i + 1) {
        MusicStorage::get()->add("music" + std::to_string(i + 1), "music/" + std::to_string(i + 1) + ".ogg");
    }
    TextStorage::get()->add({"death", "levelFinished", "gameFinished", "license"}, "locales.txt");
}
void Game::createSun() {
    this->sun.setTexture(*TextureStorage::get()->get("sun"));
    this->sun.setPosition((float)this->window.getSize().x - this->sun.getLocalBounds().width - 50, 50);
}
void Game::createBlackBooks() {
    this->observingSpheres.setTexture(*TextureStorage::get()->get("observingSpheres"));
    this->observingSpheres.setPosition(10, 20);

    this->abandonedLives.setTexture(*TextureStorage::get()->get("abandonedLives"));
    this->abandonedLives.setPosition(this->observingSpheres.getPosition().x + this->observingSpheres.getLocalBounds().width + 5, this->observingSpheres.getPosition().y);
}
void Game::createEndingMsgs() {
    this->defeatRect.setSize(sf::Vector2f((float)this->window.getSize().x, (float)this->window.getSize().y));
    this->defeatRect.setFillColor(sf::Color(0, 0, 0, 200));

    this->defeatMessage.setFillColor(sf::Color(200, 0, 0));
    this->defeatMessage.setOutlineColor(sf::Color::Black);
    this->defeatMessage.setOutlineThickness(2);
    this->defeatMessage.setFont(*FontStorage::get()->get("font1"));
    this->defeatMessage.setString(*TextStorage::get()->get("death"));
    this->defeatMessage.setCharacterSize(40);
    this->defeatMessage.setPosition(((float)this->window.getSize().x - this->defeatMessage.getLocalBounds().width) / 2, ((float)this->window.getSize().y - this->defeatMessage.getLocalBounds().height) / 2);

    this->finishRect = this->defeatRect;

    this->finishMessageDefault = this->defeatMessage;
    this->finishMessageDefault.setString(*TextStorage::get()->get("levelFinished"));
    this->finishMessageDefault.setPosition(((float)this->window.getSize().x - this->finishMessageDefault.getLocalBounds().width) / 2, ((float)this->window.getSize().y - this->finishMessageDefault.getLocalBounds().height) / 2);

    this->finishMessageLast.setFillColor(this->finishMessageDefault.getFillColor());
    this->finishMessageLast.setOutlineColor(this->finishMessageDefault.getOutlineColor());
    this->finishMessageLast.setOutlineThickness(1);
    this->finishMessageLast.setFont(*this->finishMessageDefault.getFont());
    this->finishMessageLast.setCharacterSize(18);
    this->finishMessageLast.setString(*TextStorage::get()->get("gameFinished"));
    this->finishMessageLast.setPosition(((float)this->window.getSize().x - this->finishMessageLast.getLocalBounds().width) / 2, ((float)this->window.getSize().y - this->finishMessageLast.getLocalBounds().height) / 2);
}
void Game::createLicenseTitle() {
    this->license.setFillColor(this->finishMessageLast.getFillColor());
    this->license.setFont(*this->finishMessageDefault.getFont());
    this->license.setCharacterSize(8);
    this->license.setString(*TextStorage::get()->get("license"));
    this->license.setPosition(0, 0);
}
void Game::updatePhysics(bool lastLevel) {
    this->player.update(this->player.isAlive() * !this->finish(lastLevel) * (
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) * Player::Flags::Left |
            sf::Keyboard::isKeyPressed(sf::Keyboard::D) * Player::Flags::Right |
            sf::Keyboard::isKeyPressed(sf::Keyboard::W) * Player::Flags::Jump), &this->map
    );
    for (auto &weapon : this->weapons) {
        weapon->update(bullets, &map, &player);
    }
    for (auto &enemy : this->enemies) {
        if (enemy->isAlive()) {
            enemy->update(&this->map, &this->player);
        }
    }
    for (auto &bullet : this->bullets) {
        if (bullet.isExist()) {
            bullet.update(&map, &player);
            if (this->player.isAlive() and bullet.getRect().intersects(this->player.getCompressedRect())) {
                this->player.kill("cannonBall");
            }
        }
    }
}
void Game::displayEverything(bool lastLevel) {
    this->playerView.setCenter(std::min(32 * (float)this->map.getWidth() - (float)this->window.getSize().x / 2, std::max((float)this->window.getSize().x / 2, this->player.getCenterX())), std::min(32 * (float)this->map.getHeight() - (float)this->window.getSize().y / 2, std::max((float)this->window.getSize().y / 2, this->player.getCenterY())));
    this->window.clear(sf::Color(3, 3, 3));
    this->window.setView(this->window.getDefaultView());
    this->window.draw(sun);
    int32_t i = -(int32_t)(this->playerView.getCenter().x / 3);
    do {
        sf::Sprite sprite;
        sprite.setTexture(*TextureStorage::get()->get("background"));
        float scale = ((float)this->window.getSize().y - this->sun.getPosition().y - this->sun.getLocalBounds().height) / (float)TextureStorage::get()->get("background")->getSize().y;
        sprite.setScale(scale, scale);
        sprite.setPosition((float)i, this->sun.getPosition().y + this->sun.getLocalBounds().height);
        i = i + (int32_t)((float)sprite.getTexture()->getSize().x * scale);
        this->window.draw(sprite);
    }
    while (i < (int32_t)this->window.getSize().x);
    this->window.setView(this->playerView);
    this->window.draw(this->map);
    this->window.draw(this->player);
    for (auto &bullet : this->bullets) {
        if (bullet.isExist()) {
            this->window.draw(bullet);
        }
    }
    for (auto &enemy : this->enemies) {
        if (enemy->isAlive()) {
            this->window.draw(*enemy);
        }
    }
    this->window.setView(this->window.getDefaultView());
    if (!this->player.wasObservingSpheresUsed()) {
        this->window.draw(this->observingSpheres);
    }
    if (!this->player.wasAbandonedLivesUsed()) {
        this->window.draw(this->abandonedLives);
    }
    if (this->finish(lastLevel)) {
        this->player.kill("");
        this->window.draw(this->finishRect);
        if (lastLevel) {
            this->window.draw(this->finishMessageLast);
        }
        else {
            this->window.draw(this->finishMessageDefault);
        }
    }
    else if (!this->player.isAlive()) {
        this->window.draw(this->defeatRect);
        this->window.draw(this->defeatMessage);
    }
    this->window.draw(this->license);
    this->window.display();
}
int32_t Game::getCurrentLevel() {
    std::ifstream file;
    file.open(std::string(ROOT) + "/appdata/conf.dl");
    if (file.is_open()) {
        std::string buff;
        std::getline(file, buff);
        return std::stoi(buff);
    }
    return 1;
}
void Game::setCurrentLevel(int32_t level) {
    if (!std::filesystem::exists(std::string(ROOT) + "/appdata")) {
        std::filesystem::create_directory(std::string(ROOT) + "/appdata");
    }
    std::ofstream file;
    file.open(std::string(ROOT) + "/appdata/conf.dl");
    file << std::to_string(level);
    file.close();
}
bool Game::finish(bool lastLevel) const {
    if (lastLevel) {
        for (auto &enemy : this->enemies) {
            if (enemy->isAlive() and enemy->isBoss()) {
                return false;
            }
        }
        return true;
    }
    return (this->player.getCenterX() > this->finishX);
}
uint8_t Game::startLevel(const std::string &path, bool lastLevel) {
    SoundQueue::get()->clear();
    Playlist::get()->restartMusic();

    this->map = Map(std::string(ROOT) + "/" + path, &this->playerView);

    this->weapons.clear();
    this->bullets.clear();
    this->enemies.clear();
    std::vector<sf::Vector2f> lordResPositions;
    for (int32_t y = 0; y < this->map.getHeight(); y = y + 1) {
        for (int32_t x = 0; x < this->map.getWidth(); x = x + 1) {
            int32_t id = this->map.getID(x, y);
            auto position = sf::Vector2f(32 * (float)x, 32 * (float)y);
            if (id == Cannon().getLeftMuzzleID()) this->weapons.push_back(std::make_unique<Cannon>(position, false));
            else if (id == Cannon().getRightMuzzleID()) this->weapons.push_back(std::make_unique<Cannon>(position, true));
            else if (id == Mortar().getMuzzleID()) this->weapons.push_back(std::make_unique<Mortar>(position));
            else if (id == Player().getID()) this->player = Player(position);
            else if (id == Vampire().getID()) this->enemies.push_back(std::make_unique<Vampire>(position));
            else if (id == 316) finishX = 32 * (float)x;
            else if (id == Spider().getID()) this->enemies.push_back(std::make_unique<Spider>(position));
            else if (id == Soul().getID()) this->enemies.push_back(std::make_unique<Soul>(position));
            else if (id == OldVampire().getID()) this->enemies.push_back(std::make_unique<OldVampire>(position));
            else if (id == Lord().getID()) this->enemies.push_back(std::make_unique<Lord>(position, &lordResPositions, &this->enemies));
            else if (id == 321) lordResPositions.push_back(position);
        }
    }

    for (; ;) {
        while (this->window.pollEvent(event)) {
            if ((event.type == sf::Event::Closed) or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)) {
                return Flag::EXIT;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (this->finish(lastLevel)) {
                    if (event.key.code == sf::Keyboard::Space or event.key.code == sf::Keyboard::Enter) {
                        return Flag::NEXT;
                    }
                }
                else {
                    if (this->player.isAlive()) {
                        if (event.key.code == sf::Keyboard::Num1 and !this->player.wasObservingSpheresUsed()) {
                            this->player.useObservingSpheres();
                        }
                        else if (event.key.code == sf::Keyboard::Num2 and !this->player.wasAbandonedLivesUsed()) {
                            this->player.useAbandonedLives();
                        }
                    }
                    else {
                        if (event.key.code == sf::Keyboard::Space or event.key.code == sf::Keyboard::Enter) {
                            return this->startLevel(path, lastLevel);
                        }
                    }
                }
            }
        }

        this->updatePhysics(lastLevel);
        this->displayEverything(lastLevel);
        Playlist::get()->update();
    }
}