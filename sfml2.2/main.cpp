#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr int pointCount = 300;
    constexpr int radius = 40;
    constexpr float period = 3.f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Polar Rose", sf::Style::Default, settings);
    sf::Clock clock;

    sf::ConvexShape rose;
    rose.setPosition({500, 300});
    rose.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    sf::Vector2f position = {500, 320};
    const float speed = 20.f;

    const sf::Vector2f center = {400, 300};

    rose.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            200 * std::sin(6 * angle) * std::sin(angle),
            200 * std::sin(6 * angle) * std::cos(angle)};
        rose.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float time = clock.getElapsedTime().asSeconds();

        position.x = radius * cos((2 * M_PI * time) / period);
        position.y = radius * sin((2 * M_PI * time) / period);

        rose.setPosition(center + position);

        window.clear();
        window.draw(rose);
        window.display();
    }
}