#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(sf::Vector2f spawnPosition);

    void update(sf::Vector2f playerPosition, sf::Time dt);
    void render(sf::RenderWindow& window);

    sf::FloatRect getGlobalBounds() const;
    bool isAlive() const;
    void takeDamage(int damage);

private:
    sf::RectangleShape m_torso;
    sf::CircleShape m_head;
    sf::RectangleShape m_weapon;
    
    float m_speed;
    int m_health;
    bool m_alive;
};