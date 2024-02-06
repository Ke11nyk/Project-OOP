#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <assert.h>
#include<map>


class AssetManager
{
	std::map<std::string, sf::Texture> sTextures;
	std::map<std::string, sf::SoundBuffer> sSoundBuffer;
	std::map<std::string, sf::Font> sFonts;

	// there is only one instance of the class
	static AssetManager* stcInstance;


public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& sFilename);
	static sf::SoundBuffer& GetSoundBuffer(std::string const& sFilename);
	static sf::Font& GetFont(std::string const& sFilename);
};