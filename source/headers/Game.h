#pragma once
#include "Sprite.h"
#include "SFML/Graphics.hpp"

class Game
{
    sf::RenderWindow win;
    sf::Image icon;
    sf::Texture textureWall;
    sf::Font font;
    sf::Text Title;

    void InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, 
        int sizeFont, sf::Color menuTextColor, int bord, sf::Color borderColor);
    void GameStart();
    void Options();
    void AboutGame();

public:
    int mainloop();
};
