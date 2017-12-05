#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float BALL_SIZE = 40;

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
    sf::Vector2f position;
};

void initBalls(std::vector<Ball> &balls)
{
    balls[0].ball.setPosition({40, 150});
    balls[1].ball.setPosition({200, 300});
    balls[2].ball.setPosition({410, 20});
    balls[3].ball.setPosition({110, 600});
    balls[4].ball.setPosition({111, 222});

    balls[0].ball.setFillColor(sf::Color(242, 0, 0));
    balls[1].ball.setFillColor(sf::Color(121, 141, 1));
    balls[2].ball.setFillColor(sf::Color(3, 77, 129));
    balls[3].ball.setFillColor(sf::Color(239, 255, 2));
    balls[4].ball.setFillColor(sf::Color(1, 140, 16));

    balls[0].ball.setRadius(BALL_SIZE);
    balls[1].ball.setRadius(BALL_SIZE);
    balls[2].ball.setRadius(BALL_SIZE);
    balls[3].ball.setRadius(BALL_SIZE);
    balls[4].ball.setRadius(BALL_SIZE);

    balls[0].speed = {500.f, -100.f};
    balls[1].speed = {-100.f, 100.f};
    balls[2].speed = {30.f, -300.f};
    balls[3].speed = {-200.f, 400.f};
    balls[4].speed = {400.f, -50.f};
}

float scalarProduct(sf::Vector2f speedVector, sf::Vector2f positionVector)
{
    return ((speedVector.x * positionVector.x) + (speedVector.y * positionVector.y));
}

void updateSpeed(std::vector<Ball> &balls, size_t fi, size_t si)
{
    sf::Vector2f deltaPosition = balls[fi].ball.getPosition() - balls[si].ball.getPosition();
    sf::Vector2f deltaPosition2 = balls[si].ball.getPosition() - balls[fi].ball.getPosition();
    sf::Vector2f deltaSpeed = balls[fi].speed - balls[si].speed;
    sf::Vector2f deltaSpeed2 = balls[si].speed - balls[fi].speed;

    float speedXAfterImpact = balls[fi].speed.x - (scalarProduct(deltaSpeed, deltaPosition) / std::pow(std::hypot(deltaPosition.x, deltaPosition.y), 2.0)) * deltaPosition.x;
    float speedYAfterImpact = balls[fi].speed.y - (scalarProduct(deltaSpeed, deltaPosition) / std::pow(std::hypot(deltaPosition.x, deltaPosition.y), 2.0)) * deltaPosition.y;
    balls[fi].speed = {speedXAfterImpact, speedYAfterImpact};

    speedXAfterImpact = balls[si].speed.x - (scalarProduct(deltaSpeed2, deltaPosition2) / std::pow(std::hypot(deltaPosition2.x, deltaPosition2.y), 2.0)) * deltaPosition2.x;
    speedYAfterImpact = balls[si].speed.y - (scalarProduct(deltaSpeed2, deltaPosition2) / std::pow(std::hypot(deltaPosition2.x, deltaPosition2.y), 2.0)) * deltaPosition2.y;
    balls[si].speed = {speedXAfterImpact, speedYAfterImpact};
}

void checkColision(std::vector<Ball> &balls)
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f deltaPosition = balls[fi].ball.getPosition() - balls[si].ball.getPosition();
            if (std::hypot(deltaPosition.x, deltaPosition.y) < BALL_SIZE * 2)
            {
                updateSpeed(balls, fi, si);
            }
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (int i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

void update(const float &dt, std::vector<Ball> &balls, sf::Vector2f &position)
{
    checkColision(balls);
    for (int i = 0; i < balls.size(); ++i)
    {
        position = balls[i].ball.getPosition();

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        position += balls[i].speed * dt;
        balls[i].ball.setPosition(position);
    }
}

int main()
{
    constexpr int BALLS_COUNT = 5;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Moving ball", sf::Style::Default, settings);
    sf::Clock clock;

    std::vector<Ball> balls(BALLS_COUNT);
    sf::Vector2f position = {0, 0};
    initBalls(balls);

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
        const float dt = clock.restart().asSeconds();
        update(dt, balls, position);
        redrawFrame(window, balls);
    }
}