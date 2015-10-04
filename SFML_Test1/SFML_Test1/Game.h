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
public:
    TheGame();
    TheGame(std::shared_ptr<NetworkManager>, std::shared_ptr<GameData>);
};

#endif /* defined(__myTest__Game__) */
