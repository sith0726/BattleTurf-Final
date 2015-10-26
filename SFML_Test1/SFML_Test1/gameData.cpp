#include "gameData.h"
#include <iostream> //debug

GameData::GameData()
{
    //when start...
    //the game is not created, so set isCreated false.
    isCreated = false;
    
	//Randomize
	std::srand(time(NULL));

    //set the game_state to introduction
    game_state = intro;
    //add 1 player, the one that runs this program
    Player you;
	playerList.push_back(you);
	//Player somebody;	//testing
	//playerList.push_back(somebody);
}

void GameData::AddPlayer()
{
    //mutex.lock();
	Player newPlayer;
    //if the number of players is less than 4, add 1 player
	if (playerList.size() < 4)
    {
		playerList.push_back(newPlayer);
    }
    //mutex.unlock();
}

void GameData::RebuildPlayer(const int& num)
{
    mutex.lock();
	playerList.clear();
	for (int i = 0; i < num; i++)
	{
		AddPlayer();
	}
    mutex.unlock();
}

void GameData::RemovePlayer(const int& index)
{
    mutex.lock();
    //remove that player from the list(for networking, remember to disconnect the socket.)
	playerList.pop_back();
    mutex.unlock();
}

void GameData::NewGame()
{
    mutex.lock();

    //create new map
	gameMap.create();

	//set the basic texture path of each player
	std::string texture_path[] = { "Texture/box_blue_1_", "Texture/box_red_1_", "Texture/box_green_1_", "Texture/box_yellow_1_" };
	int numPlayer = 0;
	for (Player &player : playerList)
	{
		player.setTexturePath(texture_path[numPlayer]);
		numPlayer++;
	}
    
	//generate a score pool
	std::vector<int> score_pool;
    int size = gameMap.getAvailableBox() / playerList.size() + 1;
	for (unsigned int i = 0; i < size; i++)
	{
		score_pool.push_back(rand() % 27 + 3);
	}

    //set player's scorelist
	for (Player & player : playerList)
	{
		for (int & score : score_pool)
		{
			player.getScoreList().push_back(score);
		}
	}

	//when start, the iterator points to begining
	playerList_it = playerList.begin();

    //game created
    isCreated = true;
    mutex.unlock();
}

void GameData::NextPlayer()
{
	mutex.lock();
	playerList_it++;
	if (playerList_it == playerList.end())
	{
		playerList_it = playerList.begin();
	}
	mutex.unlock();
}

Player& GameData::getWinner()
{
    //don't blame me in case of no winner...because I don't have "Draw" image for that...
    std::list<Player>::iterator winner = playerList.begin();
    
    for(std::list<Player>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        if(it->getTotalScore() > winner->getTotalScore())
            winner = it;
    }
    return *winner;
}

int GameData::getScore(int index)
{
    if(index > getPlayerNumber() || index < 0)
    {
        return 0;
    }
    
    std::list<Player>::iterator it = playerList.begin();
    
    
    for(int i = 0; i != index; i++)
    {
        it++;
    }
    
    return it->getTotalScore();
}

sf::Packet& GameData::fillScore_Packet(sf::Packet & packet)
{
    //structure :
    //(# of player) -> for each player[(size of scoreList)->(scoreList)]
    
    //send the amount of player
    packet << getPlayerNumber();
    
    for(Player &player : playerList)
    {
        //get that player's scoreList
        std::vector<int> holdList = player.getScoreList();
        //send the size first
        packet << static_cast<int>(holdList.size());
        //send the scoreList
        for(int & num : holdList)
        {
            packet << num;
        }
    }
	return packet;
}

void GameData::decodeScore_Packet(sf::Packet & packet)
{
    //structure :
    //(# of player) -> for each player[(size of scoreList)->(scoreList)]
    
    int playerNumber;
    packet >> playerNumber;
    if(playerNumber != getPlayerNumber())
    {
        std::cout << "PlayerNum Error...the value is " << playerNumber << std::endl;
		RebuildPlayer(playerNumber);
    }
    
    for(Player &player : playerList)
    {
        //get the size first
        int size;
        packet >> size;
        
        //get that player's scoreList
        std::vector<int>& holdList = player.getScoreList();
        
        //clear the list
        holdList.clear();
        
        for(int i = 0; i < size; i++)
        {
            int value;
            packet >> value;
            holdList.push_back(value);
        }
    }
    
    //set the basic texture path of each player
    std::string texture_path[] = { "Texture/box_blue_1_", "Texture/box_red_1_", "Texture/box_green_1_", "Texture/box_yellow_1_" };
    int numPlayer = 0;
    for (Player &player : playerList)
    {
        player.setTexturePath(texture_path[numPlayer]);
        numPlayer++;
    }

	playerList_it = playerList.begin();

	isCreated = true;
}

void GameData::decodeUpdate_Packet(sf::Packet &packet)
{
	sf::Vector2i mouseposition;
	packet >> mouseposition.x >> mouseposition.y;

	//do capture stuff
	if (gameMap.getCurrentBox(mouseposition).isCapturable())
	{
		Box newUserBox(*playerList_it);
		//set the size to 50...
		newUserBox.setSize(sf::Vector2f(50, 50));

		sf::Vector2f position = gameMap.getCurrentBox(mouseposition).getPosition();
		//set the new position for userBox
		newUserBox.setPosition(position);
		//set the score
		newUserBox.txt_score.setPosition(position.x + 5, position.y + 5);
		newUserBox.txt_score.setCharacterSize(30);
		newUserBox.txt_score.setColor(sf::Color(0, 0, 0, 255));
		//copy the box into the map
		gameMap.captureBox(newUserBox, mouseposition);
		//next player move
		NextPlayer();
	}
}