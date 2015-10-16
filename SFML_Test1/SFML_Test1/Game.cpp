#include "Game.h"

TheGame::TheGame()
{
    
}

TheGame::TheGame(std::shared_ptr<NetworkManager> ptr1, std::shared_ptr<GameData> ptr2)
{
    ptrNet = ptr1;
    ptrData = ptr2;
    previousBox = NULL;
    //set no player when started
    currentPlayer = NULL;
    
}


void TheGame::Graphic_update(sf::RenderWindow* window)
{
    //draw the map
    window->draw(ptrData->getGameMap());
    window->draw(userBox);
    window->draw(userBox.txt_score);
}

void TheGame::Mouse_moved_update(sf::Vector2i &mouseposition)
{

    //update the position of userBox
    userBox.setPosition(mouseposition.x + 10, mouseposition.y + 10);
    userBox.txt_score.setPosition(mouseposition.x + 15, mouseposition.y + 15);
    
	//if the previousBox "exist", set that box to normal texture
	if (previousBox)
	{
		previousBox->change_texture_to_normal();
	}

	Box& hold = ptrData->getGameMap().getCurrentBox(mouseposition);

	//if the box is not empty, return 
	{
		if (hold.getState() != Boxstate::non_occupied)
		{
			return;
		}
	}

	//change the box where the cursor located to focus
	hold.change_texture_to_focus();

	//set pointer to that box, so that it can return to normal texture
	previousBox = &hold;
}

void TheGame::Mouse_clicked_update(sf::Vector2i &mouseposition)
{
	//if the target box is capturable...
	if (ptrData->getGameMap().getCurrentBox(mouseposition).isCapturable())
	{
        //set the size to 50...
        userBox.setSize(sf::Vector2f(50,50));
        
        sf::Vector2f position = ptrData->getGameMap().getCurrentBox(mouseposition).getPosition();
		//set the new position for userBox
		userBox.setPosition(position);
        userBox.setFillColor(sf::Color(255,255,255,255));
		//set the score
        userBox.txt_score.setPosition(position.x + 5, position.y + 5);
        userBox.txt_score.setCharacterSize(30);
        userBox.txt_score.setColor(sf::Color(0,0,0,255));
		//copy the box into the map
		ptrData->getGameMap().captureBox(userBox, mouseposition);
		//next player move
		ptrData->NextPlayer();

	}
    
}

void TheGame::dataUpdate(sf::Vector2i &mouseposition)
{
    //if this function is called, that means the game has created.
    
    //get the current player
    Player& player= ptrData->getCurrentPlayer();
    
    //if the player is different, update to that player
    if(currentPlayer != &player)
    {
        currentPlayer = &player;
        
        //update the Box
        Box newUserBox(*currentPlayer);
        newUserBox.setSize(sf::Vector2f(70,70));
        newUserBox.setFillColor(sf::Color(255,255,255,150));
        newUserBox.setPosition(mouseposition.x + 10 , mouseposition.y + 10);
        newUserBox.setButtonTexture(&AssetManager::GetTexture(currentPlayer->getTexturePath() + "22.png"), &AssetManager::GetTexture(currentPlayer->getTexturePath() + "22.png"));
        newUserBox.setScore(currentPlayer->getNextScore());
        newUserBox.txt_score.setCharacterSize(50);
        newUserBox.txt_score.setPosition(mouseposition.x + 15, mouseposition.y + 15);
        newUserBox.txt_score.setColor(sf::Color(0,0,0,150));
        userBox = newUserBox;
    }
}
