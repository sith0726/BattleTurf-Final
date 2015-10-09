#include "Box.h"

//constructor
Box::Box()
{
    score = 0;
    state = non_occupied;
    this->setSize(sf::Vector2f(50,50));
    this->setTexture(&AssetManager::GetTexture("Texture/box_empty_1_1.png"));
}
