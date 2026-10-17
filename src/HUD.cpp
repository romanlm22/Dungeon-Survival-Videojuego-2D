#include "HUD.hpp"

HUD::HUD() 
    : m_fontLoaded(false),
      m_healthText(m_font, "", 18),
      m_scoreText(m_font, "", 18),
      m_waveText(m_font, "", 18),
      m_enemiesText(m_font, "", 18),
      m_titleText(m_font, "DUNGEON SURVIVAL", 40),
      m_pauseText(m_font, "JUEGO EN PAUSA\n\nPresiona ESC para continuar", 30),
      m_gameOverText(m_font, "HAS MUERTO\n\nPresiona ENTER para reiniciar", 36),
      m_victoryText(m_font, "¡VICTORIA!\nHas completado todas las oleadas\n\nPresiona ENTER para reiniciar", 36) {
    
    if (m_font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        m_fontLoaded = true;
    } else if (m_font.openFromFile("assets/fonts/arial.ttf")) {
        m_fontLoaded = true;
    }

    if (m_fontLoaded) {
        m_healthText.setFillColor(sf::Color::Green);
        m_healthText.setPosition(sf::Vector2f(35.f, 10.f));

        m_scoreText.setFillColor(sf::Color::White);
        m_scoreText.setPosition(sf::Vector2f(200.f, 10.f));

        m_waveText.setFillColor(sf::Color::Yellow);
        m_waveText.setPosition(sf::Vector2f(450.f, 10.f));

        m_enemiesText.setFillColor(sf::Color(255, 100, 100));
        m_enemiesText.setPosition(sf::Vector2f(650.f, 10.f));

        m_titleText.setFillColor(sf::Color(220, 180, 50));
        m_titleText.setStyle(sf::Text::Bold);
        m_titleText.setPosition(sf::Vector2f(280.f, 140.f));

        sf::Text opt1(m_font, "> Iniciar Aventura", 24);
        sf::Text opt2(m_font, "> Salir del Juego", 24);
        opt1.setPosition(sf::Vector2f(370.f, 280.f));
        opt2.setPosition(sf::Vector2f(370.f, 330.f));
        m_menuOptions.push_back(opt1);
        m_menuOptions.push_back(opt2);

        m_pauseText.setFillColor(sf::Color::Yellow);
        m_pauseText.setPosition(sf::Vector2f(330.f, 260.f));

        m_gameOverText.setFillColor(sf::Color::Red);
        m_gameOverText.setPosition(sf::Vector2f(310.f, 240.f));

        m_victoryText.setFillColor(sf::Color::Green);
        m_victoryText.setPosition(sf::Vector2f(250.f, 220.f));
    }
}

void HUD::update(int health, int score, int wave, int enemiesRemaining) {
    if (!m_fontLoaded) return;
    m_healthText.setString("Vida: " + std::to_string(health));
    m_scoreText.setString("Puntuacion: " + std::to_string(score));
    m_waveText.setString("Oleada: " + std::to_string(wave) + "/5");
    m_enemiesText.setString("Enemigos: " + std::to_string(enemiesRemaining));
}

void HUD::render(sf::RenderWindow& window, int gameState, int selectedMenuIndex) {
    if (!m_fontLoaded) return;

    if (gameState == 1) {
        window.draw(m_healthText);
        window.draw(m_scoreText);
        window.draw(m_waveText);
        window.draw(m_enemiesText);
    } else if (gameState == 0) {
        window.draw(m_titleText);
        for (size_t i = 0; i < m_menuOptions.size(); ++i) {
            if (static_cast<int>(i) == selectedMenuIndex) {
                m_menuOptions[i].setFillColor(sf::Color(255, 220, 100));
                m_menuOptions[i].setStyle(sf::Text::Bold);
            } else {
                m_menuOptions[i].setFillColor(sf::Color(180, 180, 180));
                m_menuOptions[i].setStyle(sf::Text::Regular);
            }
            window.draw(m_menuOptions[i]);
        }

        sf::Text instructions(m_font, "Usa ARRIBA/ABAJO para moverte y ENTER para seleccionar", 16);
        instructions.setFillColor(sf::Color(150, 150, 150));
        instructions.setPosition(sf::Vector2f(290.f, 450.f));
        window.draw(instructions);
    } else if (gameState == 2) {
        window.draw(m_pauseText);
    } else if (gameState == 3) {
        window.draw(m_gameOverText);
    } else if (gameState == 4) {
        window.draw(m_victoryText);
    }
}