#pragma once
#include"Animator.h"

class Player
{
	struct Borders
	{
		float nX; // left 
		float nY; // up
		float fMaxx; // right
		float fMaxy; // down
	};

	sf::RenderWindow& WWindow;   
	sf::Sprite SStickSprite;
	Animator StickAnim = Animator(SStickSprite);  // animation

	sf::String StrTexture;
	int nFrame;

	// size of sprite
	int const static stc_nWidth = 54;
	int const static stc_nHeight = 60;

	int const static stc_nTs = 50; // side of block and point

	float fOffsetX = 0, fOffsetY = 0;

	float fStepx = 0.0f; // step of moving of sprite
	float fStepy = 0.0f;       

	Borders borders{0};
	sf::Vector2f fiPos; // starting coordinates
	sf::Time TTimeUpdate;
	bool bDead = false; // status of player
	bool bOnGround;

	int nPoints = 0;

	std::vector<sf::String>& vecMap;

	bool bDoorOpened = false;


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
		

		borders.fMaxx = static_cast<float>(WWindow.getSize().x);
		borders.fMaxy = static_cast<float>(WWindow.getSize().y);
	}

	void setStepx(float fX)
	{
		fStepx = fX;
	}
	void setStepy(float fY)
	{
		fStepy = fY;
	}

	void Keys(sf::Event EEvent);

	void Collision(float fDir);

	void update(sf::Time const& TDeltaTime);

	void setBordersPlayer(float fX, float fY, float fMaxx, float fMaxy)
	{
		borders.nX = fX;
		borders.nY = fY;
		borders.fMaxx = fMaxx;
		borders.fMaxy = fMaxy;
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

	Borders getBorders()
	{
		return borders;
	}
};