#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "title");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({30, 100});
    shape1.setPosition({40, 10});
    shape1.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({50, 30});
    shape2.setPosition({40, 10});
    shape2.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({50, 30});
    shape3.setPosition({40, 50});
    shape3.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape3);

    sf::CircleShape shape4(30);
    shape4.setFillColor(sf::Color(0x43, 0x43, 0x43));
    shape4.setPosition({100, 10});
    window.draw(shape4);

    sf::CircleShape shape5(20);
    shape5.setFillColor(sf::Color(0x00, 0x00, 0x00));
    shape5.setPosition({110, 20});
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({100, 30});
    shape6.setRotation(90);
    shape6.setPosition({130, 10});
    shape6.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({45, 25});
    shape7.setRotation(45);
    shape7.setPosition({130, 60});
    shape7.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape7);

    sf::CircleShape shape8(30);
    shape8.setFillColor(sf::Color(0x43, 0x43, 0x43));
    shape8.setPosition({170, 10});
    window.draw(shape8);

    sf::CircleShape shape9(20);
    shape9.setFillColor(sf::Color(0x00, 0x00, 0x00));
    shape9.setPosition({180, 20});
    window.draw(shape9);

    sf::RectangleShape shape10;
    shape10.setSize({100, 30});
    shape10.setRotation(90);
    shape10.setPosition({200, 10});
    shape10.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape10);

    sf::RectangleShape shape11;
    shape11.setSize({45, 25});
    shape11.setRotation(45);
    shape11.setPosition({200, 60});
    shape11.setFillColor(sf::Color(0x43, 0x43, 0x43));
    window.draw(shape11);

    window.display();

    sf::sleep(sf::seconds(5));
}