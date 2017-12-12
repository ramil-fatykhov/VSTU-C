#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition, sf::Sprite &sprite)
{
    mousePosition = {float(event.x), float(event.y)};
    const sf::Vector2f distance = mousePosition - sprite.getPosition();
    const float angle = fmodf(atan2(distance.y, distance.x) + 2 * M_PI, 2 * M_PI);
    std::cout << "angle=" << toDegrees(angle) << std::endl;
    if ((toDegrees(angle) <= 270) && (toDegrees(angle) >= 90))
    {
        sprite.setScale(-1, 1);
    }
    else
    {
        sprite.setScale(1, 1);
    }
    std::cout << "mouse x=" << event.x << "mouse y=" << event.y << std::endl;
}

float lenghtVector(const sf::Vector2f &vector)
{
    return std::hypotf(vector.x, vector.y);
}

void update(const sf::Vector2f &mousePosition, sf::Sprite &sprite, sf::Clock &clock, sf::Vector2f &position, sf::Sprite &laser)
{
    laser.setPosition(mousePosition);
    const sf::Vector2f motion = mousePosition - sprite.getPosition();
    const sf::Vector2f direction = motion / lenghtVector(motion);

    const float dt = clock.restart().asSeconds();
    const float speed = 200.f;

    position += direction * speed * dt;

    sprite.setPosition(position);
}

void drawFrame(sf::RenderWindow &window, sf::Sprite &sprite, sf::Sprite &laser)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(sprite);
    window.draw(laser);
    window.display();
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Sprite &sprite)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition, sprite);
            break;
        default:
            break;
        }
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "texture cat", sf::Style::Default, settings);

    sf::Texture cat;
    cat.loadFromFile("images/cat.png");
    if (!cat.loadFromFile("images/cat.png"))
    {
        std::cout << "Не удалось загрузить текстуру cat" << std::endl;
    }
    sf::Texture redPointer;
    redPointer.loadFromFile("images/red_pointer.png");
    if (!redPointer.loadFromFile("images/red_pointer.png"))
    {
        std::cout << "Не удалось загрузить текстуру redPointer" << std::endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(cat);
    sprite.setPosition(400, 300);
    sprite.setOrigin(19, 17.5);

    sf::Sprite laser;
    laser.setTexture(redPointer);
    laser.setOrigin(16, 16);

    sf::Clock clock;
    sf::Vector2f position;
    sf::Vector2f mousePosition;
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, sprite);
        update(mousePosition, sprite, clock, position, laser);
        drawFrame(window, sprite, laser);
    }
}