#include "Player.h"
Player::Player()
{
    score = 0;
    //start with index 0
	scoreIndex = 0;
}

Player::Player(const int& size)
{
    //the score of the player
    score = 0;
    
    //start with index 0
	scoreIndex = 0;
    
    //initializing the list
    //...
}

void Player::resetList(const int& size)
{
	scoreList.clear();
}

int Player::getNextScore()
{
	int ans = scoreList[scoreIndex];
	scoreIndex++;
    return ans;
}