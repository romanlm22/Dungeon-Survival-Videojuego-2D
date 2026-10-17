#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class HUD {
public:
    HUD();

    void update(int health, int score, int wave, int enemiesRemaining);
    void render(sf::RenderWindow& window, int gameState, int selectedMenuIndex);

private:
    sf::Font m_font;
    bool m_fontLoaded;

    sf::Text m_healthText;
    sf::Text m_scoreText;
    sf::Text m_waveText;
    sf::Text m_enemiesText;

    sf::Text m_titleText;
    std::vector<sf::Text> m_menuOptions;
    sf::Text m_pauseText;
    sf::Text m_gameOverText;
    sf::Text m_victoryText;
};