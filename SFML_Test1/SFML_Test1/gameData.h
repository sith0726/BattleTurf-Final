#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "AssetManager.h" //resource manager
#include "Player.h"
#include <vector>
#include <list>
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
    std::list<Player> player;
    //map
    //...
    
public:
    GameData();

    //get the current game state
    Game_State getGameState(){return game_state;}
    
    //set the current game state
    void setGameState(const Game_State &newState){game_state = newState;}
    
    //get the number of players
    int getPlayerNumber(){return player.size();}
    
    //insert a player
    void InsertPlayer(Player&);
    
    //remove a player
    void RemovePlayer(const int&);
    
};

#endif // GAMEDATA_H

