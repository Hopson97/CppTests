#pragma once

#include <SFML/Graphics.hpp>

namespace WinInfo
{
    constexpr unsigned WIDTH = 1366;
    constexpr unsigned HEIGHT = 768;
}

class Application
{
    public:
        Application();

        void run();

    private:
        void handleEvents();

        sf::RenderWindow m_window;
};