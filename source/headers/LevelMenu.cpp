#include "LevelMenu.h"

// text formatting
void LevelMenu::setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos)
{
	text.setFont(font);
	text.setFillColor(menuTextColor);
	text.setString(str);
	text.setCharacterSize(sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(borderColor);
}

void LevelMenu::addEl(list** first, int num, sf::Text column[])
{
	list* newList = new list;

	newList->column = column;
	newList->num = num;


	if (*first == NULL)
		*first = newList;
	else
	{
		list* current = *first;
		int i = 1;

		if (num == 1)
		{
			(*first)->left = newList;
			newList->right = *first;
			*first = newList;
		}
		else
		{
			while (i < num - 1 && current->right != NULL)
			{
				current = current->right;
				i++;
			}

			if (current->right == NULL)
			{
				current->right = newList;
				newList->left = current;
				newList->right = NULL;
			}
			else
			{
				newList->left = current;
				newList->right = current->right;
				current->right->left = newList;
				current->right = newList;
			}
		}
	}
}

LevelMenu::LevelMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int stepx, int stepy, int lines, int columns)
	:mywindow(window), menuX(menux), menuY(menuy), sizeFont(sizeFont), menuStepX(stepx), menuStepY(stepy)
{
	if (!font.loadFromFile("source/fontes/Gilroy-Heavy.woff")) exit(32);
	

	for (int j = 0, xpos = menuX; j < columns - 1; j++, xpos += menuStepX)
	{
		mainMenu = new sf::Text[lines];
		addEl(&first, j, mainMenu);

		for (int i = 0, ypos = menuY; i < lines - 1; i++, ypos += menuStepY)
			setInitText(mainMenu[i], std::to_string(i + i * columns), xpos, ypos);
	}
		
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
}

// moving through the menu
void LevelMenu::MoveUp()
{
	/*mainMenuSelected--;

	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
		mainMenu[mainMenuSelected + 1].setFillColor(menuTextColor);
	}
	else
	{
		mainMenu[0].setFillColor(menuTextColor);
		mainMenuSelected = maxMenu - 1;
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
	}*/
}

void LevelMenu::MoveDown()
{
	mainMenuSelected++;

	/*if (mainMenuSelected < maxMenu) {
		mainMenu[mainMenuSelected - 1].setFillColor(menuTextColor);
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
	}
	else
	{
		mainMenu[maxMenu - 1].setFillColor(menuTextColor);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
	}*/

}

// drawing menu items
void LevelMenu::draw()
{
	//for (int i = 0; i < maxMenu; i++) mywindow.draw(mainMenu[i]);

	if (first == NULL)
		return;
	else
	{
		list* current = first;

		while (current != NULL)
		{
			for (int i = 0; i < lines - 1; i++)
				mywindow.draw(current->column[i]);
		}
	}
}

// changing the color of the menu item
void LevelMenu::setColorTextMenu(sf::Color menuColor, sf::Color chosenColor, sf::Color bordColor)
{
	menuTextColor = menuColor;
	chosenTextColor = chosenColor;
	borderColor = bordColor;

	for (int j = 0; j < columns - 1; j++)
		for (int i = 0; i < lines - 1; i++) 
		{
		mainMenu[i].setFillColor(menuTextColor);
		mainMenu[i].setOutlineColor(borderColor);
		}

	if (first == NULL)
		return;
	else
	{
		list* current = first;

		while (current != NULL)
		{
			for (int i = 0; i < lines - 1; i++)
			{
				mainMenu[i].setFillColor(menuTextColor);
				mainMenu[i].setOutlineColor(borderColor);
			}
		}
	}

	mainMenu[mainMenuSelected].setFillColor(chosenTextColor);
}