#include "Box.h"

//constructor
Box::Box()
{
    score = 0;
    state = non_occupied;
    this->setSize(sf::Vector2f(50,50));
	this->setButtonTexture(&AssetManager::GetTexture("Texture/box_empty_1_1.png"), &AssetManager::GetTexture("Texture/box_focus_1_1.png"));
	this->change_texture_to_normal();
	state = Boxstate::non_occupied;
}

Box::Box(Boxstate& newstate)
{
	score = 0;
	this->setSize(sf::Vector2f(50, 50));
	this->setButtonTexture(&AssetManager::GetTexture("Texture/box_empty_1_1.png"), &AssetManager::GetTexture("Texture/box_focus_1_1.png"));
	this->change_texture_to_normal();
	state = newstate;
}

Box::Box(Player& player)
{
	score = 0;
	this->setSize(sf::Vector2f(50, 50));
	this->setButtonTexture(&AssetManager::GetTexture(player.getTexturePath() + "22.png"), &AssetManager::GetTexture(player.getTexturePath() + "22.png"));
	this->change_texture_to_normal();
	state = Boxstate::occupied;
	owner = &player;
}

bool Box::setWall()
{
	//if the box is empty, set the box to wall
	if (state == Boxstate::non_occupied)
	{
		state = Boxstate::wall;
		this->setButtonTexture(&AssetManager::GetTexture("Texture/box_wall_1_1.png"), &AssetManager::GetTexture("Texture/box_wall_1_1.png"));
		this->change_texture_to_normal();
		return true;
	}
	//else, the box is occupied or wall, return false.
	return false;
}