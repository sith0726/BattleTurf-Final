#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "AssetManager.h" //resource manager
#include <vector>
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
public:
    GameData()
    {
        game_state = intro;
    }
    
    //get the current game state
    Game_State getGameState(){return game_state;}
    
    //set the current game state
    void setGameState(const Game_State &newState){game_state = newState;}
    
};

#endif // GAMEDATA_H

