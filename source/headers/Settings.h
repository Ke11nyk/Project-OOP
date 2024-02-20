#pragma once
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include "GameMenu.h"
#include "SettingsValues.h"
#include <iostream>
#include <fstream>
#include <vector>

class Settings
{
    //AssetManager manager;

    SettingsValues settingsValues;

    sf::Text TxtSettings;
    sf::RectangleShape RSBackground;

    // size of background
    int nBgWidth = settingsValues.getWidth();
    int nBgHeight = settingsValues.getHeight();

    // settings
    std::vector<sf::String> vecTitles = { "Run to exit", L"���� �� ������", "Start", L"�����", "Settings", L"������������", "About game", L"��� ���", "Exit", L"�����", "English", "English", L"���������", L"���������", "To menu", L"�� ����", "Language", L"����", "Character", L"��������", "Stickman", L"������",
        "Man", L"���", "To settings", L"�� �����������", "Points: ", L"����: ", "Time: ", L"���: ", "Screen", L"�����", "Fullscreen", L"������ �����", "level", L"�����",
                              L"���� �� ������",  L"�����", L"������������", L"��� ���", L"�����", "English", L"���������", L"�� ����", L"����", L"��������", L"������",
        L"���", L"�� �����������", L"����: ", L"���: ", L"�����", L"������ �����", L"�����" };

    std::vector<sf::String> vecSkin = { "source/images/figure.png", "source/images/figure1.png" };

    std::vector<sf::String> vecBackground = { "source/images/background.png" , "source/images/settings.png" , "source/images/about(1).png", "source/images/level1(1).png" };


    void InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr,
        int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor);
    void readValues(SettingsValues& settingValues, std::string sNameFile);
    void writeValues(const SettingsValues settingValues, const std::string& sNameFile);
    void clearValues(std::string sNameFile);

    
    void createMenu(sf::RenderWindow& WWin, GameMenu& myMenu);
    void Language(sf::RenderWindow& WWin);
    void Skin(sf::RenderWindow& WWin);
    void Screen(sf::RenderWindow& WWin);

public:
    void main(sf::RenderWindow& WWin);
};