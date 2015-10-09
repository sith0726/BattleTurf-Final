#ifndef _AssetManager_
#define _AssetManager_

#include <SFML/Graphics.hpp>
#include <map>
#include <assert.h>

#include "ResourcePath.hpp"

class AssetManager
{
private:
    //texture handler
	std::map<std::string, sf::Texture> m_Textures;  //map of textures
	std::map<std::string, sf::Font> m_Font;	//map of font

    static AssetManager* sInstance;
public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);
	static sf::Font& GetFont(std::string const& filename);
};

#endif