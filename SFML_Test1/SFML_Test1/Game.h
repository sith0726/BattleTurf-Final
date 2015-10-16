/*
 This class handle the game mechanism and on-screen graphic operations,
 for game data, see gameData class.
 */
#ifndef __myTest__Game__
#define __myTest__Game__

#include "gameData.h"
#include <memory>
#include "NetworkManager.h"

class TheGame
{
private:
    std::shared_ptr<GameData> ptrData;
    std::shared_ptr<NetworkManager> ptrNet;

	//a pointer pointing to the previous Box, for graphing
	Box* previousBox;

    //the current player's turn
    Player* currentPlayer;
    
	//the box to be put into the map
	Box userBox;
public:
    TheGame();
    TheGame(std::shared_ptr<NetworkManager>, std::shared_ptr<GameData>);
    
	void Mouse_moved_update(sf::Vector2i &mouseposition);

	void Mouse_clicked_update(sf::Vector2i &mouseposition);

    void Graphic_update(sf::RenderWindow*);
    
    void dataUpdate(sf::Vector2i &mouseposition);
};

#endif /* defined(__myTest__Game__) */
