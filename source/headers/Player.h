#pragma once
#include"Animator.h"

class Player
{
	struct Borders
	{
		float x; // left 
		float y; // up
		float maxx; // right
		float maxy; // down
	};

	sf::RenderWindow& window;   
	sf::Sprite StickSprite;
	Animator StickAnim = Animator(StickSprite);  // animation

	sf::String texture;
	int frame;

	// size of sprite
	int const static width = 54;
	int const static height = 60;
	int const static ts = 50; // side of block and point

	float offsetX = 0, offsetY = 0;

	float stepx = 0.0f; // step of moving of sprite
	float stepy = 0.0f;       

	Borders borders{0};
	sf::Vector2f pos; // starting coordinates
	sf::Time timeUpdate;
	bool dead = false; // status of player
	bool onGround;

	int points = 0;

	sf::String* map;

	bool doorOpened = false;


public:

	Player(sf::RenderWindow& window, sf::String* map, sf::String texture, int frame, sf::Vector2f mypos = sf::Vector2f(800, 300), float time = 0.5,
		sf::Vector2i spriteSize=sf::Vector2i(width, height), int stepy=60): window(window), map(map), texture(texture), frame(frame), pos(mypos)
	{
		StickSprite.setPosition(pos.x, pos.y);
		auto& idleForwardStatic = StickAnim.CreateAnimation("idleForwardStatic", texture, sf::seconds(time), true);
		idleForwardStatic.AddFrames(sf::Vector2i(0, 0), spriteSize, 1, 1);
		auto& idleBackStatic = StickAnim.CreateAnimation("idleBackStatic", texture, sf::seconds(time), true);
		idleBackStatic.AddFrames(sf::Vector2i(0, stepy), spriteSize, 1, 1);
		auto& idleForward = StickAnim.CreateAnimation("idleForward", texture, sf::seconds(time), true);
		idleForward.AddFrames(sf::Vector2i(0, 0), spriteSize, frame, 1);
		auto& idleBack = StickAnim.CreateAnimation("idleBack", texture, sf::seconds(time), true);
		idleBack.AddFrames(sf::Vector2i(0, stepy), spriteSize, frame, 1);
		

		borders.maxx = static_cast<float>(window.getSize().x);
		borders.maxy = static_cast<float>(window.getSize().y);
	}

	void setStepx(float x)
	{
		stepx = x;
	}
	void setStepy(float y)
	{
		stepy = y;
	}

	void Keys(sf::Event event);

	void Collision(float dir);

	void update(sf::Time const& deltaTime);

	void setBordersPlayer(float x, float y, float maxx, float maxy)
	{
		borders.x = x;
		borders.y = y;
		borders.maxx = maxx;
		borders.maxy = maxy;
	}

	void setOffsetX(float x)
	{
		offsetX = x;
	}

	void setOffsetY(float y)
	{
		offsetY = y;
	}

	int getPoints()
	{
		return points;
	}

	void setPoints(int value)
	{
		points = value;
	}

	void setTexture(sf::String text)
	{
		texture = text;
	}

	void setDead(bool playerdead)
	{
		dead = playerdead;
	}

	bool getDead() const
	{
		return dead;
	}

	void setDoorOpened(bool value)
	{
		doorOpened = value;
	}

	bool getDoorOpened()
	{
		return doorOpened;
	}

	sf::Sprite& getStick()
	{
		return StickSprite;
	}

	Borders getBorders()
	{
		return borders;
	}
};