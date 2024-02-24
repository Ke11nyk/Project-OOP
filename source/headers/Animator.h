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
		std::string sName;
		std::string sTextureName;
		std::vector<sf::IntRect> vecFrames;
		sf::Time TDuration; // animation frame playback time
		bool bLooping;

		Animation(std::string const& sName, std::string const& sTextureName,
			sf::Time const& TDuration, bool bLooping) :sName(sName), sTextureName(sTextureName),
			TDuration(TDuration), bLooping(bLooping)
		{}

		// switching animation frames
		void AddFrames(sf::Vector2i const& iStartFrom,
			sf::Vector2i const& iFrameSize, unsigned int nFrames, unsigned int nTraccia)
		{
			sf::Vector2i iCurrent = iStartFrom;
			for (unsigned int t = 0; t < nTraccia; t++) {
				for (unsigned int i = 0; i < nFrames; i++)
				{
					// picture parameters with animation frames
					vecFrames.push_back(sf::IntRect(iCurrent.x, iCurrent.y, iFrameSize.x, iFrameSize.y));
					// we move through the animation frames in the current line
					iCurrent.x += iFrameSize.x;
				}
				iCurrent.y += iFrameSize.y;
				iCurrent.x = iStartFrom.x;
			}
		}
	};

	explicit Animator(sf::Sprite& SSprite); // initialization of mSprite

	Animator::Animation& CreateAnimation(std::string const& sName,
		std::string const& sTextureName, sf::Time const& TDuration, bool bLoop = false);

	void Update(sf::Time const& TDt); // working out how to choose the right frame at the right time

	bool SwitchAnimation(std::string const& sName); // changing the current animation to an animation with the given name

	std::string GetCurrentAnimationName() const;

	void Restart();

	bool getEndAnim() const
	{
		return bEndAnim;
	}


private:
	// we are looking for an animation using the given name
	Animator::Animation* FindAnimation(std::string const& sName);
	// change the current animation
	void SwitchAnimation(Animator::Animation* aniAnimation);

	// animation properties
	sf::Sprite& SSprite;
	sf::Time TCurrentTime;
	std::list<Animator::Animation> lAnimations;
	Animator::Animation* aniCurrentAnimation;
	bool bEndAnim = false;
};