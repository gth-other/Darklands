cmake_minimum_required(VERSION 3.24)
project(Darklands)
set(CMAKE_CXX_STANDARD 20)
add_definitions(-Werror)
add_definitions(-O3)
add_definitions(-flto)
add_executable(Darklands src/main.cpp src/creatures/Player.hpp src/creatures/Player.cpp src/Map.hpp src/Map.cpp src/Playlist.hpp src/Playlist.cpp src/weapons/Bullet.hpp src/weapons/Bullet.cpp src/weapons/Weapon.hpp src/weapons/Weapon.cpp src/SoundQueue.hpp src/SoundQueue.cpp src/weapons/Cannon.hpp src/weapons/Cannon.cpp src/weapons/Mortar.hpp src/weapons/Mortar.cpp src/weapons/SymmetricalWeapon.hpp src/weapons/SymmetricalWeapon.cpp src/weapons/AsymmetricalWeapon.hpp src/weapons/AsymmetricalWeapon.cpp src/creatures/Creature.hpp src/creatures/Creature.cpp src/creatures/Vampire.hpp src/creatures/Vampire.cpp src/creatures/Enemy.hpp src/creatures/Enemy.cpp src/Game.hpp src/Game.cpp src/creatures/Patroller.hpp src/creatures/Patroller.cpp src/creatures/Spider.hpp src/creatures/Spider.cpp src/creatures/Soul.hpp src/creatures/Soul.cpp src/creatures/OldVampire.hpp src/creatures/OldVampire.cpp src/creatures/Lord.hpp src/creatures/Lord.cpp
        src/storages/TextureStorage.hpp
        src/storages/TextureStorage.cpp
        src/storages/SoundStorage.hpp
        src/storages/SoundStorage.cpp
        src/storages/FontStorage.hpp
        src/storages/FontStorage.cpp
        src/storages/MusicStorage.hpp
        src/storages/MusicStorage.cpp
        src/storages/TextStorage.hpp
        src/storages/TextStorage.cpp
        src/storages/Root.hpp)


target_link_libraries(Darklands sfml-system sfml-window sfml-graphics sfml-audio)