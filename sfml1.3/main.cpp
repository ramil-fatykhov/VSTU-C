#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "title");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({400, 250});
    shape1.setPosition({40, 300});
    shape1.setFillColor(sf::Color(0x4d, 0x2d, 0x0b));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({70, 150});
    shape2.setPosition({80, 400});
    shape2.setFillColor(sf::Color(0x18, 0x16, 0x18));
    window.draw(shape2);

    sf::ConvexShape shape3;
    shape3.setFillColor(sf::Color(0x5e, 0x1d, 0x18));
    shape3.setPosition({240, 200});
    shape3.setPointCount(4);
    shape3.setPoint(0, {-90, 0});
    shape3.setPoint(1, {+90, 0});
    shape3.setPoint(2, {+230, 100});
    shape3.setPoint(3, {-230, 100});
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({30, 80});
    shape4.setPosition({290, 180});
    shape4.setFillColor(sf::Color(0x3a, 0x39, 0x37));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({60, 40});
    shape5.setPosition({275, 150});
    shape5.setFillColor(sf::Color(0x3a, 0x39, 0x37));
    window.draw(shape5);

    sf::CircleShape shape6(15);
    shape6.setPosition({300, 120});
    shape6.setFillColor(sf::Color(0xbf, 0xbf, 0xbf));
    window.draw(shape6);

    sf::CircleShape shape7(18);
    shape7.setPosition({310, 100});
    shape7.setFillColor(sf::Color(0xbf, 0xbf, 0xbf));
    window.draw(shape7);

    sf::CircleShape shape8(22);
    shape8.setPosition({320, 70});
    shape8.setFillColor(sf::Color(0xbf, 0xbf, 0xbf));
    window.draw(shape8);

    sf::CircleShape shape9(27);
    shape9.setPosition({330, 40});
    shape9.setFillColor(sf::Color(0xbf, 0xbf, 0xbf));
    window.draw(shape9);

    window.display();

    sf::sleep(sf::seconds(5));
}