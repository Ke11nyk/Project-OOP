#pragma once

#include "SFML/Graphics.hpp"
using namespace sf;

class Game
{

private:
    Image icon;
    Texture textureWall;

public:
    int mainloop();
};
