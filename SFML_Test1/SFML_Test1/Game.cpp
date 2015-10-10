#include "Game.h"
TheGame::TheGame()
{
    
}

TheGame::TheGame(std::shared_ptr<NetworkManager> ptr1, std::shared_ptr<GameData> ptr2)
{
    ptrNet = ptr1;
    ptrData = ptr2;
}


void TheGame::Graphic_update(sf::RenderWindow* window)
{
    //draw the map
    window->draw(ptrData->getGameMap());
    
}

void TheGame::Mouse_moved_update(sf::Vector2i &mouseposition)
{
	//if the previousBox "exist", set that box to normal texture
	if (previousBox)
	{
		previousBox->change_texture_to_normal();
	}

	Box& hold = ptrData->getGameMap().getCurrentBox(mouseposition);

	//change the box where the cursor located to focus
	hold.change_texture_to_focus();

	//set pointer to that box, so that it can return to normal texture
	previousBox = &hold;
}

void TheGame::Mouse_clicked_update(sf::Vector2i &mouseposition)
{
	//ptrData->getGameMap().captureBox()
	ptrData->getGameMap().getCurrentBox(mouseposition).setFillColor(sf::Color::Blue);
}