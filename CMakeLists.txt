cmake_minimum_required(VERSION 3.16)
project(DungeonSurvival VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar SFML 3
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio Network)

add_executable(DungeonSurvival
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/HUD.cpp
)

target_include_directories(DungeonSurvival PRIVATE include)

target_link_libraries(DungeonSurvival PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio 
    SFML::Network
)