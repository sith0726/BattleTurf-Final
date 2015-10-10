#include "GameMap.h"

//constructor
GameMap::GameMap()
{
	//initialize the available box
	available_Box = MAP_HEIGHT * MAP_WIDTH;

	//initailizing the vector map
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_Map[i][j].setPosition(sf::Vector2f(50 * j, 50 * i));
		}
	}
}

void GameMap::create()
{
	//the edge are walls
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		if (m_Map[i][0].setWall())
		{
			available_Box--;
		}
		if (m_Map[i][MAP_HEIGHT - 1].setWall())
		{
			available_Box--;
		}
	}
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (m_Map[0][i].setWall())
		{
			available_Box--;
		}
		if (m_Map[MAP_WIDTH - 1][i].setWall())
		{
			available_Box--;
		}
	}

	//generate walls
	int wallCount = 0;
	while (wallCount < 20)
	{
		if (m_Map[rand() % MAP_HEIGHT][rand() % MAP_WIDTH].setWall())
		{
			wallCount++;
			available_Box--;
		}
	}
}

Box& GameMap::getCurrentBox(const sf::Vector2i& mouseposition)
{
	return m_Map[mouseposition.y / 50][mouseposition.x / 50];
}

bool GameMap::captureBox(const Box& newBox, const sf::Vector2i &mouseposition)
{
    //get the reference of the box
    Box targetBox = getCurrentBox(mouseposition);
    
    //if the box is not capturable, return false
    if(!targetBox.isCapturable())
    {
        return false;
    }
    
    //copy the newBox to the target
    targetBox = newBox;
    
    return true;
    
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