#include "ball.h"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

void initWindow(sf::RenderWindow &window)
{
    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(videoMode, "APA/FRR ", sf::Style::Default, settings);
}

void initText(sf::Text &text, sf::Font &font)
{
    text.setFont(font);
    text.setString("APA/FRR");
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::Black);
    text.setPosition(390, 310);
}

void initCircle(sf::CircleShape &circle)
{
    circle.setOrigin({40, 40});
    circle.setPosition({400, 300});
    circle.setFillColor(sf::Color(0xFF, 0xC0, 0x00));
    circle.setOutlineColor(sf::Color(0x2F, 0x55, 0x97));
    circle.setOutlineThickness(4);
}