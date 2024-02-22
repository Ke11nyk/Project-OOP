#include "../headers/GameMenu.h"

// text formatting
void GameMenu::setInitText(sf::Text& TxtText, const sf::String& StrStr, float fXpos, float fYpos) 
{
	TxtText.setString(StrStr);
	TxtText.setFont(FFont);
	TxtText.setFillColor(ColMenuTextColor);
	TxtText.setCharacterSize(nSizeFont);
	TxtText.setPosition(fXpos, fYpos);
	TxtText.setOutlineThickness(3);
	TxtText.setOutlineColor(ColBorderColor);
}

// choice of placement of menu items
void GameMenu::AlignMenu(int nPosX)
{
	float fNullx = 0;

	for (int i = 0; i < nMaxMenu; i++) {

		switch (nPosX)
		{
		case 0:
			fNullx = 0;
			break;
		case 1:
			fNullx = vecMainMenu[i].getLocalBounds().width;
			break;
		case 2:
			fNullx = vecMainMenu[i].getLocalBounds().width / 2;
			break;
		default:break;
		}

		vecMainMenu[i].setPosition(vecMainMenu[i].getPosition().x - fNullx, vecMainMenu[i].getPosition().y);
	}

}
  
GameMenu::GameMenu(sf::RenderWindow& WWindow, float fMenux, float fMenuy, int nSizeFont, int nStep, std::vector<sf::String> vecName)
	:WMywindow(WWindow), fMenuX(fMenux), fMenuY(fMenuy), nSizeFont(nSizeFont), nMenuStep(nStep)
{
	if (!FFont.loadFromFile("source/fontes/Gilroy-Heavy.woff")) exit(32);
	nMaxMenu = vecName.size();
	sf::Text TxtText;
	vecMainMenu.assign(nMaxMenu, TxtText);

	for (int i = 0, fYpos = fMenuY, fXpos = fMenuX; i < nMaxMenu; i++, fYpos += nMenuStep)
		setInitText(vecMainMenu[i], vecName[i], fXpos, fYpos);

	nMainMenuSelected = 0;
	vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
}


// moving through the menu
void GameMenu::MoveUp()
{
	nMainMenuSelected--;

	if (nMainMenuSelected >= 0) {
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
		vecMainMenu[nMainMenuSelected + 1].setFillColor(ColMenuTextColor);
	}
	else
	{
		vecMainMenu[0].setFillColor(ColMenuTextColor);
		nMainMenuSelected = nMaxMenu - 1;
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
	}
}

void GameMenu::MoveUp(int nStart, int nEnd)
{
	nMainMenuSelected--;

	if (nMainMenuSelected >= nStart) {
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
		vecMainMenu[nMainMenuSelected + 1].setFillColor(ColMenuTextColor);
	}
	else
	{
		vecMainMenu[1].setFillColor(ColMenuTextColor);
		nMainMenuSelected = nEnd - 1;
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
	}
}

void GameMenu::MoveDown()
{
	nMainMenuSelected++;

	if (nMainMenuSelected < nMaxMenu) {
		vecMainMenu[nMainMenuSelected - 1].setFillColor(ColMenuTextColor);
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
	}
	else
	{
		vecMainMenu[nMaxMenu - 1].setFillColor(ColMenuTextColor);
		nMainMenuSelected = 0;
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
	}

}

void GameMenu::MoveDown(int nStart, int nEnd)
{
	nMainMenuSelected++;

	if (nMainMenuSelected < nEnd) {
		vecMainMenu[nMainMenuSelected - 1].setFillColor(ColMenuTextColor);
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
	}
	else
	{
		vecMainMenu[nEnd - 1].setFillColor(ColMenuTextColor);
		nMainMenuSelected = nStart;
		vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
	}

}

// drawing menu items
void GameMenu::draw()
{
	for (int i = 0; i < nMaxMenu; i++) WMywindow.draw(vecMainMenu[i]);
}

void GameMenu::draw(int nStart, int nEnd)
{
	for (int i = nStart; i < nEnd; i++) WMywindow.draw(vecMainMenu[i]);
}

// changing the color of the menu item
void GameMenu::setColorTextMenu(sf::Color ColMenuColor, sf::Color ColChosenColor, sf::Color ColBordColor)
{
	ColMenuTextColor = ColMenuColor;
	ColchosenTextColor = ColChosenColor;
	ColBorderColor = ColBordColor;

	for (int i = 0; i < nMaxMenu; i++) {
		vecMainMenu[i].setFillColor(ColMenuTextColor);
		vecMainMenu[i].setOutlineColor(ColBorderColor);
	}

	vecMainMenu[nMainMenuSelected].setFillColor(ColchosenTextColor);
}