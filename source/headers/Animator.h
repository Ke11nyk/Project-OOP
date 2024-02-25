#pragma once
#include<iostream>
#include<vector>
#include<list>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

/**
* \brief This is the class to animate player
*/
class Animator
{
public:
	/**
	* \brief This is the struct to create animations
	*/
	struct Animation
	{
		std::string sName; ///< Name of the animation
		std::string sTextureName; ///< Name of the texture
		std::vector<sf::IntRect> vecFrames; ///< Frames of the animation
		sf::Time TDuration; ///< The animation frame playback time
		bool bLooping; ///< The animation is looped or not

		Animation(std::string const& sName, std::string const& sTextureName,
			sf::Time const& TDuration, bool bLooping) :sName(sName), sTextureName(sTextureName),
			TDuration(TDuration), bLooping(bLooping)
		{}

		/** 
		* \brief The method that switches animation frames
		* \param iStartFrom The coordinates of the upper left corner of the starting frame
		* \param iFrameSize The size of the frame
		* \param nFrames The number of the frames
		* \param nTraccia The number of the lines of the frames
		*/
		void AddFrames(sf::Vector2i const& iStartFrom,
			sf::Vector2i const& iFrameSize, unsigned int nFrames, unsigned int nTraccia)
		{
			sf::Vector2i iCurrent = iStartFrom;
			for (unsigned int t = 0; t < nTraccia; t++) {
				for (unsigned int i = 0; i < nFrames; i++)
				{
					vecFrames.push_back(sf::IntRect(iCurrent.x, iCurrent.y, iFrameSize.x, iFrameSize.y)); // Picture parameters with animation frames
					iCurrent.x += iFrameSize.x; // We move through the animation frames in the current line
				}
				iCurrent.y += iFrameSize.y;
				iCurrent.x = iStartFrom.x;
			}
		}
	};

	explicit Animator(sf::Sprite& SSprite); 

	Animator::Animation& CreateAnimation(std::string const& sName,
		std::string const& sTextureName, sf::Time const& TDuration, bool bLoop = false);

	void Update(sf::Time const& TDt); 

	bool SwitchAnimation(std::string const& sName); 

	std::string GetCurrentAnimationName() const;

	void Restart();

	bool getEndAnim() const
	{
		return bEndAnim;
	}


private:
	Animator::Animation* FindAnimation(std::string const& sName);
	void SwitchAnimation(Animator::Animation* aniAnimation);

	/** Animation properties */
	sf::Sprite& SSprite; ///< The sprite for which animations will be created
	sf::Time TCurrentTime; ///< The time to countdown
	std::list<Animator::Animation> lAnimations; ///< The list of the animations
	Animator::Animation* aniCurrentAnimation; ///< The current animation
	bool bEndAnim = false; ///< The end of the animation is reached or not
};