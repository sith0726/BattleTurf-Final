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
	txt_score.setCharacterSize(30);
	txt_score.setColor(sf::Color::Black);
	txt_score.setFont(AssetManager::GetFont("Texture/arial.ttf"));
}

//set the score of the box, also renew the position of the txt_score
void Box::setScore(const int& newScore)
{
	score = newScore;
	txt_score.setPosition(sf::Vector2f(this->getPosition().x + 5, this->getPosition().y + 5));
	txt_score.setString(std::to_string(score));
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

sf::Packet& operator<<(sf::Packet& packet, const Box& box)
{
    //insert the state
    if(box.state == Boxstate::non_occupied)
    {
        packet << 0;
    }
    else if(box.state == Boxstate::occupied)
    {
        packet << 1;
    }
    else if(box.state == Boxstate::wall)
    {
        packet << 2;
    }
    
    //insert the score
    packet << box.score;
    
    //insert the owner
    //...
    
    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Box& box)
{
    //get the state
    int state;
    packet >> state;
    if(state == 0)
    {
        box.state = Boxstate::non_occupied;
    }
    else if(state == 1)
    {
        box.state = Boxstate::occupied;
    }
    else if(state == 2)
    {
        box.state = Boxstate::wall;
    }
    
    //get the score
    int score = 0;
    packet >> score;
    box.score = score;
    
    //get the owner
    //...
    
    return packet;
}