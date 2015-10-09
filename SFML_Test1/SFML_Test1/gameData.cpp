#include "gameData.h"

GameData::GameData()
{
    //when start...
    //set the game_state to introduction
    game_state = intro;
    //add 1 player, the one that runs this program
    Player you;
    player.push_back(you);
}

void GameData::AddPlayer()
{
    mutex.lock();
	Player newPlayer;
    //if the number of players is less than 4, add 1 player
    if(player.size() < 4)
    {
        player.push_back(newPlayer);
    }
    mutex.unlock();
}

void GameData::RebuildPlayer(const int& num)
{
    mutex.lock();
	player.clear();
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
	player.pop_back();
    mutex.unlock();
}

void GameData::NewGame()
{
    mutex.lock();
    //create new map
    //...
    
    //
    mutex.unlock();
}