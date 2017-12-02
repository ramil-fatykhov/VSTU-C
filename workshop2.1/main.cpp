#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
    sf::Vector2f position;
};

void initBall(Ball &ball, const sf::Vector2f &position, const sf::Vector2f &speed)
{
    ball.speed = speed;
    ball.ball.setPosition(position);
    ball.position = position;
    ball.ball.setRadius(40);
}

void updateBall(const float &dt, Ball &ball)
{
    const float BALL_SIZE = 40;
    ball.position += ball.speed * dt;

    if ((ball.position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (ball.speed.x > 0))
    {
        ball.speed.x = -ball.speed.x;
    }
    if ((ball.position.x < 0) && (ball.speed.x < 0))
    {
        ball.speed.x = -ball.speed.x;
    }
    if ((ball.position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (ball.speed.y > 0))
    {
        ball.speed.y = -ball.speed.y;
    }
    if ((ball.position.y < 0) && (ball.speed.y < 0))
    {
        ball.speed.y = -ball.speed.y;
    }

    ball.ball.setPosition(ball.position);
}

void update(const float &dt, Ball &blueBall, Ball &redBall, Ball &blackBall, Ball &whiteBall, Ball &greenBall)
{
    updateBall(dt, blueBall);
    updateBall(dt, redBall);
    updateBall(dt, blackBall);
    updateBall(dt, whiteBall);
    updateBall(dt, greenBall);
}

void redrawFrame(sf::RenderWindow &window, const Ball &blueBall, const Ball &redBall, const Ball &blackBall, const Ball &whiteBall, const Ball &greenBall)
{
    window.draw(blueBall.ball);
    window.draw(redBall.ball);
    window.draw(blackBall.ball);
    window.draw(whiteBall.ball);
    window.draw(greenBall.ball);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wawe Moving Ball");
    sf::Clock clock;

    std::vector<Ball> balls;

    sf::Vector2f position = {10, 350};
    Ball blueBall;
    initBall(blueBall, {400, 300}, {500, 300});
    Ball redBall;
    initBall(redBall, {300, 200}, {-400, 200});
    Ball blackBall;
    initBall(blackBall, {200, 100}, {70, -70});
    Ball whiteBall;
    initBall(whiteBall, {100, 50}, {90, 70});
    Ball greenBall;
    initBall(greenBall, {100, 50}, {300, 70});

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
        update(dt, blueBall, redBall, blackBall, whiteBall, greenBall);
        window.clear();
        redrawFrame(window, blueBall, redBall, blackBall, whiteBall, greenBall);
        window.display();
    }
}