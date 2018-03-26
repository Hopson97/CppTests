#include "Application.h"

Application::Application()
    : m_window({ WinInfo::WIDTH, WinInfo::HEIGHT }, "Map Editor Test")
{
    m_window.setFramerateLimit(60);
}

void Application::run()
{
    while (m_window.isOpen()) {
        handleEvents();

        m_window.clear();

        m_window.display();
    }
}

void Application::handleEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
        }
    }
}