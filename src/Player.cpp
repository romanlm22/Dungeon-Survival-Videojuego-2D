#include "Player.hpp"
#include <cmath>

Player::Player() 
    : m_speed(240.0f), m_velocity(0.0f, 0.0f), m_health(100), m_maxHealth(100),
      m_isAttacking(false), m_attackDuration(0.2f) {
    
    m_torso.setSize(sf::Vector2f(26.f, 30.f));
    m_torso.setFillColor(sf::Color(65, 85, 120));
    m_torso.setOrigin(sf::Vector2f(13.f, 15.f));
    m_torso.setPosition(sf::Vector2f(480.f, 320.f));

    m_helmet.setSize(sf::Vector2f(20.f, 16.f));
    m_helmet.setFillColor(sf::Color(80, 85, 95));
    m_helmet.setOrigin(sf::Vector2f(10.f, 22.f));

    m_crown.setSize(sf::Vector2f(18.f, 5.f));
    m_crown.setFillColor(sf::Color(240, 200, 50));
    m_crown.setOrigin(sf::Vector2f(9.f, 27.f));

    m_visorCrossV.setSize(sf::Vector2f(3.f, 10.f));
    m_visorCrossV.setFillColor(sf::Color(240, 200, 50));
    m_visorCrossV.setOrigin(sf::Vector2f(1.5f, 20.f));

    m_visorCrossH.setSize(sf::Vector2f(8.f, 3.f));
    m_visorCrossH.setFillColor(sf::Color(240, 200, 50));
    m_visorCrossH.setOrigin(sf::Vector2f(4.f, 18.f));

    m_swordBlade.setSize(sf::Vector2f(6.f, 32.f));
    m_swordBlade.setFillColor(sf::Color(220, 230, 245)); 
    m_swordBlade.setOrigin(sf::Vector2f(3.f, 32.f));

    m_swordGuard.setSize(sf::Vector2f(14.f, 4.f));
    m_swordGuard.setFillColor(sf::Color(240, 200, 50)); 
    m_swordGuard.setOrigin(sf::Vector2f(7.f, 34.f));
}

void Player::handleInput() {
    m_velocity = sf::Vector2f(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        m_velocity.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        m_velocity.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_velocity.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_velocity.x += 1.0f;
    }

    float length = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (length != 0.0f) {
        m_velocity /= length;
    }
}

void Player::startAttack() {
    if (!m_isAttacking) {
        m_isAttacking = true;
        m_attackClock.restart();
    }
}

bool Player::isAttacking() const {
    return m_isAttacking;
}

void Player::update(sf::Time dt, const sf::FloatRect& bounds) {
    m_torso.move(m_velocity * m_speed * dt.asSeconds());

    sf::Vector2f pos = m_torso.getPosition();
    sf::Vector2f size = m_torso.getSize();

    if (pos.x - size.x / 2.f < bounds.position.x) pos.x = bounds.position.x + size.x / 2.f;
    if (pos.x + size.x / 2.f > bounds.position.x + bounds.size.x) pos.x = bounds.position.x + bounds.size.x - size.x / 2.f;
    if (pos.y - size.y / 2.f < bounds.position.y) pos.y = bounds.position.y + size.y / 2.f;
    if (pos.y + size.y / 2.f > bounds.position.y + bounds.size.y) pos.y = bounds.position.y + bounds.size.y - size.y / 2.f;

    m_torso.setPosition(pos);
    m_helmet.setPosition(pos);
    m_crown.setPosition(pos);
    m_visorCrossV.setPosition(pos);
    m_visorCrossH.setPosition(pos);
    m_swordBlade.setPosition(pos);
    m_swordGuard.setPosition(pos);

    if (m_isAttacking) {
        float elapsed = m_attackClock.getElapsedTime().asSeconds();
        if (elapsed < m_attackDuration) {
            float progress = elapsed / m_attackDuration;
            float rotationAngle = -75.f + (progress * 200.f);
            m_swordBlade.setRotation(sf::degrees(rotationAngle));
            m_swordGuard.setRotation(sf::degrees(rotationAngle));
        } else {
            m_isAttacking = false;
            m_swordBlade.setRotation(sf::degrees(0.f));
            m_swordGuard.setRotation(sf::degrees(0.f));
        }
    } else {
        m_swordBlade.setRotation(sf::degrees(0.f));
        m_swordGuard.setRotation(sf::degrees(0.f));
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(m_torso);
    window.draw(m_helmet);
    window.draw(m_crown);
    window.draw(m_visorCrossV);
    window.draw(m_visorCrossH);
    window.draw(m_swordBlade);
    window.draw(m_swordGuard);
}

sf::Vector2f Player::getPosition() const {
    return m_torso.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const {
    return m_torso.getGlobalBounds();
}

int Player::getHealth() const {
    return m_health;
}

void Player::takeDamage(int amount) {
    if (m_damageClock.getElapsedTime().asSeconds() > 0.6f) {
        m_health -= amount;
        if (m_health < 0) m_health = 0;
        m_damageClock.restart();
        m_torso.setFillColor(sf::Color::White);
    } else {
        m_torso.setFillColor(sf::Color(65, 85, 120));
    }
}