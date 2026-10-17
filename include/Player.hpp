#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void handleInput();
    void update(sf::Time dt, const sf::FloatRect& bounds);
    void render(sf::RenderWindow& window);

    void startAttack();
    bool isAttacking() const;

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    int getHealth() const;
    void takeDamage(int amount);

private:
    sf::RectangleShape m_torso;        
    sf::RectangleShape m_helmet;       
    sf::RectangleShape m_crown;         
    sf::RectangleShape m_visorCrossV;   
    sf::RectangleShape m_visorCrossH;  
    
    sf::RectangleShape m_swordBlade;    
    sf::RectangleShape m_swordGuard;    
    
    float m_speed;
    sf::Vector2f m_velocity;
    
    int m_health;
    int m_maxHealth;
    sf::Clock m_damageClock;

    bool m_isAttacking;
    sf::Clock m_attackClock;
    float m_attackDuration;
};