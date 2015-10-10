#include "Player.h"
Player::Player()
{
    score = 0;
    //the iterator points at the beginning of the list
    it = scoreList.begin();
}

Player::Player(const int& size)
{
    //the score of the player
    score = 0;
    
    //the iterator pooints at the beginning of the list
    it = scoreList.begin();
    
    //initializing the list
    //...
}

void Player::resetList(const int& size)
{
	scoreList.clear();
}

int Player::getNextScore()
{
    int ans = 0;
    if(it != scoreList.end())
    {
        ans = *it;
    }
    return ans;
}