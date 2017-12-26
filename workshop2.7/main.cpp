#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

struct Ball
{
    sf::Color color;
    sf::CircleShape ball;
    sf::Vector2f speed;
    float timer = 10;
};

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

unsigned random_color(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 255);
    return distribution(generator.engine);
}

bool removeDeathBalls(Ball &balls)
{
    return balls.timer <= 0;
}

float updateBallLifetimes(float timer, const float &dt)
{
    timer = timer - dt;
}

sf::Color randomColor(PRNG &generator)
{
    return {
        sf::Uint8(random(generator, 0, 255)),
        sf::Uint8(random(generator, 0, 255)),
        sf::Uint8(random(generator, 0, 255))};
}

unsigned random_sign(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 1);
    return distribution(generator.engine);
}

float vectorLenght(sf::Vector2f &argument)
{
    return (pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5));
}

bool itsNotBallRadius(std::vector<Ball> &balls, sf::Vector2f clickPosition, const float BALL_SIZE)
{
    bool answer = true;
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f delta = balls[i].ball.getPosition() - clickPosition;
        if (vectorLenght(delta) <= BALL_SIZE * 2)
        {
            answer = false;
        }
    }
    return answer;
}

void initBall(std::vector<Ball> &balls, sf::Vector2f clickPosition, const float BALL_SIZE)
{
    if (itsNotBallRadius(balls, clickPosition, BALL_SIZE))
    {
        Ball bell;
        balls.push_back(bell);

        PRNG generator;
        initGenerator(generator);
        sf::Color color;

        size_t i = balls.size() - 1;
        float speedX = random(generator, 100, 300);
        float speedY = random(generator, 100, 300);
        balls[i].speed = {speedX, speedY};
        balls[i].ball.setFillColor(randomColor(generator));
        balls[i].ball.setRadius(BALL_SIZE);
        balls[i].ball.setPosition({clickPosition});
    }
}

void pollEvents(sf::RenderWindow &window, std::vector<Ball> &balls, const float BALL_SIZE)
{
    sf::Vector2f clickPosition;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            clickPosition = {float(event.mouseButton.x) - BALL_SIZE / 2, float(event.mouseButton.y) - BALL_SIZE / 2};
            initBall(balls, clickPosition, BALL_SIZE);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

float dot(sf::Vector2f speedVector, sf::Vector2f posVector)
{
    return ((speedVector.x * posVector.x) + (speedVector.y * posVector.y));
}

void speedUpdate(std::vector<Ball> &balls, size_t fi, size_t si)
{
    sf::Vector2f deltaPos = balls[fi].ball.getPosition() - balls[si].ball.getPosition();
    sf::Vector2f deltaSpeed = balls[fi].speed - balls[si].speed;
    float speedX = balls[fi].speed.x - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    float speedY = balls[fi].speed.y - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[fi].speed = {speedX, speedY};

    deltaPos = -deltaPos;
    deltaSpeed = -deltaSpeed;
    speedX = balls[si].speed.x - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    speedY = balls[si].speed.y - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[si].speed = {speedX, speedY};
}

void checkBallCollision(std::vector<Ball> &balls, const float BALL_SIZE)
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f delta = balls[fi].ball.getPosition() - balls[si].ball.getPosition();
            if (vectorLenght(delta) <= BALL_SIZE * 2)
            {
                speedUpdate(balls, fi, si);
            }
        }
    }
}

void checkWallCollision(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const float BALL_SIZE, sf::Vector2f &speed, sf::Vector2f &position)
{
    if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((position.x < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((position.y < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
}

void update(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, sf::Clock &clock, const float BALL_SIZE, std::vector<Ball> &balls)
{
    const float dt = clock.restart().asSeconds();
    for (float j = 0; j <= dt; j = j + (dt / 5))
    {
        checkBallCollision(balls, BALL_SIZE);
        for (size_t i = 0; i < balls.size(); ++i)
        {
            sf::Vector2f position = balls[i].ball.getPosition();
            balls[i].timer = updateBallLifetimes(balls[i].timer, dt / 5);
            auto it = std::remove_if(balls.begin(), balls.end(), removeDeathBalls);
            balls.erase(it, balls.end());
            checkWallCollision(WINDOW_WIDTH, WINDOW_HEIGHT, BALL_SIZE, balls[i].speed, position);

            balls[i].ball.setPosition(position + balls[i].speed * (dt / 5));
        }
    }
}

int main()
{
    constexpr float BALL_SIZE = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;

    std::vector<Ball> balls;

    while (window.isOpen())
    {
        pollEvents(window, balls, BALL_SIZE);
        update(WINDOW_WIDTH, WINDOW_HEIGHT, clock, BALL_SIZE, balls);
        redrawFrame(window, balls);
    }
}