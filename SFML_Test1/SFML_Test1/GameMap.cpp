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
    Box& targetBox = getCurrentBox(mouseposition);
    
    //if the box is not capturable, return false
    if(!targetBox.isCapturable())
    {
        return false;
    }
    
    //copy the newBox to the target
    targetBox = newBox;
    
	//define the adjaceBoxes
	Box *adjacentBox[] = { &targetBox - MAP_WIDTH,                                  //up
		&targetBox + MAP_WIDTH,                                 //down
		&targetBox - 1,    //left
		&targetBox + 1,    //right
		&targetBox - MAP_WIDTH - 1,//left top
		&targetBox + MAP_WIDTH - 1,//left bottom
		&targetBox - MAP_WIDTH + 1,//right top
		&targetBox + MAP_WIDTH + 1//right bottom
	};

	//check the surroundings...
	for (int i = 0; i < 8; i++)
	{
		if (adjacentBox[i]->getState() == Boxstate::occupied)
		{
			//if it is the same owner, fortify and change the texture
			if (adjacentBox[i]->getOwner() == targetBox.getOwner())
			{
				//fortify...
				//...
				}
			//else, capture that box
			else
			{

			}
		}
	}

	//change the textures....
	changeTexture(targetBox);

	for (int i = 0; i < 8; i++)
	{
		if (adjacentBox[i]->getState() == Boxstate::occupied)
		{
			changeTexture(*adjacentBox[i]);
		}
	}

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

void GameMap::changeTexture(Box& box)
{
	//define the box at top, bottom, left, right
	Box *foursideBox[] = { &box - MAP_WIDTH, &box + 1 , & box + MAP_WIDTH, &box - 1};

	/*declare the hash value, initialize as 0.
	If the player also owns the top, the hash value +1
	If the player also owns the right, the hash value +5
	If the player also owns the bottom, the hash value +7
	If the player also owns the left, the hash value +9
	*/
	int hashAddress = 0;
	if (box.getOwner() != foursideBox[0]->getOwner())
	{
		hashAddress += 1;
	}
	if (box.getOwner() != foursideBox[1]->getOwner())
	{
		hashAddress += 5;
	}
	if (box.getOwner() != foursideBox[2]->getOwner())
	{
		hashAddress += 7;
	}
	if (box.getOwner() != foursideBox[3]->getOwner())
	{
		hashAddress += 9;
	}
	//change the texture according to the hash value

	std::string path = box.getOwner()->getTexturePath() + std::to_string(hashAddress) + ".png"; 
		
	box.setButtonTexture(&AssetManager::GetTexture(path), &AssetManager::GetTexture(path));
	box.change_texture_to_normal();
}