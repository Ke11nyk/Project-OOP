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


class Game
{
    AssetManager manager;

    // settings
    SettingsValues settingsValues;
    std::vector<sf::String> vecTitles = { "Run to exit", L"���� �� ������", "Start", L"�����", "Settings", L"������������", "About game", L"��� ���", "Exit", L"�����", "English", "English", L"���������", L"���������", "To menu", L"�� ����", "Language", L"����", "Character", L"��������", "Stickman", L"������", 
        "Man", L"���", "To settings", L"�� �����������", "Points: ", L"����: ", "Time: ", L"���: ", "Screen", L"�����", "Fullscreen", L"������ �����", "level", L"�����",
                              L"���� �� ������",  L"�����", L"������������", L"��� ���", L"�����", "English", L"���������", L"�� ����", L"����", L"��������", L"������", 
        L"���", L"�� �����������", L"����: ", L"���: ", L"�����", L"������ �����", L"�����"};
    std::vector<sf::String> vecAbout = {"A game about a stickman who needs to get to the door by \njumping on platforms.\
 Originally implemented in Python, the \ncurrent implementation is in C++ using the SFML library. \n\n\
Currently, a static level is implemented. \nRandomization of levels, endless mode are planned. \
    \n\nMade by Artem Verbytskyi as part of a project for OOOP \
    \n\n\n\n\nCopyright � 2023 by Ke11nyk", L"��� ��� �������, ����� ������� �������� �� ������, \n��������� �� ����������\
  �������� ���������� �� Python, \n������� ��������� �� C++ � ������������� �������� SFML. \n\n\
�� ����� ������ ����������� ��������� �����. \n��������� ����������� �����, ����������� �����. \
     \n\n�������� ������� ���������� � ������ ������� ��� ���� \
     \n\n\n\n\nCopyright � 2023 by Ke11nyk" };
    std::vector<sf::String> vecBackground = { "source/images/background.png" , "source/images/settings.png" , "source/images/about(1).png", "source/images/level1(1).png" };
    std::vector<sf::String> vecTexture = { "source/images/plat.png", "source/images/plat1.png", "source/images/door.png", "source/images/door1.png" };

    // window
    sf::RenderWindow WWin;
    sf::RectangleShape RSBackground;

    // size of window
    int nWidth = sf::VideoMode::getDesktopMode().width;
    int nHeight = sf::VideoMode::getDesktopMode().height;

    // size of background
    int nBgWidth = settingsValues.getWidth();
    int nBgHeight = settingsValues.getHeight();


    void InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr, 
        int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor);
    void readValues(SettingsValues& settingValues, std::string sNameFile);
    void writeValues(const SettingsValues settingValues, const std::string& sNameFile);
    void clearValues(std::string sNameFile);

    void SettingsWindow(sf::Text& TxtSettings, GameMenu& myMenu);
    void Settings();
    void SettingsLanguage();
    void SettingsPers();
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
