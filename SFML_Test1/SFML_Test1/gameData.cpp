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