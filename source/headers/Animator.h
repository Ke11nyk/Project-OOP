#pragma once
#include<iostream>
#include<vector>
#include<list>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Animator
{
public:
	struct Animation
	{
		std::string mName;
		std::string mTextureName;
		std::vector<sf::IntRect> mFrames;
		sf::Time mDuration; // animation frame playback time
		bool mLooping;

		Animation(std::string const& name, std::string const& textureName,
			sf::Time const& duration, bool looping) :mName(name), mTextureName(textureName),
			mDuration(duration), mLooping(looping)
		{}

		// switching animation frames
		void AddFrames(sf::Vector2i const& startFrom,
			sf::Vector2i const& frameSize, unsigned int frames, unsigned int traccia)
		{
			sf::Vector2i  current = startFrom;
			for (unsigned int t = 0; t < traccia; t++) {
				for (unsigned int i = 0; i < frames; i++)
				{
					// picture parameters with animation frames
					mFrames.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
					// we move through the animation frames in the current line
					current.x += frameSize.x;
				}
				current.y += frameSize.y;
				current.x = startFrom.x;
			}
		}
	};

	explicit Animator(sf::Sprite& sprite); // initialization of mSprite

	Animator::Animation& CreateAnimation(std::string const& name,
		std::string const& textureName, sf::Time const& duration, bool loop = false);

	void Update(sf::Time const& dt); // working out how to choose the right frame at the right time

	bool SwitchAnimation(std::string const& name); // changing the current animation to an animation with the given name

	std::string GetCurrentAnimationName() const;

	void restart();

	bool getEndAnim() const
	{
		return endAnim;
	}


private:
	// we are looking for an animation using the given name
	Animator::Animation* FindAnimation(std::string const& name);
	// change the current animation
	void SwitchAnimation(Animator::Animation* animation);

	// animation properties
	sf::Sprite& mSprite;
	sf::Time mCurrentTime;
	std::list<Animator::Animation> mAnimations;
	Animator::Animation* mCurrentAnimation;
	bool endAnim = false;
};