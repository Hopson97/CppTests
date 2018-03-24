#pragma once

#include <SFML/Graphics.hpp>

#include "TileMap.h"
#include "Player.h"

class Application
{
    public:
        Application();

        void run();

    private:
        void checkWinEvents();
        void onInput();
        void onUpdate(float dt);
        void onDraw();

        sf::RenderWindow m_window;
        TileMap m_tileMap;

        Player m_player;
};