#include "ball.h"

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void createWindow(sf::RenderWindow &window)
{
    sf::VideoMode videoMode(800, 600);
    const std::string title = "APA/FRR Rap Album";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(videoMode, title, sf::Style::Default, settings);
}

void drawFrame(sf::RenderWindow &window, albumCoverRap &drawCover)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(drawCover);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    sf::Font font;
    if (!font.loadFromFile("font/pricedown.ttf"))
    {
        std::cout << "Font doesn't loaded" << std::endl;
    }

    albumCoverRap drawCover(font);

    while (window.isOpen())
    {
        pollEvents(window);
        drawCover.updateBallElements();
        drawFrame(window, drawCover);
    }
}