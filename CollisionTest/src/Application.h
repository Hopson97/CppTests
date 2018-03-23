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
        void onUpdate();
        void onDraw();

        sf::RenderWindow m_window;
};