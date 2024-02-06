#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <vector>

class GameMenu
{
	float fMenuX;
	float fMenuY;
	int nMenuStep;
	int nMaxMenu;
	int nSizeFont;
	int nMainMenuSelected;
	sf::Font FFont;
	std::vector<sf::Text> vecMainMenu;

	sf::Color ColMenuTextColor = sf::Color::White;
	sf::Color ColchosenTextColor = sf::Color::Yellow;
	sf::Color ColBorderColor = sf::Color::Black;


	void setInitText(sf::Text& TxtText, const sf::String& StrStr, float fXpos, float fYpos);

	sf::RenderWindow& WMywindow;


public:
	GameMenu(sf::RenderWindow& WWindow, float fMenux, float fMenuy, int nSizeFont, int nStep, std::vector<sf::String> vecName);

	void draw();
	void draw(int fStart, int fEnd);

	void MoveUp();
	void MoveUp(int fStart, int fEnd);

	void MoveDown();
	void MoveDown(int fStart, int fEnd);

	void setColorTextMenu(sf::Color ColMenuColor, sf::Color ColChosenColor, sf::Color ColBordColor);

	void AlignMenu(int nPosX);

	int getSelectedMenuNumber() const { return nMainMenuSelected; }
};