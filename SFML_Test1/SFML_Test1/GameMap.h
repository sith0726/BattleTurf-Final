#ifndef _GAMEMAP_
#define _GAMEMAP_

#include "box.h"
#include <SFML/Network.hpp>
#include <vector>

//the map of the game, can be drawn into the window
//It consists of an array of boxes, which are the important part of the game.
class GameMap : public sf::Drawable
{
private:
	//the map is an array of boxes, 10x10 boxes and the walls at each sides,
	//therefore we have 12x12 boxes = 144 boxes
	static const int MAP_WIDTH = 12;
	static const int MAP_HEIGHT = 12;
	Box m_Map[MAP_HEIGHT][MAP_WIDTH];

	Box* currentBox;
public:
	//constructor
	GameMap();
    
    //reset the map
    void reset();

	//get the currentbox (cannot be modified directly)
	const Box& getCurrentBox(const sf::Vector2i &mouseposition);
    
    //direct capture the box
    bool captureBox(const Box& newBox, const sf::Vector2i &mouseposition);

	//for window drawing
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//packet operator overloading
	friend sf::Packet& operator<<(sf::Packet&, const GameMap&);
	friend sf::Packet& operator>>(sf::Packet&, GameMap&);
};
#endif