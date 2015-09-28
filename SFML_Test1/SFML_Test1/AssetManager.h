#include <SFML/Graphics.hpp>
#include <map>
#include <assert.h>

#include "ResourcePath.hpp"

class AssetManager
{
private:
    //texture handler
	std::map<std::string, sf::Texture> m_Textures;  //map of textures

    static AssetManager* sInstance;
public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);
};
