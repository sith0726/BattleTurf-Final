#include "Game.h"
TheGame::TheGame()
{
    
}

TheGame::TheGame(std::shared_ptr<NetworkManager> ptr1, std::shared_ptr<GameData> ptr2)
{
    ptrNet = ptr1;
    ptrData = ptr2;
}


void TheGame::Graphic_update(sf::RenderWindow* window)
{
    //draw the map
    window->draw(ptrData->getGameMap());
    
}