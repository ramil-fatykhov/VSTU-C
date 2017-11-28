#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

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

void drawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    arrow.setPosition({400, 300});
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    arrow.setPointCount(7);
    arrow.setPoint(0, {0, -40});
    arrow.setPoint(1, {40, 0});
    arrow.setPoint(2, {20, 0});
    arrow.setPoint(3, {20, 40});
    arrow.setPoint(4, {-20, 40});
    arrow.setPoint(5, {-20, 0});
    arrow.setPoint(6, {-40, 0});
    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(2);
    arrow.setRotation(12);

    while (window.isOpen())
    {
        pollEvents(window);
        drawFrame(window, arrow);
    }
}