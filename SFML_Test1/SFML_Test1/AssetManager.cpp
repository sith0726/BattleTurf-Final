//The resource directory of Windows and Mac is different.
//So for mac I have to add a resourcePath funcion to
//ensure it can read the files.
#include "AssetManager.h"

AssetManager* AssetManager::sInstance = 0;

AssetManager::AssetManager()
{
	//if instance is not declared, create a new one.
	if (sInstance == 0)
	{
		assert(sInstance == 0);
        sInstance = this;
	}
    
}

sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
	std::map<std::string, sf::Texture>& texMap = sInstance->m_Textures;
	
    std::map<std::string, sf::Texture>::iterator pairFound = texMap.find(filename);
	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else
	{
        sf::Texture& texture = texMap[filename];

#ifdef _WIN32
		texture.loadFromFile(filename);
#elif __MACH__
        texture.loadFromFile(resourcePath() + filename);
#endif
		return texture;
	}
}

sf::Font& AssetManager::GetFont(std::string const& filename)
{
	auto& FontMap = sInstance->m_Font;

	auto pairFound = FontMap.find(filename);
	if (pairFound != FontMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& font = FontMap[filename];

#ifdef _WIN32
		font.loadFromFile(filename);
#elif __MACH__
		font.loadFromFile(resourcePath() + filename);
#endif
		return font;
	}
}