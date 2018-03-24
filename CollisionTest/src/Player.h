#pragma once

#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player();

        void input();
        void update(); 
        void draw(sf::RenderTarget& window);

        const sf::Vector2f& getPosition() const;
        const sf::Vector2f& getBoxSize() const;

    private:
        sf::Vector2f m_boxSize;
        sf::RectangleShape m_rect;
        sf::Vector2f m_velocity;
};