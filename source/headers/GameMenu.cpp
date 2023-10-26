#include "GameMenu.h"

// text formatting
void GameMenu::setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) 
{
	text.setFont(font);
	text.setFillColor(menuTextColor);
	text.setString(str);
	text.setCharacterSize(sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(borderColor);
}

// choice of placement of menu items
void GameMenu::AlignMenu(int posX)
{
	float nullx = 0;

	for (int i = 0; i < maxMenu; i++) {

		switch (posX)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;
			break;
		case 2:
			nullx = mainMenu[i].getLocalBounds().width / 2;
			break;
		default:break;
		}

		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}

}

GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, sf::String name[])
	:mywindow(window), menuX(menux), menuY(menuy), sizeFont(sizeFont), menuStep(step)
{
	if (!font.loadFromFile("source/fontes/Gilroy-Heavy.woff")) exit(32);
	maxMenu = name->getSize() - 1;
	mainMenu = new sf::Text[name->getSize()];

	for (int i = 0, ypos = menuY; i < maxMenu; i++, ypos += menuStep)
		setInitText(mainMenu[i], name[i], menuX, ypos);
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
}

// moving through the menu
void GameMenu::MoveUp()
{
	mainMenuSelected--;

	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
		mainMenu[mainMenuSelected + 1].setFillColor(menuTextColor);
	}
	else
	{
		mainMenu[0].setFillColor(menuTextColor);
		mainMenuSelected = maxMenu - 1;
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
	}
}

void GameMenu::MoveDown()
{
	mainMenuSelected++;

	if (mainMenuSelected < maxMenu) {
		mainMenu[mainMenuSelected - 1].setFillColor(menuTextColor);
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
	}
	else
	{
		mainMenu[maxMenu - 1].setFillColor(menuTextColor);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
	}

}

// drawing menu items
void GameMenu::draw()
{
	for (int i = 0; i < maxMenu; i++) mywindow.draw(mainMenu[i]);
}

// changing the color of the menu item
void GameMenu::setColorTextMenu(sf::Color menuColor, sf::Color chosenColor, sf::Color bordColor)
{
	menuTextColor = menuColor;
	chosenTextColor = chosenColor;
	borderColor = bordColor;

	for (int i = 0; i < maxMenu; i++) {
		mainMenu[i].setFillColor(menuTextColor);
		mainMenu[i].setOutlineColor(borderColor);
	}

	mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
}
