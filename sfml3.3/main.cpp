#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

struct Eye
{
    sf::ConvexShape white;
    sf::ConvexShape pupil;
};

void initEllipse(sf::ConvexShape& ellipse, const sf::Vector2f& ellipseRadius, const sf::Vector2f& position)
{
    constexpr int pointCount = 200;

    ellipse.setPosition(position);
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)     
        };        
        ellipse.setPoint(pointNo, point);
    }
}

void initEye(Eye& eye, const sf::Vector2f& position)
{
    initEllipse(eye.white, {60.f, 100.f}, position);    
    initEllipse(eye.pupil, {20.f, 40.f}, position);    
    eye.white.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye.pupil.setFillColor(sf::Color(0, 0, 0));
}

void drawEye(sf::RenderWindow& window, const Eye& eye)
{
    window.draw(eye.white);
    window.draw(eye.pupil);
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f& mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

float length(const sf::Vector2f& value)
{
    return std::hypotf(value.x, value.y);
}

void updateEye(const sf::Vector2f& mousePosition, Eye& eye)
{
    const sf::Vector2f radius = {20.f, 40.f};

    const sf::Vector2f delta = mousePosition - eye.white.getPosition();
    const float angle = atan2(delta.y, delta.x);
    std::cout << "angle: " << angle << std::endl;
    sf::Vector2f shapeOffset;

    shapeOffset.x = radius.x * std::cos(angle);
    shapeOffset.y = radius.y * std::sin(angle);

    if (length(delta) < length(shapeOffset))
    {
        eye.pupil.setPosition(mousePosition);
    }
    else
    {
        eye.pupil.setPosition(eye.white.getPosition() + shapeOffset);            
    }
}

void update(const sf::Vector2f& mousePosition, Eye& leftEye, Eye& rightEye)
{
    updateEye(mousePosition, leftEye);
    updateEye(mousePosition, rightEye);
}

void redrawFrame(sf::RenderWindow& window, const Eye& leftEye, const Eye& rightEye)
{
    window.clear(sf::Color(0xFF, 0x80, 0xA0));
    drawEye(window, leftEye);
    drawEye(window, rightEye);
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
        "Pointer follows mouse", sf::Style::Default, settings);

    Eye leftEye;
    initEye(leftEye, {200, 300});
    Eye rightEye;
    initEye(rightEye, {400, 300});
    
    sf::Vector2f mousePosition;
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}