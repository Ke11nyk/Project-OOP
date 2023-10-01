#include "Game.h"

int Game::mainloop()
{
    RenderWindow win(sf::VideoMode(1280, 720), "Stickman");

    if (!icon.loadFromFile("source/images/icon.png"))
    {
        return 1;
    }
    win.setIcon(32, 32, icon.getPixelsPtr());

    textureWall.loadFromFile("source/images/background.png");
    RectangleShape gamingBackground(Vector2f(1280, 720));
    gamingBackground.setTexture(&textureWall);

    while (win.isOpen())
    {
        Event event;
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
                win.close();
        }

        win.clear();
        win.draw(gamingBackground);
        win.display();
    }
}