#pragma once
#include "SFML/Graphics.hpp"
#include<SFML/Audio.hpp>
#include "Sprite.h"
#include "GameMenu.h"
#include "AssetManager.h"
#include "Animator.h"

class Game
{
    AssetManager manager;

    sf::RenderWindow win;
    sf::Image icon;
    sf::RectangleShape background;
    sf::Text Title;

    sf::Font fontAbout;
    sf::Text About;

    sf::Time PlayerTime;
    sf::Sprite PlayerSprite;
    Animator PlayerAnim = Animator(PlayerSprite);
    
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    void InitText(sf::Text& mtext, float xpos, float ypos, const sf::String str, 
        int sizeFont, sf::Color menuTextColor, int bord, sf::Color borderColor);
    void GameStart();
    void Settings();
    void AboutGame();
    void update(sf::Time const& deltaTime);
    void mainloop();
    

public:
    void CreateWindow();
};
