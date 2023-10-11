#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <assert.h>
#include<map>


class AssetManager
{
	std::map<std::string, sf::Texture> mTextures;
	std::map<std::string, sf::SoundBuffer> mSoundBuffer;
	std::map<std::string, sf::Font> mFonts;

	// there is only one instance of the class
	static AssetManager* sInstance;


public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);
	static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);
	static sf::Font& GetFont(std::string const& filename);
};