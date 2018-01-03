#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

class albumCoverRap : public sf::Drawable
{
  public:
    albumCoverRap(sf::Font &font);
    void updateBallElements();

  private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Text m_albumTitle;
    sf::Clock clock;
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Vector2f center = {400, 100};
    sf::CircleShape m_albumCoverBackground;
};