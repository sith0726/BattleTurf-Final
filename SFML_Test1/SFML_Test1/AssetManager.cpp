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
	auto& texMap = sInstance->m_Textures;
	
	auto pairFound = texMap.find(filename);
	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}