#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <assert.h>
#include<map>

/**
* \brief This is the class to organize access to source files
* 
* There is only one instance of the class.
*/
class AssetManager
{
	std::map<std::string, sf::Texture> sTextures; ///< The map for saving textures
	std::map<std::string, sf::SoundBuffer> sSoundBuffer; ///< The map for saving sounds
	std::map<std::string, sf::Font> sFonts; ///< The map for saving fonts

	static AssetManager* stcInstance; ///< The pointer to allow only one AssetManager to exist


public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& sFilename);
	static sf::SoundBuffer& GetSoundBuffer(std::string const& sFilename);
	static sf::Font& GetFont(std::string const& sFilename);
};