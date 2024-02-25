#include "../headers/Animator.h"

/**
* \brief Initialization of SSprite
* \param SSprite The sprite that will be animated
*/
Animator::Animator(sf::Sprite& SSprite) : aniCurrentAnimation(nullptr), SSprite(SSprite)
{

}

Animator::Animation& Animator::CreateAnimation(std::string const& sName, std::string const& sTextureName, sf::Time const& TDuration, bool bLoop)
{

	lAnimations.emplace_back(sName, sTextureName, TDuration, bLoop);

	// if we don't have a next animation, we use the current animation
	if (aniCurrentAnimation == nullptr) SwitchAnimation(&lAnimations.back());

	return lAnimations.back();
}

/**
* \brief The method that switch animations of the sprite
* \param aniAnimation The animation to be switched to
* **Example using**
* \code
* auto& idleForwardStatic = StickAnim.CreateAnimation("idleForwardStatic", StrTexture, sf::seconds(fTime), true);
* idleForwardStatic.AddFrames(sf::Vector2i(0, 0), iSpriteSize, 1, 1);
* auto animation = &idleForwardStatic;
* SwitchAnimation(animation);
* \endcode
*/
void Animator::SwitchAnimation(Animator::Animation* aniAnimation)
{
	// Change the texture of the animation 
	if (aniAnimation != nullptr)
	{
		SSprite.setTexture(AssetManager::GetTexture(aniAnimation->sTextureName));
	}

	aniCurrentAnimation = aniAnimation;
	TCurrentTime = sf::Time::Zero; // Reset time
}

/**
* \brief The method that works out how to choose the right frame at the right time
* \param TDt The delta time
*/
void Animator::Update(sf::Time const& TDt)
{
	if (aniCurrentAnimation == nullptr) return;

	TCurrentTime += TDt;

	float scaledTime = (TCurrentTime.asSeconds() / aniCurrentAnimation->TDuration.asSeconds());
	auto numFrames = static_cast<int>(aniCurrentAnimation->vecFrames.size());
	auto currentFrame = static_cast<int>(scaledTime * numFrames);

	if (aniCurrentAnimation->bLooping) currentFrame %= numFrames;
	else
		if (currentFrame >= numFrames) { currentFrame = numFrames - 1; bEndAnim = true; }

	SSprite.setTextureRect(aniCurrentAnimation->vecFrames[currentFrame]);

}

/**
* \brief The method that check if animation exists
* \param sName The name of the searched animation
* \return True if animation exist and false otherwise
*/
bool Animator::SwitchAnimation(std::string const& sName)
{
	auto animation = FindAnimation(sName);
	if (animation != nullptr)
	{
		SwitchAnimation(animation);
		return true;
	}
	return false;
}

/**
* \brief The method that gives a name of the animation
* \param sName The name of the searched animation
* \return The name of the animation or empty string
*/
std::string Animator::GetCurrentAnimationName() const
{
	if (aniCurrentAnimation != nullptr) return aniCurrentAnimation->sName;
	return "";
}

/**
* \brief The method that restarts the animation
*/
void Animator::Restart()
{
	TCurrentTime = sf::Time::Zero; // Reset time
	bEndAnim = false;
}

/**
* \brief The method that searches for the given animation
* \param sName The name of the animation
* \return Link on the animation if it exists
*/
Animator::Animation* Animator::FindAnimation(std::string const& sName)
{
	for (auto it = lAnimations.begin(); it != lAnimations.end(); ++it)
	{
		if (it->sName == sName) return &*it;
	}

	return nullptr;
}