/*
 Box class, the box in the map
 box is an button (but disabled after occupied or became wall)
 Each player has an array of boxes, when they put it in the map
 If the player can capture the box, return true
 if not return false.
 
 Then the map class will compare the surrounding box
 by passing box into capture_indirectly function
 if the player can "steal" the box, change the textures and owner
 if this box is already owned by that player, add score by 3
 
 
 */
#ifndef _Box_
#define _Box_

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Button.h"
#include "AssetManager.h"

enum Boxstate {non_occupied = 0, occupied = 1, wall = 2};

class Box : public Button
{
private:
    //is it non occupited? occupied? or just a wall?
    Boxstate state;
    
    //the score of the box
    int score;
    
    //the pointer to the owner
    Player* owner;
    
public:
    //constructor
    Box();

	//constructor accept boxstate
	Box(Boxstate&);

	//constructor accept player
	Box(Player&);

	//the score text for graphing
	sf::Text txt_score;
    
    //try set the box to wall, if success return true, if fail return false
	bool setWall();
    
    //can player capture this box?
    bool isCapturable(){return state == Boxstate::non_occupied;}

	//get the box state
	Boxstate getState() const { return state; }
    
    //get the score of this box
    int getScore(){return score;}

	//set the score of the box
	void setScore(const int&);

	//get the owner
	Player* getOwner() { return owner; }

	//set the owner
	void setOwner(Player* newOwner){ owner = newOwner; }
};
#endif