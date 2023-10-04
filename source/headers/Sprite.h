#pragma once
#include "SFML/Graphics.hpp"

class Sprite
{
	sf::Texture texplayer;
public:
	sf::RectangleShape getSprite(sf::RenderWindow* window, float x, float y);
};