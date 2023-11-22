#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GameMenu.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Player.h"
#include "Levelmenu.h"
#include <iostream>
#include <vector>
#include <fstream>


class Game
{
    AssetManager manager;

    std::vector<sf::String> Titles = { "Run to exit", "Start", "Settings", "About game", "Exit", "English", L"Українська", "To menu", "Language", "Character", "Stickman", "Man", "To settings", "Points: ", "Time: ", "Screen", "Fullscreen", "level",
                              L"Біжи до виходу",  L"Старт", L"Налаштування", L"Про гру", L"Вихід", "English", L"Українська", L"До меню", L"Мова", L"Персонаж", L"Стікмен", L"Поц", L"До налаштувань", L"Очки: ", L"Час: ", L"Екран", L"Повний екран", L"рівень"};

    std::vector<sf::String> Ab = {"A game about a stickman who needs to get to the door by \njumping on platforms.\
 Originally implemented in Python, the \ncurrent implementation is in C++ using the SFML library. \n\n\
Currently, a static level is implemented. \nRandomization of levels, endless mode are planned. \
    \n\nMade by Artem Verbytskyi as part of a project for OOOP \
    \n\n\n\n\nCopyright © 2023 by Ke11nyk", L"Гра про стікмена, якому потрібно дістатися до дверей, \nстрибаючи по платформам\
  Спочатку реалізовано на Python, \nпоточна реалізація на C++ з використанням бібліотеки SFML. \n\n\
На даний момент реалізований статичний рівень. \nПланується рандомізація рівнів, нескінченний режим. \
     \n\nВиконано Артемом Вербицьким в рамках проекту для ОООП \
     \n\n\n\n\nCopyright © 2023 by Ke11nyk" };

    std::vector<sf::String> Pers = { "source/images/figure.png", "source/images/figure1.png" };

    std::vector<sf::String> Bg = { "source/images/background.png" , "source/images/settings.png" , "source/images/about(1).png", "source/images/level1(1).png" };

    std::vector<sf::String> Texture = { "source/images/plat.png", "source/images/plat1.png" };

    int language = 0;
    int about = 0;
    int pers = 0;

    // main window
    sf::RenderWindow win;
    sf::Image icon;
    sf::RectangleShape background;
    sf::Text Title;
    bool fullscreen = false;

    // other windows
    sf::Text Set;
    sf::Text About;

    float setTitle = 573;

    sf::RectangleShape backgroundSet;

    // player
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

    int ts = 50;

    sf::String TileMap[H];

    // size of window
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;

    int bgWidth = 1920;
    int bgHeight = 1080;


    void InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, 
        int sizeFont, sf::Color menuTextColor, int bord, sf::Color borderColor);
    void LevelMenu();
    void Level();
    void Settings();
    void SettingsLanguage();
    void SettingsPers();
    void SettingsScreen();
    void AboutGame();
    void input(Player& stick, bool& preEx);
    void update(sf::Time const& deltaTime, Player& stick);
    void drawMap(sf::String TileMap[H], int size);
    void readMap(sf::String TileMap[H], int level);
    void preExit();
    

public:
    void CreateWindow();
    void mainloop();
    

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

    float getOffsetX()
    {
        return offsetX;
    }

    void setOffsetY(float y)
    {
        offsetY = y;
    }

    float getOffsetY()
    {
        return offsetY;
    }

    void setWidth(int value)
    {
        width = value;
    }

    int getWidth()
    {
        return width;
    }

    void setHeight(int value)
    {
        height = value;
    }

    int getHeight()
    {
        return height;
    }

    void setFullscreen(bool value)
    {
        fullscreen = value;
    }

    bool getFullscreen()
    {
        return fullscreen;
    }

    void setTs(int value)
    {
        ts = value;
    }

    int getTs()
    {
        return ts;
    }
};
