#include "Player.h"

#include "TileMap.h"

#include <iostream>

Player::Player()
:   m_boxSize (1.0f, 2.0f)
,   m_rect({ (float)TILE_SIZE * m_boxSize.x, (float)TILE_SIZE * m_boxSize.y })
{
    m_rect.setFillColor(sf::Color::Blue);
    m_rect.setPosition(100, 200);
}

void Player::input()
{
    float speed = 25.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_velocity.y -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_velocity.y += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_velocity.x -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_velocity.x += speed;
    }
}

void Player::update(float dt)
{
    m_rect.move(m_velocity * dt);
    m_velocity *= 0.95f;
}

void Player::draw(sf::RenderTarget & window)
{
    window.draw(m_rect);
}

const sf::Vector2f& Player::getPosition() const
{
    return m_rect.getPosition();
}
const sf::Vector2f & Player::getBoxSize() const
{
    return m_boxSize;
}



