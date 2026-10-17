#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f spawnPosition)
    : m_speed(130.0f), m_health(2), m_alive(true) {
    
    m_torso.setSize(sf::Vector2f(26.f, 26.f));
    m_torso.setFillColor(sf::Color(150, 40, 40));
    m_torso.setOrigin(sf::Vector2f(13.f, 13.f));
    m_torso.setPosition(spawnPosition);

    m_head.setRadius(7.f);
    m_head.setFillColor(sf::Color(180, 140, 110));
    m_head.setOrigin(sf::Vector2f(7.f, 14.f));

    m_weapon.setSize(sf::Vector2f(4.f, 20.f));
    m_weapon.setFillColor(sf::Color(120, 120, 120));
    m_weapon.setOrigin(sf::Vector2f(2.f, 20.f));
}

void Enemy::update(sf::Vector2f playerPosition, sf::Time dt) {
    if (!m_alive) return;

    sf::Vector2f pos = m_torso.getPosition();
    sf::Vector2f direction = playerPosition - pos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 1.0f) {
        direction /= length;
        m_torso.move(direction * m_speed * dt.asSeconds());
    }

    m_head.setPosition(sf::Vector2f(pos.x, pos.y - 13.f));
    m_weapon.setPosition(pos);
}

void Enemy::render(sf::RenderWindow& window) {
    if (m_alive) {
        window.draw(m_torso);
        window.draw(m_head);
        window.draw(m_weapon);
    }
}

sf::FloatRect Enemy::getGlobalBounds() const {
    return m_torso.getGlobalBounds();
}

bool Enemy::isAlive() const {
    return m_alive;
}

void Enemy::takeDamage(int damage) {
    m_health -= damage;
    if (m_health <= 0) {
        m_alive = false;
    }
}