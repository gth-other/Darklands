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
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    this->window.create(sf::VideoMode::getDesktopMode(), "Darklands", sf::Style::Fullscreen, settings);
    this->window.setVerticalSyncEnabled(true);
    this->window.setFramerateLimit(60);
    this->window.setMouseCursorVisible(false);

    this->playerView = sf::View(sf::FloatRect(0, 0, (float)this->window.getSize().x, (float)this->window.getSize().y));

    Storage::get()->addTexture("playerBase", "images/creatures/player/base.png");
    Storage::get()->addTexture("playerRun", "images/creatures/player/run.png");
    Storage::get()->addTexture("vampireBase", "images/creatures/vampire/base.png");
    Storage::get()->addTexture("vampireRun", "images/creatures/vampire/run.png");
    Storage::get()->addTexture("spiderBase", "images/creatures/spider/base.png");
    Storage::get()->addTexture("spiderRun", "images/creatures/spider/run.png");
    Storage::get()->addTexture("soulBase", "images/creatures/soul/base.png");
    Storage::get()->addTexture("soulRun", "images/creatures/soul/run.png");
    Storage::get()->addTexture("oldVampireBase", "images/creatures/oldVampire/base.png");
    Storage::get()->addTexture("oldVampireRun", "images/creatures/oldVampire/run.png");
    Storage::get()->addTexture("lordBase", "images/creatures/lord/base.png");
    Storage::get()->addTexture("lordRun", "images/creatures/lord/run.png");
    Storage::get()->addTexture("bullet", "images/bullet.png");
    Storage::get()->addTexture("tileset1", "images/tilesets/1.png");
    Storage::get()->addTexture("tileset2", "images/tilesets/2.png");
    Storage::get()->addTexture("tileset3", "images/tilesets/3.png");
    Storage::get()->addTexture("tileset4", "images/tilesets/4.png");
    Storage::get()->addTexture("sun", "images/sun.png");
    Storage::get()->addTexture("background", "images/background.png");
    Storage::get()->addTexture("observingSpheres", "images/blackBooks/observingSpheres.png");
    Storage::get()->addTexture("abandonedLives", "images/blackBooks/abandonedLives.png");
    Storage::get()->addFont("font1", "fonts/1.ttf");
    Storage::get()->addSoundBuffer("bite", "sounds/bite.ogg");
    Storage::get()->addSoundBuffer("blackBook", "sounds/blackBook.ogg");
    Storage::get()->addSoundBuffer("soul", "sounds/soul.ogg");
    Storage::get()->addSoundBuffer("ground", "sounds/ground.ogg");
    Storage::get()->addSoundBuffer("sword", "sounds/sword.ogg");
    Storage::get()->addSoundBuffer("fire", "sounds/fire.ogg");
    Storage::get()->addSoundBuffer("cannonBall", "sounds/cannonBall.ogg");
    Storage::get()->addSoundBuffer("darkMagick", "sounds/darkMagick.ogg");
    for (int32_t i = 0; i < Playlist::SOUNDTRACKS_N; i = i + 1) {
        Storage::get()->addMusic("music" + std::to_string(i + 1), "music/" + std::to_string(i + 1) + ".ogg");
    }

    this->sun.setTexture(*Storage::get()->getTexture("sun"));
    this->sun.setPosition((float)this->window.getSize().x - this->sun.getLocalBounds().width - 50, 50);

    this->observingSpheres.setTexture(*Storage::get()->getTexture("observingSpheres"));
    this->observingSpheres.setPosition(10, 20);

    this->abandonedLives.setTexture(*Storage::get()->getTexture("abandonedLives"));
    this->abandonedLives.setPosition(this->observingSpheres.getPosition().x + this->observingSpheres.getLocalBounds().width + 5, this->observingSpheres.getPosition().y);

    this->defeatRect.setSize(sf::Vector2f((float)this->window.getSize().x, (float)this->window.getSize().y));
    this->defeatRect.setFillColor(sf::Color(0, 0, 0, 200));

    this->defeatMessage.setFillColor(sf::Color(200, 0, 0));
    this->defeatMessage.setOutlineColor(sf::Color::Black);
    this->defeatMessage.setOutlineThickness(2);
    this->defeatMessage.setFont(*Storage::get()->getFont("font1"));
    this->defeatMessage.setString(L"история завершена");
    this->defeatMessage.setCharacterSize(40);
    this->defeatMessage.setPosition(((float)this->window.getSize().x - this->defeatMessage.getLocalBounds().width) / 2, ((float)this->window.getSize().y - this->defeatMessage.getLocalBounds().height) / 2);

    this->finishRect = this->defeatRect;

    this->finishMessageDefault = this->defeatMessage;
    this->finishMessageDefault.setString(L"глава окончена");
    this->finishMessageDefault.setPosition(((float)this->window.getSize().x - this->finishMessageDefault.getLocalBounds().width) / 2, ((float)this->window.getSize().y - this->finishMessageDefault.getLocalBounds().height) / 2);

    this->finishMessageLast.setFillColor(this->finishMessageDefault.getFillColor());
    this->finishMessageLast.setOutlineColor(this->finishMessageDefault.getOutlineColor());
    this->finishMessageLast.setOutlineThickness(1);
    this->finishMessageLast.setFont(*this->finishMessageDefault.getFont());
    this->finishMessageLast.setCharacterSize(18);
    this->finishMessageLast.setString(L"лорд так и не увидел меча, что убил его. он умер мгновенно,\nне успев понять, что мир вернется к прежнему виду.");
    this->finishMessageLast.setPosition(((float)this->window.getSize().x - this->finishMessageLast.getLocalBounds().width) / 2, ((float)this->window.getSize().y - this->finishMessageLast.getLocalBounds().height) / 2);

    this->license.setFillColor(this->finishMessageLast.getFillColor());
    this->license.setFont(*this->finishMessageDefault.getFont());
    this->license.setCharacterSize(8);
    this->license.setString("Darklands. Copyright (C) 2023 gth-other. Darklands is free software: you can redistribute it and/or modify it under the terms of the\nGNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.");
    this->license.setPosition(0, 0);
}
void Game::start() {
    for (int32_t i = Game::getCurrentLevel(); i <= LEVELS_NUMBER; i = i + 1) {
        Game::setCurrentLevel(i);
        if (this->startLevel("levels/" + std::to_string(i) + ".tmx", i == LEVELS_NUMBER) == Game::Flag::EXIT) {
            break;
        }
    }
}
int32_t Game::getCurrentLevel() {
    std::ifstream file;
    file.open(std::string(Storage::ROOT) + "/appdata/conf.dl");
    if (file.is_open()) {
        std::string buff;
        std::getline(file, buff);
        return std::stoi(buff);
    }
    return 1;
}
void Game::setCurrentLevel(int32_t level) {
    if (!std::filesystem::exists(std::string(Storage::ROOT) + "/appdata")) {
        std::filesystem::create_directory(std::string(Storage::ROOT) + "/appdata");
    }
    std::ofstream file;
    file.open(std::string(Storage::ROOT) + "/appdata/conf.dl");
    file << std::to_string(level);
    file.close();
}
uint8_t Game::startLevel(const std::string &path, bool lastLevel) {
    SoundQueue::get()->clear();
    Playlist::get()->restartMusic();

    this->map = Map(std::string(Storage::ROOT) + "/" + path, &this->playerView);

    this->weapons.clear();
    this->bullets.clear();
    this->enemies.clear();
    std::vector<sf::Vector2f> lordResPositions;
    for (int32_t y = 0; y < this->map.getHeight(); y = y + 1) {
        for (int32_t x = 0; x < this->map.getWidth(); x = x + 1) {
            int32_t id = this->map.getID(x, y);
            auto position = sf::Vector2f(32 * (float)x, 32 * (float)y);
            if (id == Cannon().getLeftMuzzleID()) {
                this->weapons.push_back(std::make_unique<Cannon>(position, false));
            }
            else if (id == Cannon().getRightMuzzleID()) {
                this->weapons.push_back(std::make_unique<Cannon>(position, true));
            }
            else if (id == Mortar().getMuzzleID()) {
                this->weapons.push_back(std::make_unique<Mortar>(position));
            }
            else if (id == Player().getID()) {
                this->player = Player(position);
            }
            else if (id == Vampire().getID()) {
                this->enemies.push_back(std::make_unique<Vampire>(position, &this->player));
            }
            else if (id == 316) {
                finishX = 32 * (float)x;
            }
            else if (id == Spider().getID()) {
                this->enemies.push_back(std::make_unique<Spider>(position, &this->player));
            }
            else if (id == Soul().getID()) {
                this->enemies.push_back(std::make_unique<Soul>(position, &this->player));
            }
            else if (id == OldVampire().getID()) {
                this->enemies.push_back(std::make_unique<OldVampire>(position, &this->player));
            }
            else if (id == Lord().getID()) {
                this->enemies.push_back(std::make_unique<Lord>(position, &this->player, &lordResPositions, &this->enemies));
            }
            else if (id == 321) {
                lordResPositions.push_back(position);
            }
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
                enemy->update(&this->map);
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
        Playlist::get()->update();

        this->playerView.setCenter(std::min(32 * (float)this->map.getWidth() - (float)this->window.getSize().x / 2, std::max((float)this->window.getSize().x / 2, this->player.getCenterX())), std::min(32 * (float)this->map.getHeight() - (float)this->window.getSize().y / 2, std::max((float)this->window.getSize().y / 2, this->player.getCenterY())));
        this->window.clear(sf::Color(3, 3, 3));
        this->window.setView(this->window.getDefaultView());
        this->window.draw(sun);
        int32_t i = -(int32_t)(this->playerView.getCenter().x / 3);
        do {
            sf::Sprite sprite;
            sprite.setTexture(*Storage::get()->getTexture("background"));
            float scale = ((float)this->window.getSize().y - this->sun.getPosition().y - this->sun.getLocalBounds().height) / (float)Storage::get()->getTexture("background")->getSize().y;
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