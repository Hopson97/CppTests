#pragma once

#include <SFML/Graphics.hpp>

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
        sf::RectangleShape m_player;
};