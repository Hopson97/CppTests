#pragma once

#include <SFML/Graphics.hpp>

#include "TileMap.h"

struct Player
{
    sf::RectangleShape rect;
    sf::Vector2f velocity;
};

class Application
{
    public:
        Application();

        void run();

    private:
        void checkWinEvents();
        void onInput();
        void onUpdate();
        void onDraw();

        sf::RenderWindow m_window;
        TileMap m_tileMap;

        Player m_player;
};