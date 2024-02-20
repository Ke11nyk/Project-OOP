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
    std::vector<sf::String> vecTitles = { "Run to exit", L"Біжи до виходу", "Start", L"Старт", "Settings", L"Налаштування", "About game", L"Про гру", "Exit", L"Вихід", "English", "English", L"Українська", L"Українська", "To menu", L"До меню", "Language", L"Мова", "Character", L"Персонаж", "Stickman", L"Стікмен",
        "Man", L"Поц", "To settings", L"До налаштувань", "Points: ", L"Очки: ", "Time: ", L"Час: ", "Screen", L"Екран", "Fullscreen", L"Повний екран", "level", L"рівень",
                              L"Біжи до виходу",  L"Старт", L"Налаштування", L"Про гру", L"Вихід", "English", L"Українська", L"До меню", L"Мова", L"Персонаж", L"Стікмен",
        L"Поц", L"До налаштувань", L"Очки: ", L"Час: ", L"Екран", L"Повний екран", L"рівень" };

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