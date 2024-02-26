#include "../headers/AssetManager.h"

AssetManager* AssetManager::stcInstance = nullptr;

/**
* \brief The constructor that allowes only one AssetManager to exist
*/
AssetManager::AssetManager()
{
	assert(stcInstance == nullptr);
	stcInstance = this;
}

sf::Texture& AssetManager::GetTexture(std::string const& sFilename)
{
	auto& texMap = stcInstance->sTextures;
	auto pairFound = texMap.find(sFilename);

	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& texture = texMap[sFilename];
		texture.loadFromFile(sFilename);
		return texture;
	}

}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& sFilename)
{
	auto& bufferMap = stcInstance->sSoundBuffer;
	auto pairFound = bufferMap.find(sFilename);

	if (pairFound != bufferMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& buffer = bufferMap[sFilename];
		buffer.loadFromFile(sFilename);
		return buffer;
	}
}

sf::Font& AssetManager::GetFont(std::string const& sFilename)
{
	auto& fontMap = stcInstance->sFonts;
	auto pairFound = fontMap.find(sFilename);

	if (pairFound != fontMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& font = fontMap[sFilename];
		font.loadFromFile(sFilename);
		return font;
	}
}
