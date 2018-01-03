#include "ball.h"

albumCoverRap::albumCoverRap(sf::Font &font)
{
    m_albumTitle.setFont(font);
    m_albumTitle.setString("APA/FRR");
    m_albumTitle.setCharacterSize(36);
    m_albumTitle.setFillColor(sf::Color::Black);
    m_albumTitle.setPosition(390, 310);
    m_albumTitle.setOrigin({10, -10});

    m_albumCoverBackground.setRadius(80);
    m_albumCoverBackground.setOrigin({40, 40});
    m_albumCoverBackground.setPosition({400, 300});
    m_albumCoverBackground.setFillColor(sf::Color(0xFF, 0xC0, 0x00));
    m_albumCoverBackground.setOutlineColor(sf::Color(0x2F, 0x55, 0x97));
    m_albumCoverBackground.setOutlineThickness(4);
}

void albumCoverRap::updateBallElements()
{
    const float dt = clock.restart().asSeconds();
    speed.y += dt * 9.8f;

    position += dt * speed;
    if ((position.y + 2 * 80 >= 380) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((position.y < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
    m_albumCoverBackground.setPosition(center + position);
    m_albumTitle.setPosition(center + position);
}

void albumCoverRap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_albumCoverBackground, states);
    target.draw(m_albumTitle, states);
}