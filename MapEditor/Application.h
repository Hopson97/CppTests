#pragma once

#include <SFML/Graphics.hpp>

class Application
{
    public:
        Application();

        void run();

    private:
        void handleEvents();

        sf::RenderWindow m_window;
};