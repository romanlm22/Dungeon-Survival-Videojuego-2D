#include "Game.hpp"
#include <cstdlib>
#include <cmath>
#include <algorithm>

Game::Game()
    : m_window(sf::VideoMode({960, 640}), "Dungeon Survival - Edicion Medieval"),
      m_score(0), m_currentWave(1), m_gameState(0), m_selectedMenuIndex(0),
      m_spacePressedLastFrame(false), m_escapePressedLastFrame(false), 
      m_enterPressedLastFrame(false), m_upPressedLastFrame(false), m_downPressedLastFrame(false) {
    m_window.setFramerateLimit(60);

    m_arenaBounds = sf::RectangleShape(sf::Vector2f(900.f, 580.f));
    m_arenaBounds.setPosition(sf::Vector2f(30.f, 30.f));
    m_arenaBounds.setFillColor(sf::Color(35, 30, 40));
    m_arenaBounds.setOutlineThickness(6.f);
    m_arenaBounds.setOutlineColor(sf::Color(70, 60, 80));
}

void Game::startNewGame() {
    m_player = Player();
    m_score = 0;
    m_currentWave = 1;
    m_enemies.clear();
    startNextWave();
    m_gameState = 1;
}

void Game::startNextWave() {
    m_enemies.clear();
    int enemyCount = 2 + m_currentWave * 3;
    for (int i = 0; i < enemyCount; ++i) {
        float x = 60.f + static_cast<float>(std::rand() % 840);
        float y = 60.f + static_cast<float>(std::rand() % 520);
        while (std::abs(x - 480.f) < 100.f && std::abs(y - 320.f) < 100.f) {
            x = 60.f + static_cast<float>(std::rand() % 840);
            y = 60.f + static_cast<float>(std::rand() % 520);
        }
        m_enemies.emplace_back(sf::Vector2f(x, y));
    }
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();
        processEvents();
        if (m_gameState == 1) {
            update(dt);
        }
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }

    bool enterPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    bool escapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

    if (m_gameState == 0) {
        if (upPressed && !m_upPressedLastFrame) {
            m_selectedMenuIndex = (m_selectedMenuIndex - 1 + 2) % 2;
        }
        if (downPressed && !m_downPressedLastFrame) {
            m_selectedMenuIndex = (m_selectedMenuIndex + 1) % 2;
        }
        if (enterPressed && !m_enterPressedLastFrame) {
            if (m_selectedMenuIndex == 0) {
                startNewGame();
            } else {
                m_window.close();
            }
        }
    } else if (m_gameState == 3 || m_gameState == 4) {
        if (enterPressed && !m_enterPressedLastFrame) {
            m_gameState = 0;
        }
    }

    if (escapePressed && !m_escapePressedLastFrame) {
        if (m_gameState == 1) {
            m_gameState = 2;
        } else if (m_gameState == 2) {
            m_gameState = 1;
        }
    }

    m_enterPressedLastFrame = enterPressed;
    m_escapePressedLastFrame = escapePressed;
    m_upPressedLastFrame = upPressed;
    m_downPressedLastFrame = downPressed;
}

void Game::update(sf::Time dt) {
    m_player.handleInput();
    m_player.update(dt, m_arenaBounds.getGlobalBounds());

    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    if (spacePressed && !m_spacePressedLastFrame) {
        m_player.startAttack();

        float attackRadius = 60.0f;
        sf::Vector2f playerPos = m_player.getPosition();

        for (auto& enemy : m_enemies) {
            if (!enemy.isAlive()) continue;
            sf::Vector2f enemyPos = enemy.getGlobalBounds().position;
            
            float distX = playerPos.x - enemyPos.x;
            float distY = playerPos.y - enemyPos.y;
            float distance = std::sqrt(distX * distX + distY * distY);

            if (distance <= attackRadius) {
                enemy.takeDamage(1);
                if (!enemy.isAlive()) {
                    m_score += 100;
                }
            }
        }
    }
    m_spacePressedLastFrame = spacePressed;

    for (auto& enemy : m_enemies) {
        enemy.update(m_player.getPosition(), dt);

        if (enemy.isAlive() && enemy.getGlobalBounds().findIntersection(m_player.getGlobalBounds())) {
            m_player.takeDamage(10);
            if (m_player.getHealth() <= 0) {
                m_gameState = 3; 
            }
        }
    }

    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(), [](const Enemy& e) { return !e.isAlive(); }),
        m_enemies.end()
    );

    if (m_enemies.empty()) {
        if (m_currentWave < 5) {
            m_currentWave++;
            startNextWave();
        } else {
            m_gameState = 4; 
        }
    }

    m_hud.update(m_player.getHealth(), m_score, m_currentWave, static_cast<int>(m_enemies.size()));
}

void Game::render() {
    m_window.clear(sf::Color(45, 55, 72)); 

    if (m_gameState == 1 || m_gameState == 2) {
        sf::RectangleShape tile(sf::Vector2f(40.f, 40.f));
        for (float x = 30.f; x < 930.f; x += 40.f) {
            for (float y = 30.f; y < 610.f; y += 40.f) {
                tile.setPosition(sf::Vector2f(x, y));
                int pattern = static_cast<int>((x / 40) + (y / 40)) % 3;
                if (pattern == 0) {
                    tile.setFillColor(sf::Color(65, 75, 95));
                } else if (pattern == 1) {
                    tile.setFillColor(sf::Color(55, 65, 85));
                } else {
                    tile.setFillColor(sf::Color(50, 58, 75));
                }
                tile.setOutlineThickness(1.f);
                tile.setOutlineColor(sf::Color(35, 42, 55));
                m_window.draw(tile);
            }
        }

        sf::ConvexShape archLeft;
        archLeft.setPointCount(4);
        archLeft.setPoint(0, sf::Vector2f(100.f, 30.f));
        archLeft.setPoint(1, sf::Vector2f(260.f, 30.f));
        archLeft.setPoint(2, sf::Vector2f(260.f, 130.f));
        archLeft.setPoint(3, sf::Vector2f(100.f, 130.f));
        archLeft.setFillColor(sf::Color(35, 42, 55));
        m_window.draw(archLeft);

        sf::ConvexShape archRight;
        archRight.setPointCount(4);
        archRight.setPoint(0, sf::Vector2f(700.f, 30.f));
        archRight.setPoint(1, sf::Vector2f(860.f, 30.f));
        archRight.setPoint(2, sf::Vector2f(860.f, 130.f));
        archRight.setPoint(3, sf::Vector2f(700.f, 130.f));
        archRight.setFillColor(sf::Color(35, 42, 55));
        m_window.draw(archRight);

        m_window.draw(m_arenaBounds);

        for (auto& enemy : m_enemies) {
            enemy.render(m_window);
        }
        m_player.render(m_window);
    }

    m_hud.render(m_window, m_gameState, m_selectedMenuIndex);

    m_window.display();
}