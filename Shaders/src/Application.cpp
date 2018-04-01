#include "Application.h"

#include <iostream>

Application::Application()
    : m_window({ 1280, 720 }, "Collide")
{
    m_window.setFramerateLimit(60);
}

void Application::run()
{
    sf::Clock clock;
    while (m_window.isOpen()) {
        checkWinEvents();
        onInput();
        onUpdate(clock.restart().asSeconds());
        m_window.clear();
        onDraw();
        m_window.display();
    }
}

void Application::checkWinEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
    }
}

void Application::onInput()
{

}

void Application::onUpdate(float dt)
{  
}

void Application::onDraw()
{
}
