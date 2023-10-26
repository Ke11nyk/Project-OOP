#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class LevelMenu
{
	float menuX;
	float menuY;
	int stepx;
	int stepy;
	int lines;
	int columns;
	int sizeFont;
	int mainMenuSelected;
	sf::Font font;
	sf::Text* mainMenu;

	sf::Color menuTextColor = sf::Color::White;
	sf::Color chosenTextColor = sf::Color::Yellow;
	sf::Color borderColor = sf::Color::Black;


	void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos);

	sf::RenderWindow& mywindow;

	int const static H = 22;

	struct level
	{
		int num;
		sf::String numText;
		level* left;
		level* right;
	};

	void addLevel(level* nod, int dataNum);


public:
	LevelMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int stepx, int stepy, int lines, int column, sf::String name[]);

	void draw();

	void MoveUp();

	void MoveDown();

	void setColorTextMenu(sf::Color menuColor, sf::Color chosenColor, sf::Color bordColor);

	void AlignMenu(int posX);

	int getSelectedMenuNumber() const { return mainMenuSelected; }
};