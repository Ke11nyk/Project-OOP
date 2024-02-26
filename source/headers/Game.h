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
    std::vector<sf::String> vecTitles = { "Run to exit", L"���� �� ������", "Start", L"�����", "Settings", L"������������", "About game", L"��� ���", "Exit", L"�����", "English", "English", L"���������", L"���������", "To menu", L"�� ����", "Language", L"����", "Character", L"��������", "Stickman", L"������", 
        "Man", L"���", "To settings", L"�� �����������", "Points: ", L"����: ", "Time: ", L"���: ", "Screen", L"�����", "Fullscreen", L"������ �����", "level", L"�����",
                              L"���� �� ������",  L"�����", L"������������", L"��� ���", L"�����", "English", L"���������", L"�� ����", L"����", L"��������", L"������", 
        L"���", L"�� �����������", L"����: ", L"���: ", L"�����", L"������ �����", L"�����"}; ///< Vector of titles
    std::vector<sf::String> vecAbout = {"A game about a stickman who needs to get to the door by \njumping on platforms.\
 Originally implemented in Python, the \ncurrent implementation is in C++ using the SFML library. \n\n\
Currently, a static level is implemented. \nRandomization of levels, endless mode are planned. \
    \n\nMade by Artem Verbytskyi as part of a project for OOOP \
    \n\n\n\n\nCopyright � 2023 by Ke11nyk", L"��� ��� �������, ����� ������� �������� �� ������, \n��������� �� ����������\
  �������� ���������� �� Python, \n������� ��������� �� C++ � ������������� �������� SFML. \n\n\
�� ����� ������ ����������� ��������� �����. \n��������� ����������� ����, ����������� �����. \
     \n\n�������� ������� ���������� � ������ ������� ��� ���� \
     \n\n\n\n\nCopyright � 2023 by Ke11nyk" }; ///< Vector with about game text
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
