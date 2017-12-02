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
    balls[0].ball.setPosition({40, 250});
    balls[1].ball.setPosition({400, 300});
    balls[2].ball.setPosition({410, 290});
    balls[3].ball.setPosition({20, 600});
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
    balls[1].speed = {-200.f, 100.f};
    balls[2].speed = {30.f, -300.f};
    balls[3].speed = {-200.f, 400.f};
    balls[4].speed = {400.f, -50.f};
}

void update(const float &dt, std::vector<Ball> &balls, sf::Vector2f &position)
{
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

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (int i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

int main()
{
    constexpr int BALLS_COUNT = 5;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wawe Moving Ball");
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