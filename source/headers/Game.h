#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GameMenu.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Player.h"
#include "SettingsValues.h"
#include "Gameplay.h"
#include <iostream>
#include <vector>
#include <fstream>

/**
* \brief This is the main class of the program
*/
class Game
{
    AssetManager manager; ///< A single copy of the asset manager 

    // settings
    SettingsValues settingsValues; ///< Struct for saving settings values
    std::vector<sf::String> vecTitles = { "Run to exit", L"Біжи до виходу", "Start", L"Старт", "Settings", L"Налаштування", "About game", L"Про гру", "Exit", L"Вихід", "English", "English", L"Українська", L"Українська", "To menu", L"До меню", "Language", L"Мова", "Character", L"Персонаж", "Stickman", L"Стікмен", 
        "Man", L"Поц", "To settings", L"До налаштувань", "Points: ", L"Очки: ", "Time: ", L"Час: ", "Screen", L"Екран", "Fullscreen", L"Повний екран", "level", L"рівень",
                              L"Біжи до виходу",  L"Старт", L"Налаштування", L"Про гру", L"Вихід", "English", L"Українська", L"До меню", L"Мова", L"Персонаж", L"Стікмен", 
        L"Поц", L"До налаштувань", L"Очки: ", L"Час: ", L"Екран", L"Повний екран", L"рівень"}; ///< Vector of titles
    std::vector<sf::String> vecAbout = {"A game about a stickman who needs to get to the door by \njumping on platforms.\
 Originally implemented in Python, the \ncurrent implementation is in C++ using the SFML library. \n\n\
Currently, a static level is implemented. \nRandomization of levels, endless mode are planned. \
    \n\nMade by Artem Verbytskyi as part of a project for OOOP \
    \n\n\n\n\nCopyright © 2023 by Ke11nyk", L"Гра про стікмена, якому потрібно дістатися до дверей, \nстрибаючи по платформам\
  Спочатку реалізовано на Python, \nпоточна реалізація на C++ з використанням бібліотеки SFML. \n\n\
На даний момент реалізований статичний рівень. \nПланується рандомізація рівнів, нескінченний режим. \
     \n\nВиконано Артемом Вербицьким в рамках проекту для ОООП \
     \n\n\n\n\nCopyright © 2023 by Ke11nyk" }; ///< Vector with about game text
    std::vector<sf::String> vecBackground = { "source/images/background.png" , 
        "source/images/settings.png" , "source/images/about(1).png", "source/images/level1(1).png" }; ///< Vector of background sources
    
    // window
    sf::RenderWindow WWin; ///< Window of the game
    sf::RectangleShape RSBackground; ///< Background of the window

    // size of window
    int nWidth = sf::VideoMode::getDesktopMode().width; ///< Width of the window
    int nHeight = sf::VideoMode::getDesktopMode().height; ///< Height of the window

    // size of background
    int nBgWidth = settingsValues.getWidth(); ///< Width of the background
    int nBgHeight = settingsValues.getHeight(); ///< Height of the background


    void InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr, 
        int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor);
    void ReadValues(SettingsValues& settingValues, std::string sNameFile);
    void WriteValues(const SettingsValues settingValues, const std::string& sNameFile);
    void ClearValues(std::string sNameFile);

    void SettingsWindow(sf::Text& TxtSettings, GameMenu& myMenu);
    void Settings();
    void SettingsLanguage();
    void SettingsSkin();
    void SettingsScreen();

    void AboutGame();

  
public:
    void createWindow();
    void mainloop();
    

    void setWidth(int nValue)
    {
        nWidth = nValue;
    }

    int getWidth()
    {
        return nWidth;
    }

    void setHeight(int nValue)
    {
        nHeight = nValue;
    }

    int getHeight()
    {
        return nHeight;
    }
};
