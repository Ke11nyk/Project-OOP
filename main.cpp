#include <iostream>
#include "source/headers/Game.h"

/**
* \mainpage Project OOP
* This is documentation of a game about a stickman who needs to get to the door by jumping on platforms.
* 
* It is made as Project OOP and documentation is a part of Lab 1 of 2 semester.
* 
* For more information about this game see \ref UML "next page".
*/

int main()
{
    Game game;
    game.createWindow();
    game.mainloop();

    return 0;
}