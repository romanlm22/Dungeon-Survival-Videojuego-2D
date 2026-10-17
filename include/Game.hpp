#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "HUD.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void startNewGame();
    void startNextWave();

    sf::RenderWindow m_window;
    Player m_player;
    sf::RectangleShape m_arenaBounds;
    std::vector<Enemy> m_enemies;
    HUD m_hud;

    int m_score;
    int m_currentWave;
    int m_gameState; 
    int m_selectedMenuIndex;

    bool m_spacePressedLastFrame;
    bool m_escapePressedLastFrame;
    bool m_enterPressedLastFrame;
    bool m_upPressedLastFrame;
    bool m_downPressedLastFrame;
};