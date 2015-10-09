#ifndef _Player_
#define _Player_
#include <list>

class Player
{
private:
    //the list of score
    std::list<int> scoreList;
    
    //the iterator of the scorelist, move 1 forword
    std::list<int>::iterator it;
    
    //player total score
    int score;
    
public:
    //constructor
    Player();
    
    //constructor accepting the size of list
    Player(const int&);
    
    //reset list, generate a list of score to be put into the game
    void resetList(const int& size);
    
    //get the next score in the list. The iterator will move 1 forword
    //if the iterator reaches the end of the list, it returns 0
    int getNextScore();
    
    
    
};

#endif