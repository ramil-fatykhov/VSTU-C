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

void drawFrame(sf::RenderWindow &window, sf::CircleShape &circle, sf::Text &text)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(circle);
    window.draw(text);
    window.display();
}

int main()
{

    sf::RenderWindow window;
    initWindow(window);

    sf::Font font;
    if (!font.loadFromFile("font/pricedown.ttf"))
    {
        std::cout << "Font doesn't loaded" << std::endl;
    }

    sf::Text text;
    initText(text, font);

    sf::CircleShape circle(80);
    initCircle(circle);

    while (window.isOpen())
    {
        pollEvents(window);
        drawFrame(window, circle, text);
    }
}