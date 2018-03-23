#include "Application.h"

Application::Application()
    : m_window({ 1280, 720 }, "Collide")
{
    m_window.setFramerateLimit(60);
}

void Application::run()
{
    while (m_window.isOpen()) {
        checkWinEvents();
        onInput();
        onUpdate();
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
    }
}

void Application::onInput()
{
}

void Application::onUpdate()
{
}

void Application::onDraw()
{
}
