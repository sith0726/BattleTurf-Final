#include "Game.h"
TheGame::TheGame()
{
    
}

TheGame::TheGame(std::shared_ptr<NetworkManager> ptr1, std::shared_ptr<GameData> ptr2)
{
    ptrNet = ptr1;
    ptrData = ptr2;
}