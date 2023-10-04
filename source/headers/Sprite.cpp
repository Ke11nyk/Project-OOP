#include "Sprite.h"

sf::RectangleShape Sprite::getSprite(sf::RenderWindow* window, float x, float y)
{
    sf::RenderWindow& win = *window;

    sf::Vector2f moveRec;
    sf::Vector2f pos;

    sf::Clock clock;
    float time, timePlayer;

    texplayer.loadFromFile("source/images/figure-R3.png");
    sf::RectangleShape player(sf::Vector2f(54, 60));
    player.setTexture(&texplayer);
    player.setPosition(sf::Vector2f(x, y));

    sf::Event event;

    time = clock.getElapsedTime().asMicroseconds();
    timePlayer = time / 2000;
    clock.restart();

    while (win.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::S) moveRec.y = 1 * timePlayer;
            if (event.key.code == sf::Keyboard::W) moveRec.y = -1 * timePlayer;
            if (event.key.code == sf::Keyboard::D) moveRec.x = 1 * timePlayer;
            if (event.key.code == sf::Keyboard::A) moveRec.x = -1 * timePlayer;
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::S) moveRec.y = 0;
            if (event.key.code == sf::Keyboard::W) moveRec.y = 0;
            if (event.key.code == sf::Keyboard::D) moveRec.x = 0;
            if (event.key.code == sf::Keyboard::A) moveRec.x = 0;
            break;
        default:
            break;
        }
    }

    player.move(moveRec);
    pos = player.getPosition();
    if (pos.x > 1200) player.setPosition(1200, pos.y);
    if (pos.x < 54) player.setPosition(54, pos.y);
    if (pos.y > 640) player.setPosition(pos.x, 640);
    if (pos.y < 120) player.setPosition(pos.x, 120);

    if ((pos.x > 1200) && (pos.y < 120)) player.setPosition(1200, 120);
    if ((pos.x > 1200) && (pos.y > 640)) player.setPosition(1200, 640);
    if ((pos.x < 54) && (pos.y < 120)) player.setPosition(54, 120);
    if ((pos.x < 54) && (pos.y > 640)) player.setPosition(54, 640);

    return player;
}