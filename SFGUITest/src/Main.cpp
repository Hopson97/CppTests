// Always include the necessary header files.
// Including SFGUI/Widgets.hpp includes everything
// you can possibly need automatically.
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 768), "SFGUI Buttons Example", sf::Style::Titlebar | sf::Style::Close);

   


    window.resetGLStates();
    sfg::SFGUI sfgui;

    auto guiWindow = sfg::Window::Create();
    guiWindow->SetTitle("Title");

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
    auto scrollBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);

    sf::Image img;
    img.loadFromFile("res/btn.png");
    for (int i = 0; i < 10; i++) {
        auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
        for (int i = 0; i < 10; i++) {
            auto b = sfg::Button::Create();
            b->SetImage(sfg::Image::Create(img));
            box->Pack(b);
        }
        scrollBox->Pack(box);
    }

    auto scroll = sfg::ScrolledWindow::Create();
    scroll->SetScrollbarPolicy(sfg::ScrolledWindow::ScrollbarPolicy::HORIZONTAL_ALWAYS |
        sfg::ScrolledWindow::ScrollbarPolicy::VERTICAL_ALWAYS);

    scroll->SetRequisition(sf::Vector2f(100.f, 100.f));
    scroll->AddWithViewport(scrollBox);
    box->Pack(scroll);
    guiWindow->Add(box);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            guiWindow->HandleEvent(event);
            if (event.type == sf::Event::Closed) {
                return EXIT_SUCCESS;
            }
        }

        guiWindow->Update(0.5f);


        window.clear();
        sfgui.Display(window);
        window.display();
    }

    return EXIT_SUCCESS;
}