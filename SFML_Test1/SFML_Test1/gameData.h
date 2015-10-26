/*
 This class handle the data behind the scence, 
 in contrast, TheGame class handle the
 on screen objects and operations.
*/

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "AssetManager.h" //resource manager
#include "Player.h"
#include "GameMap.h"
#include <vector>
#include <list>
#include <mutex>
#include <memory>

//declare the game state
enum Game_State{intro, menu, game};

class GameData
{
private:
    //resource manager
	AssetManager resourceManager;
    //game state
    Game_State game_state;
    //list of players
    std::list<Player> playerList;		//0 = player1, 1 = player2, 2 = player3, 3 = player4
	//the iterator of PlayerList
	std::list<Player>::iterator playerList_it;

	//index of this player
	int thisplayer;

    //map
	GameMap gameMap;
    
    //mutex
    std::mutex mutex;
    
    //is the game created?
    bool isCreated;
    
public:
    GameData();

    //get the current game state
    Game_State getGameState(){return game_state;}
    
    //set the current game state
    void setGameState(const Game_State &newState){game_state = newState;}
    
    //get the number of players
    int getPlayerNumber(){return playerList.size();}
    
    //insert a player
    void AddPlayer();

	//Rebuild the list, for client only
	void RebuildPlayer(const int& num);
    
    //remove a player
    void RemovePlayer(const int& index);

	//set player's index
	void setPlayerindex(const int& num){ thisplayer = num; }

	//get player's index
	int getPlayerindex(){ return thisplayer; }
    
    //game creation
    void NewGame();

	//next player move
	void NextPlayer();
    
    //get the gameMap
    GameMap& getGameMap(){return gameMap;}

	//get the current Player
	Player& getCurrentPlayer(){ return *playerList_it; }
    
    //is the game started? (I mean created?)
    bool isGameCreated(){return isCreated;}
    
    //get the player who has the highest score
    Player& getWinner();
    
    //get the score of target player
    int getScore(int playerindex);
    
    //fill player's score list in packet
    sf::Packet& fillScore_Packet(sf::Packet &);
    
    //decode player's score list in packet
    void decodeScore_Packet(sf::Packet &);

	//decode the update packet
	void decodeUpdate_Packet(sf::Packet &);

};
#endif // GAMEDATA_H
