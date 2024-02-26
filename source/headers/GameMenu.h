#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <vector>

/**
* \brief This is the class to create menu
*/
class GameMenu
{
	float fMenuX; ///< X-coordinates of menu
	float fMenuY; ///< Y-coordinates of menu
	int nMenuStep; ///< Distance between menu options
	int nMaxMenu; ///< Number of options
	int nSizeFont; ///< Font size
	int nMainMenuSelected; ///< Selected option
	sf::Font FFont; ///< Font
	std::vector<sf::Text> vecMainMenu; ///< Titles of options

	sf::Color ColMenuTextColor = sf::Color::White; ///< Color of the options' titles
	sf::Color ColchosenTextColor = sf::Color::Yellow; ///< Color of chosen option
	sf::Color ColBorderColor = sf::Color::Black; ///< Color of border of options

	sf::RenderWindow& WMywindow; ///< Window where menu will be displayed

	void setInitText(sf::Text& TxtText, const sf::String& StrStr, float fXpos, float fYpos);


public:
	GameMenu(sf::RenderWindow& WWindow, float fMenux, float fMenuy, int nSizeFont, int nStep, std::vector<sf::String> vecName);

	void Draw();
	void Draw(int nStart, int nEnd);

	void MoveUp();
	void MoveUp(int nStart, int nEnd);

	void MoveDown();
	void MoveDown(int nStart, int nEnd);

	void setColorTextMenu(sf::Color ColMenuColor, sf::Color ColChosenColor, sf::Color ColBordColor);

	void AlignMenu(int nPosX);

	int getSelectedMenuNumber() const { return nMainMenuSelected; }
};