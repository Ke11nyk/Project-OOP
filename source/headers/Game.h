#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GameMenu.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Player.h"
#include <iostream>


class Game
{
    AssetManager manager;

    sf::String Titles[30] = { "Run to exit", "Start", "Settings", "About game", "Exit", "Game", L"Гра", "To menu", "Lang", "Character", "Stic", "Man", "To settings", "Points: ", "Time: ",
                              L"Біжи до виходу",  L"Старт", L"Налаштування", L"Про гру", L"Вихід", "Game", L"Гра", L"До меню", L"Мова", L"Персонаж", L"Стік", L"Поц", L"До налаштувань", L"Очки: ", L"Час: "};

    sf::String Ab[2] = {"A game about a stickman who needs to get to the door by \njumping on platforms.\
 Originally implemented in Python, the \ncurrent implementation is in C++ using the SFML library. \n\n\
Currently, a static level is implemented. \nRandomization of levels, endless mode are planned. \
    \n\nMade by Artem Verbytskyi as part of a project for OOOP \
    \n\n\n\n\nCopyright © 2023 by Ke11nyk", L"Гра про стікмена, якому потрібно дістатися до дверей, \nстрибаючи по платформам\
  Спочатку реалізовано на Python, \nпоточна реалізація на C++ з використанням бібліотеки SFML. \n\n\
На даний момент реалізований статичний рівень. \nПланується рандомізація рівнів, нескінченний режим. \
     \n\nВиконано Артемом Вербицьким в рамках проекту для ОООП \
     \n\n\n\n\nCopyright © 2023 by Ke11nyk" };

    sf::String Pers[2] = { "source/images/figure.png", "source/images/figure(1).png" };

    int language = 0;
    int about = 0;
    int pers = 0;

    // main window
    sf::RenderWindow win;
    sf::Image icon;
    sf::RectangleShape background;
    sf::Text Title;

    //other windows
    sf::Text Set;
    sf::Text About;

    float setTitle = 573;

    sf::RectangleShape backgroundSet;

    // player
    Player stick = Player(win, TileMap, Pers[pers]);
    sf::Time tm;
    sf::Sprite PlayerSprite;
    Animator PlayerAnim = Animator(PlayerSprite);

    sf::Text Points;
    int points = 0;

    sf::Text Time;
    sf::Time time;
    float timeM = 0;
    float timeS = 0;

    // map of level
    sf::Sprite plat;

    float offsetX = 0, offsetY = 0;

    int const static H = 22;
    int const static W = 39;

    int const static ts = 50;

    sf::String TileMap[H] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                                     A",
    "A                AAA                  A",
    "A                     AAAA            A",
    "AAAAA    oooo   AAA                   A",
    "A                                     A",
    "A       AAAAAA                        A",
    "A                                     A",
    "AAAAA                                 A",
    "A                     oooooo          A",
    "A              AAAA                   A",
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    };

    // size of window
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    void InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, 
        int sizeFont, sf::Color menuTextColor, int bord, sf::Color borderColor);
    void GameStart();
    void Settings();
    void SettingsLanguage();
    void SettingsPers();
    void AboutGame();
    void input();
    void update(sf::Time const& deltaTime);
    void mainloop();
    

public:
    void CreateWindow();

    void drawMap();

    int getH()
    {
        return H;
    }

    int getW()
    {
        return W;
    }

    int getPoints()
    {
        return points;
    }

    void setPoints(int value)
    {
        points = value;
    }

    float getTimeM()
    {
        return timeM;
    }

    void setTimeM(int value)
    {
        timeM = value;
    }

    float getTimeS()
    {
        return timeS;
    }

    void setTimeS(int value)
    {
        timeS = value;
    }

    void setOffsetX(float x)
    {
        offsetX = x;
    }

    void setOffsetY(float y)
    {
        offsetY = y;
    }

    sf::String* getTileMap()
    {
        return TileMap;
    }
};
