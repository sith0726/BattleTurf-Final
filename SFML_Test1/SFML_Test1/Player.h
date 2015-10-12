#ifndef _Player_
#define _Player_
#include <vector>

class Player
{
private:
    //the list of score
	std::vector<int> scoreList;
    
	//the score index
	int scoreIndex;
    
    //player total score
    int score;

	//the texture path of this player
	std::string texture_path;
    
public:
    //constructor
    Player();
    
    //constructor accepting the size of list
    Player(const int&);
    
    //reset list, generate a list of score to be put into the game
    void resetList(const int& size);
    
    //
    int getNextScore();
    
	//get the scoreList
	std::vector<int>& getScoreList(){ return scoreList; }

	//set the texturepath
	void setTexturePath(const std::string& newpath){ texture_path = newpath; }
    
	//get the texturepath
	const std::string& getTexturePath() const { return texture_path; }

	//get the total score of that player
	int getTotalScore(){ return score; }

	//Add score to this player(actually it can be negative)
	void  addScore(int value){ score += value; }
};

#endif