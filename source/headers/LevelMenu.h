#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>

class LevelMenu
{
	float menuX;
	float menuY;
	int menuStepX;
	int menuStepY;
	int columns;
	int lines;
	int sizeFont;
	int mainMenuSelected;
	sf::Font font;
	sf::Text* mainMenu;

	sf::Color menuTextColor = sf::Color::White;
	sf::Color chosenTextColor = sf::Color::Yellow;
	sf::Color borderColor = sf::Color::Black;


	struct list
	{
		int num;
		sf::Text* column;
		list* right;
		list* left;
	};

	list* first = NULL;


	void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos);

	void addEl(list** first, int num, sf::Text column[]);

	sf::RenderWindow& mywindow;


public:
	LevelMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int stepx, int stepy, int lines, int columns);

	void draw();

	void MoveUp();

	void MoveDown();

	void setColorTextMenu(sf::Color menuColor, sf::Color chosenColor, sf::Color bordColor);

	int getSelectedMenuNumber() const { return mainMenuSelected; }
};