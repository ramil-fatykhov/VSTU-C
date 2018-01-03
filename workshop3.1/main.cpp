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

void update(sf::Clock &clock, sf::Vector2f &position, sf::Vector2f &speed, sf::CircleShape &circle, sf::Text &text)
{
    const float dt = clock.restart().asSeconds();
    speed.y += dt * 9.8f;

    position += dt * speed;
    if ((position.y + 2 * 80 >= 380) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((position.y < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
    circle.setPosition(position);
    text.setPosition(position);
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

    sf::Clock clock;
    sf::Vector2f position = {480, 380};
    sf::Vector2f speed = {0, -80};

    while (window.isOpen())
    {
        pollEvents(window);
        update(clock, position, speed, circle, text);
        drawFrame(window, circle, text);
    }
}