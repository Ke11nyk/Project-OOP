#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <vector>

class GameMenu
{
	float menuX;
	float menuY;
	int menuStep;
	int maxMenu;
	int sizeFont;
	int mainMenuSelected;
	sf::Font font;
	std::vector<sf::Text> mainMenu;

	sf::Color menuTextColor = sf::Color::White;
	sf::Color chosenTextColor = sf::Color::Yellow;
	sf::Color borderColor = sf::Color::Black;


	void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos);

	sf::RenderWindow& mywindow;


public:
	GameMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String> name);

	void draw();
	void draw(int start, int end);

	void MoveUp();
	void MoveUp(int start, int end);

	void MoveDown();
	void MoveDown(int start, int end);

	void setColorTextMenu(sf::Color menuColor, sf::Color chosenColor, sf::Color bordColor);

	void AlignMenu(int posX);

	int getSelectedMenuNumber() const { return mainMenuSelected; }
};