#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GameMenu.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Player.h"
#include "SettingsValues.h"
#include <fstream>

class Gameplay
{
    // settings
    std::vector<sf::String> vecTitles = { "level", L"рівень", "Press escape to return to the main menu", 
        L"Натисніть escape, аби повернутися до головного меню", 
        "If you exit, your progress\nwill not be saved\n\nPress escape to exit\nor space to return",
        L"Якщо ви зараз вийдете,\nви втратите прогрес\n\nНажміть escape для виходу\nspace, щоб повернутися",
        "Your score is: ", L"Ваш рахунок: ", "\nYour time is:\n", L"\nВаш час:\n", " minutes ",
        L" хвилин ", " seconds\n\nPress escape to exit", L" секунд\n\nНажміть escape для виходу" };

    std::vector<sf::String> vecSkin = { "source/images/figure.png", "source/images/figure1.png" };

    std::vector<sf::String> vecBackground = { "source/images/background.png" , "source/images/settings.png" , "source/images/about(1).png", "source/images/level1(1).png" };

    std::vector<sf::String> vecTexture = { "source/images/plat.png", "source/images/plat1.png", "source/images/door.png", "source/images/door1.png" };

    SettingsValues settingsValues;

    sf::RectangleShape RSBackground;

    bool bGameplayState = true;

    // other windows
    sf::Text TxtSettings;

    // player
    sf::Time TTm;
    sf::Sprite SPlayerSprite;
    Animator PlayerAnim = Animator(SPlayerSprite);

    int nPoints = 0;

    // states of game
    bool bPreEx = false;
    bool bEndLevel = false;
    bool bDoorOpened = false;

    // map of level
    sf::Sprite SPlat;
    sf::Sprite SDoor;

    int nTs = 50;

    std::vector<sf::String> vecTileMap;

    // camera
    float fOffsetX = 0, fOffsetY = 0;

    // size of window
    int nWidth = sf::VideoMode::getDesktopMode().width;
    int nHeight = sf::VideoMode::getDesktopMode().height;

    // size of background
    int nBgWidth = settingsValues.getWidth();
    int nBgHeight = settingsValues.getHeight();

    sf::RenderWindow& WWin;


    void InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr,
        int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor);
    void input(Player& stick, bool& bGameplayState);
    void update(sf::Time const& TDeltaTime, Player& stick);
    void Camera(Player& stick, std::vector<sf::String> vecTileMap);
    void drawMap(std::vector<sf::String> vecTileMap, int nSize);
    void readMap(std::vector<sf::String>& vecTileMap, int nLevel);
    void readValues(SettingsValues& settingValues, std::string sFileName);
    void Level();
    void preExit();
    void endOfTheLevel(int nStart, int& nFinish, sf::Clock CTimer, bool& bTimer);


public:
    Gameplay(sf::RenderWindow& WWindow);

	void LevelMenu();

    int getPoints()
    {
        return nPoints;
    }

    void setPoints(int nValue)
    {
        nPoints = nValue;
    }

    void setOffsetX(float fX)
    {
        fOffsetX = fX;
    }

    float getOffsetX()
    {
        return fOffsetX;
    }

    void setOffsetY(float fY)
    {
        fOffsetY = fY;
    }

    float getOffsetY()
    {
        return fOffsetY;
    }

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

    void setTs(int nValue)
    {
        nTs = nValue;
    }

    int getTs()
    {
        return nTs;
    }

    void setDoorOpened(bool bValue)
    {
        bDoorOpened = bValue;
    }

    bool getDoorOpened()
    {
        return bDoorOpened;
    }

    void setPreEx(bool bValue)
    {
        bPreEx = bValue;
    }

    bool getPreEx()
    {
        return bPreEx;
    }

    void setEndLevel(bool bValue)
    {
        bEndLevel = bValue;
    }

    bool getEndLevel()
    {
        return bEndLevel;
    }
};