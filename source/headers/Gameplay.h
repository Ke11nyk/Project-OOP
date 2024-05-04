#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GameMenu.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Player.h"
#include "SettingsValues.h"
#include "GameSound.h"
#include <fstream>

/**
* \brief This is the class to create the actual game
*/
class Gameplay
{
    // settings
    std::vector<sf::String> vecTitles = { "level", L"рівень", "Press escape to return to the main menu", 
        L"Натисніть escape, аби повернутися до головного меню", 
        "If you exit, your progress\nwill not be saved\n\nPress escape to exit\nor space to return",
        L"Якщо ви зараз вийдете,\nви втратите прогрес\n\nНажміть escape для виходу\nspace, щоб повернутися",
        "Your score is: ", L"Ваш рахунок: ", "\nYour time is:\n", L"\nВаш час:\n", " minutes ",
        L" хвилин ", " seconds\n\nPress escape to exit", L" секунд\n\nНажміть escape для виходу" }; ///< Vector of titles
    std::vector<sf::String> vecSkin = { "source/images/figure.png", "source/images/figure1.png" }; ///< Vector of skin sources
    std::vector<sf::String> vecBackground = { "source/images/background.png" , 
        "source/images/settings.png" , "source/images/about(1).png", "source/images/level1(1).png" }; ///< Vector of background sources
    std::vector<sf::String> vecTexture = { "source/images/plat.png", 
        "source/images/plat1.png", "source/images/door.png", "source/images/door1.png" }; ///< Vector of texture sources

    SettingsValues settingsValues; ///< Struct for saving settings values

    sf::RectangleShape RSBackground; ///< Background of the window

    sf::RenderWindow& WWin; ///< Window of the game

    GameSound& gameSound;

    // player
    sf::Time TTm; ///< The update time
    sf::Sprite SPlayerSprite; ///< Sprite of the player
    Animator PlayerAnim = Animator(SPlayerSprite); ///< Animation of the player
    int nPoints = 0; ///< Points number of the player

    // states of game
    bool bGameplayState = true; ///< State to exit current game
    bool bPreEx = false; ///< State to show exit window
    bool bEndLevel = false; ///< State to end current game
    bool bDoorOpened = false; ///< State of the door

    // map of level
    sf::Sprite SPlat; ///< Sprite of the plate
    sf::Sprite SDoor; ///< Sprite of the door
    int nTs = 50; ///< Size of the plate
    std::vector<sf::String> vecTileMap; ///< Map of the level

    // camera
    float fOffsetX = 0; ///< X-delta of the camera
    float fOffsetY = 0; ///< Y-delta of the camera

    // size of window
    int nWidth = sf::VideoMode::getDesktopMode().width; ///< Width of the window
    int nHeight = sf::VideoMode::getDesktopMode().height; ///< Height of the window

    // size of background
    int nBgWidth = settingsValues.getWidth(); ///< Width of the background
    int nBgHeight = settingsValues.getHeight(); ///< Height of the background


    void InitText(sf::Text& TxtMtext, float fXpos, float fYpos, const sf::String StrStr,
        int nSizeFont, sf::Color ColMenuTextColor, int nBord, sf::Color ColBorderColor);
    void Input(Player& stick, bool& bGameplayState);
    void Update(sf::Time const& TDeltaTime, Player& stick);
    void Camera(Player& stick, std::vector<sf::String> vecTileMap);
    void DrawMap(std::vector<sf::String> vecTileMap, int nSize);
    void ReadMap(std::vector<sf::String>& vecTileMap, int nLevel);
    void ReadValues(SettingsValues& settingValues, std::string sFileName);
    void Level();
    void PreExit();
    void EndOfTheLevel(int nStart, int& nFinish, sf::Clock CTimer, bool& bTimer);


public:
    Gameplay(sf::RenderWindow& WWindow, GameSound& gameSound);
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