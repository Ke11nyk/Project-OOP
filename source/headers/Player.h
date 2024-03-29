﻿#pragma once
#include"Animator.h"

/**
* \brief This is the class to create the player and control his physics
*/
class Player
{
	sf::RenderWindow& WWindow; ///< Window of the game
	sf::Sprite SStickSprite; ///< Sprite of the player
	Animator StickAnim = Animator(SStickSprite);  ///< Animation of the player

	sf::String StrTexture; ///< Texture of the player
	int nFrame; ///< Number of frames of the animation

	// size of sprite
	int const static stc_nWidth = 54; ///< Width of the player
	int const static stc_nHeight = 60; ///< Height of the player

	int const static stc_nTs = 50; ///< Side of block and point

	float fOffsetX = 0; ///< X-delta of the camera
	float fOffsetY = 0; ///< Y-delta of the camera

	float fStepx = 0.0f; ///< Step of X-moving of sprite
	float fStepy = 0.0f; ///< Step of Y-moving of sprite 

	sf::Vector2f fiPos; ///< Start coordinates
	sf::Time TTimeUpdate = sf::milliseconds(0); ///< Update time
	bool bDead = false; ///< Status of the player
	bool bOnGround; ///< Player is on ground or not

	int nPoints = 0; ///< Points number of the player

	std::vector<sf::String>& vecMap; ///< Map of the level

	bool bDoorOpened = false; ///< State of the door


public:

	Player(sf::RenderWindow& WWindow, std::vector<sf::String>& vecMap, sf::String StrTexture, int nFrame, sf::Vector2f fiMypos = sf::Vector2f(800, 300), float fTime = 0.5,
		sf::Vector2i iSpriteSize=sf::Vector2i(stc_nWidth, stc_nHeight), int nStepy=60): WWindow(WWindow), vecMap(vecMap), StrTexture(StrTexture), nFrame(nFrame), fiPos(fiMypos)
	{
		SStickSprite.setPosition(fiPos.x, fiPos.y);
		auto& idleForwardStatic = StickAnim.CreateAnimation("idleForwardStatic", StrTexture, sf::seconds(fTime), true);
		idleForwardStatic.AddFrames(sf::Vector2i(0, 0), iSpriteSize, 1, 1);
		auto& idleBackStatic = StickAnim.CreateAnimation("idleBackStatic", StrTexture, sf::seconds(fTime), true);
		idleBackStatic.AddFrames(sf::Vector2i(0, nStepy), iSpriteSize, 1, 1);
		auto& idleForward = StickAnim.CreateAnimation("idleForward", StrTexture, sf::seconds(fTime), true);
		idleForward.AddFrames(sf::Vector2i(0, 0), iSpriteSize, nFrame, 1);
		auto& idleBack = StickAnim.CreateAnimation("idleBack", StrTexture, sf::seconds(fTime), true);
		idleBack.AddFrames(sf::Vector2i(0, nStepy), iSpriteSize, nFrame, 1);
	}

	void Keys(sf::Event EEvent);

	void Collision(float fDir);

	void Update(sf::Time const& TDeltaTime);


	float getStepx()
	{
		return fStepx;
	}

	void setStepx(float fX)
	{
		fStepx = fX;
	}

	float getStepy()
	{
		return fStepy;
	}

	void setStepy(float fY)
	{
		fStepy = fY;
	}

	void setOffsetX(float fX)
	{
		fOffsetX = fX;
	}

	void setOffsetY(float fY)
	{
		fOffsetY = fY;
	}

	int getPoints()
	{
		return nPoints;
	}

	void setPoints(int nValue)
	{
		nPoints = nValue;
	}

	void setTexture(sf::String StrText)
	{
		StrTexture = StrText;
	}

	void setDead(bool bPlayerdead)
	{
		bDead = bPlayerdead;
	}

	bool getDead() const
	{
		return bDead;
	}

	void setDoorOpened(bool bValue)
	{
		bDoorOpened = bValue;
	}

	bool getDoorOpened()
	{
		return bDoorOpened;
	}

	sf::Sprite& getStick()
	{
		return SStickSprite;
	}
};