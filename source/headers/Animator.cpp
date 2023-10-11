#include "Animator.h"

Animator::Animator(sf::Sprite& sprite) : mCurrentAnimation(nullptr), mSprite(sprite)
{

}

Animator::Animation& Animator::CreateAnimation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool loop)
{

	mAnimations.emplace_back(name, textureName, duration, loop);

	// if we don't have a next animation, we use the current animation
	if (mCurrentAnimation == nullptr) SwitchAnimation(&mAnimations.back());

	return mAnimations.back();
}

void Animator::SwitchAnimation(Animator::Animation* animation)
{
	// change the texture of the animation
	if (animation != nullptr)
	{
		mSprite.setTexture(AssetManager::GetTexture(animation->mTextureName));
	}

	mCurrentAnimation = animation;
	mCurrentTime = sf::Time::Zero; // reset time
}

void Animator::Update(sf::Time const& dt)
{
	if (mCurrentAnimation == nullptr) return;

	mCurrentTime += dt;

	float scaledTime = (mCurrentTime.asSeconds() / mCurrentAnimation->mDuration.asSeconds());
	auto numFrames = static_cast<int>(mCurrentAnimation->mFrames.size());
	auto currentFrame = static_cast<int>(scaledTime * numFrames);

	if (mCurrentAnimation->mLooping) currentFrame %= numFrames;
	else
		if (currentFrame >= numFrames) { currentFrame = numFrames - 1; endAnim = true; }

	mSprite.setTextureRect(mCurrentAnimation->mFrames[currentFrame]);

}

bool Animator::SwitchAnimation(std::string const& name)
{
	auto animation = FindAnimation(name);
	if (animation != nullptr)
	{
		SwitchAnimation(animation);
		return true;
	}
	return false;
}

std::string Animator::GetCurrentAnimationName() const
{
	if (mCurrentAnimation != nullptr) return mCurrentAnimation->mName;
	return "";
}

void Animator::restart()
{
	mCurrentTime = sf::Time::Zero; // reset time
	endAnim = false;
}

Animator::Animation* Animator::FindAnimation(std::string const& name)
{
	for (auto it = mAnimations.begin(); it != mAnimations.end(); ++it)
	{
		if (it->mName == name) return &*it;
	}

	return nullptr;
}