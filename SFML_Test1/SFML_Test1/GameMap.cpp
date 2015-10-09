#include "GameMap.h"

//constructor
GameMap::GameMap()
{
	//initailizing the vector map
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_Map[i][j].setPosition(sf::Vector2f(50 * j, 50 * i));
		}
	}

}

Box& GameMap::getCurrentBox(const sf::Vector2i& mouseposition)
{
	return m_Map[mouseposition.x / 50][mouseposition.y / 50];
}

void GameMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//draw all boxes in the map
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			target.draw(m_Map[i][j], states);
		}
	}
}

sf::Packet& operator<<(sf::Packet& packet, const GameMap& gameMap)
{
	for (int i = 0; i < gameMap.MAP_HEIGHT; i++)
	{
		for (int j = 0; j < gameMap.MAP_WIDTH; j++)
		{
			int hold = gameMap.m_Map[i][j].getState();
			sf::Int8 sf_int_8(hold);
			packet << sf_int_8;
		}
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, GameMap& gameMap)
{
	for (int i = 0; i < gameMap.MAP_HEIGHT; i++)
	{
		for (int j = 0; j < gameMap.MAP_WIDTH; j++)
		{
			sf::Int8 hold;
			packet >> hold;
			Boxstate newstate = static_cast<Boxstate>(hold);
			Box box(newstate);
			gameMap.m_Map[i][j] = box;
		}
	}
	return packet;
}