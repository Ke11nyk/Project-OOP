#include "../headers/Animator.h"

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

void Animator::SwitchAnimation(Animator::Animation* aniAnimation)
{
	// change the texture of the animation
	if (aniAnimation != nullptr)
	{
		SSprite.setTexture(AssetManager::GetTexture(aniAnimation->sTextureName));
	}

	aniCurrentAnimation = aniAnimation;
	TCurrentTime = sf::Time::Zero; // reset time
}

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

std::string Animator::GetCurrentAnimationName() const
{
	if (aniCurrentAnimation != nullptr) return aniCurrentAnimation->sName;
	return "";
}

void Animator::Restart()
{
	TCurrentTime = sf::Time::Zero; // reset time
	bEndAnim = false;
}

Animator::Animation* Animator::FindAnimation(std::string const& sName)
{
	for (auto it = lAnimations.begin(); it != lAnimations.end(); ++it)
	{
		if (it->sName == sName) return &*it;
	}

	return nullptr;
}