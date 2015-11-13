#include "menu.h"
#include <iostream>

Menu::Menu()
{
	LoadAsset();
}

Menu::Menu(std::shared_ptr<NetworkManager>& ptrnetwork, std::shared_ptr<GameData>& ptrdata)
{
	//initialization
	//the menu state starts at mainmenu.
	menu_state = mainmenu;
	//set pointers
	ptrNetworkManager = ptrnetwork;
	ptrGameData = ptrdata;
	LoadAsset();
}

void Menu::LoadAsset()
{
	//gameTitle and its texture
	gameTitle.setPosition(sf::Vector2f(100, 0));
	gameTitle.setSize(sf::Vector2f(400, 300));
	gameTitle.setTexture(&AssetManager::GetTexture("Texture/image_text_3_2.png"));
	//start button
	startButton.setSize(sf::Vector2f(150, 75));
	startButton.setPosition(sf::Vector2f(225, 350));
	startButton.setButtonTexture(&AssetManager::GetTexture("Texture/button_start_2_1.png"),
		&AssetManager::GetTexture("Texture/button_start_focus_2_1.png"));
	startButton.change_texture_to_normal();
	//exit button
	exitButton.setSize(sf::Vector2f(150, 75));
	exitButton.setPosition(sf::Vector2f(225, 450));
	exitButton.setButtonTexture(&AssetManager::GetTexture("Texture/button_exit_2_1.png"),
		&AssetManager::GetTexture("Texture/button_exit_focus_2_1.png"));
	exitButton.change_texture_to_normal();
	//client button
	clientButton.setSize(sf::Vector2f(150, 50));
	clientButton.setPosition(sf::Vector2f(225, 300));
	clientButton.setButtonTexture(&AssetManager::GetTexture("Texture/button_client_4_1.png"),
		&AssetManager::GetTexture("Texture/button_client_focus_4_1.png"));
	clientButton.change_texture_to_normal();
	//host button
	hostButton.setSize(sf::Vector2f(150, 50));
	hostButton.setPosition(sf::Vector2f(225, 400));
	hostButton.setButtonTexture(&AssetManager::GetTexture("Texture/button_host_4_1.png"),
		&AssetManager::GetTexture("Texture/button_host_focus_4_1.png"));
	hostButton.change_texture_to_normal();
	//back Button
	backButton.setSize(sf::Vector2f(150, 50));
	backButton.setPosition(sf::Vector2f(225, 500));
	backButton.setButtonTexture(&AssetManager::GetTexture("Texture/button_back_4_1.png"),
		&AssetManager::GetTexture("Texture/button_back_focus_4_1.png"));
	backButton.change_texture_to_normal();
	//client/host back Button
	clientHostBackButton.setSize(sf::Vector2f(150, 50));
	clientHostBackButton.setPosition(sf::Vector2f(100, 500));
	clientHostBackButton.setButtonTexture(&AssetManager::GetTexture("Texture/button_back_4_1.png"),
		&AssetManager::GetTexture("Texture/button_back_focus_4_1.png"));
	clientHostBackButton.change_texture_to_normal();
	//client/host next Button
	clientHostNextButton.setSize(sf::Vector2f(150, 50));
	clientHostNextButton.setPosition(sf::Vector2f(350, 500));
	clientHostNextButton.setButtonTexture(&AssetManager::GetTexture("Texture/button_next_4_1.png"),
		&AssetManager::GetTexture("Texture/button_next_focus_4_1.png"));
	clientHostNextButton.change_texture_to_normal();

	//EnterIP String
	txt_EnterIP.setCharacterSize(40);
	txt_EnterIP.setPosition(sf::Vector2f(150, 325));
	txt_EnterIP.setString("Enter IP:");
	txt_EnterIP.setColor(sf::Color::Black);
	txt_EnterIP.setFont(AssetManager::GetFont("Texture/arial.ttf"));

	//IP input box in client
	IPinputbox.setPosition(sf::Vector2f(150, 400));
	IPinputbox.setSize(sf::Vector2f(300, 50));
	IPinputbox.setFillColor(sf::Color::White);
	IPinputbox.setOutlineThickness(2);
	IPinputbox.setOutlineColor(sf::Color::Black);

	//IP server IP in client
	txt_serverIP.setPosition(sf::Vector2f(150, 400));
	txt_serverIP.setCharacterSize(40);
	txt_serverIP.setColor(sf::Color::Black);
	txt_serverIP.setFont(AssetManager::GetFont("Texture/arial.ttf"));

	//lobby player's color
	PIC_lobby_Playercolor[0].setPosition(sf::Vector2f(150, 300));
	PIC_lobby_Playercolor[0].setTexture(&AssetManager::GetTexture("Texture/box_blue_1_22.png"));
	PIC_lobby_Playercolor[0].setSize(sf::Vector2f(50, 50));

	PIC_lobby_Playercolor[1].setPosition(sf::Vector2f(150, 350));
	PIC_lobby_Playercolor[1].setTexture(&AssetManager::GetTexture("Texture/box_red_1_22.png"));
	PIC_lobby_Playercolor[1].setSize(sf::Vector2f(50, 50));

	PIC_lobby_Playercolor[2].setPosition(sf::Vector2f(150, 400));
	PIC_lobby_Playercolor[2].setTexture(&AssetManager::GetTexture("Texture/box_green_1_22.png"));
	PIC_lobby_Playercolor[2].setSize(sf::Vector2f(50, 50));

	PIC_lobby_Playercolor[3].setPosition(sf::Vector2f(150, 450));
	PIC_lobby_Playercolor[3].setTexture(&AssetManager::GetTexture("Texture/box_yellow_1_22.png"));
	PIC_lobby_Playercolor[3].setSize(sf::Vector2f(50, 50));

	//lobby player's state
	lobby_Players_state[0].setPosition(sf::Vector2f(200, 300));
	lobby_Players_state[0].setSize(sf::Vector2f(250, 50));
	lobby_Players_state[0].setButtonTexture(&AssetManager::GetTexture("Texture/menu_Player1.png"), &AssetManager::GetTexture("Texture/menu_Player1.png"));
	lobby_Players_state[0].change_texture_to_normal();

	lobby_Players_state[1].setPosition(sf::Vector2f(200, 350));
	lobby_Players_state[1].setSize(sf::Vector2f(250, 50));
	lobby_Players_state[1].setButtonTexture(&AssetManager::GetTexture("Texture/menu_Player2.png"), &AssetManager::GetTexture("Texture/menu_Player2.png"));
	lobby_Players_state[1].change_texture_to_normal();

	lobby_Players_state[2].setPosition(sf::Vector2f(200, 400));
	lobby_Players_state[2].setSize(sf::Vector2f(250, 50));;
	lobby_Players_state[2].setButtonTexture(&AssetManager::GetTexture("Texture/menu_Player3.png"), &AssetManager::GetTexture("Texture/menu_Player3.png"));
	lobby_Players_state[2].change_texture_to_normal();

	lobby_Players_state[3].setPosition(sf::Vector2f(200, 450));
	lobby_Players_state[3].setSize(sf::Vector2f(250, 50));
	lobby_Players_state[3].setButtonTexture(&AssetManager::GetTexture("Texture/menu_Player4.png"), &AssetManager::GetTexture("Texture/menu_Player4.png"));
	lobby_Players_state[3].change_texture_to_normal();

	//Player's name
	PlayerName[0].setPosition(sf::Vector2f(250, 300));
	PlayerName[0].setCharacterSize(40);
	PlayerName[0].setString("Player1");
	PlayerName[0].setFont(AssetManager::GetFont("Texture/arial.ttf"));
	PlayerName[0].setColor(sf::Color::Black);

	PlayerName[1].setPosition(sf::Vector2f(250, 350));
	PlayerName[1].setCharacterSize(40);
	PlayerName[1].setString("Player2");
	PlayerName[1].setFont(AssetManager::GetFont("Texture/arial.ttf"));
	PlayerName[1].setColor(sf::Color::Black);

	PlayerName[2].setPosition(sf::Vector2f(250, 400));
	PlayerName[2].setCharacterSize(40);
	PlayerName[2].setString("Player3");
	PlayerName[2].setFont(AssetManager::GetFont("Texture/arial.ttf"));
	PlayerName[2].setColor(sf::Color::Black);

	PlayerName[3].setPosition(sf::Vector2f(250, 450));
	PlayerName[3].setCharacterSize(40);
	PlayerName[3].setString("Player4");
	PlayerName[3].setFont(AssetManager::GetFont("Texture/arial.ttf"));
	PlayerName[3].setColor(sf::Color::Black);
}

void Menu::Graphic_update(sf::RenderWindow *window)
{
	//in main menu, show the background, gameTitle, start and exit button.
	if (menu_state == mainmenu)
	{
		window->draw(gameTitle);
		window->draw(startButton);
		window->draw(exitButton);
	}
	//in setting1, show the background, gameTitle, client or host button.
	else if (menu_state == setting1)
	{
		window->draw(gameTitle);
		window->draw(clientButton);
		window->draw(hostButton);
		window->draw(backButton);
	}
	//in client
	else if (menu_state == multiplayer_client)
	{
		window->draw(gameTitle);
		window->draw(clientHostBackButton);
		window->draw(clientHostNextButton);
		window->draw(txt_EnterIP);
		window->draw(IPinputbox);
		window->draw(txt_serverIP);
	}
	//in host
	else if (menu_state == multiplayer_lobby_host)
	{
		window->draw(gameTitle);
		window->draw(clientHostBackButton);
        //do not show the next button unless it has more than 2 players
        if(ptrGameData->getPlayerNumber() > 1)
        {
            window->draw(clientHostNextButton);
        }
		//show player info
        for(int i = 0 ; i < ptrGameData->getPlayerNumber(); i++)
        {
            window->draw(PIC_lobby_Playercolor[i]);
            window->draw(lobby_Players_state[i]);
            window->draw(PlayerName[i]);
        }
	}
	//in client lobby
	else if (menu_state == multiplayer_lobby_client)
	{
		if (!ptrNetworkManager->isConnected())
		{
			menu_state = Menu_state::mainmenu;
			ptrGameData->RebuildPlayer(1);
		}
		window->draw(gameTitle);
		window->draw(clientHostBackButton);

		//show player info
		for (int i = 0; i < ptrGameData->getPlayerNumber(); i++)
		{
			window->draw(PIC_lobby_Playercolor[i]);
			window->draw(lobby_Players_state[i]);
			window->draw(PlayerName[i]);
		}
	}
}
//call when mouse move...
void Menu::Mouse_moved_update(sf::Vector2i &mouseposition)
{
	//in mainmenu...
	if (menu_state == mainmenu)
	{
		//if the mouse is on the start button, change the texture to focus
		if (startButton.isCursor_on_button(mouseposition))
		{
			startButton.change_texture_to_focus();
		}
		//else, change to normal
		else
		{
			startButton.change_texture_to_normal();
		}

		//if the niyse is on the exit button, change the texture to focus
		if (exitButton.isCursor_on_button(mouseposition))
		{
			exitButton.change_texture_to_focus();
		}
		//else, change it to normal
		else
		{
			exitButton.change_texture_to_normal();
		}
	}
	//in setting1
	else if (menu_state == setting1)
	{
		//if the mouse is on the host button, change its texture to focus
		if (hostButton.isCursor_on_button(mouseposition))
		{
			hostButton.change_texture_to_focus();
		}
		//else, change to normal
		else
		{
			hostButton.change_texture_to_normal();
		}

		if (clientButton.isCursor_on_button(mouseposition))
		{
			clientButton.change_texture_to_focus();
		}
		else
		{
			clientButton.change_texture_to_normal();
		}

		if (backButton.isCursor_on_button(mouseposition))
		{
			backButton.change_texture_to_focus();
		}
		else
		{
			backButton.change_texture_to_normal();
		}
	}
	//in client
	else if (menu_state == multiplayer_client)
	{
		if (clientHostBackButton.isCursor_on_button(mouseposition))
		{
			clientHostBackButton.change_texture_to_focus();
		}
		else
		{
			clientHostBackButton.change_texture_to_normal();
		}

		if (clientHostNextButton.isCursor_on_button(mouseposition))
		{
			clientHostNextButton.change_texture_to_focus();
		}
		else
		{
			clientHostNextButton.change_texture_to_normal();
		}
	}
	//in host
	else if (menu_state == multiplayer_lobby_host)
	{
		if (clientHostBackButton.isCursor_on_button(mouseposition))
		{
			clientHostBackButton.change_texture_to_focus();
		}
		else
		{
			clientHostBackButton.change_texture_to_normal();
		}

		if (clientHostNextButton.isCursor_on_button(mouseposition))
		{
			clientHostNextButton.change_texture_to_focus();
		}
		else
		{
			clientHostNextButton.change_texture_to_normal();
		}
	}
	//in client lobby
	else if (menu_state == multiplayer_lobby_client)
	{
		if (clientHostBackButton.isCursor_on_button(mouseposition))
		{
			clientHostBackButton.change_texture_to_focus();
		}
		else
		{
			clientHostBackButton.change_texture_to_normal();
		}

		if (clientHostNextButton.isCursor_on_button(mouseposition))
		{
			clientHostNextButton.change_texture_to_focus();
		}
		else
		{
			clientHostNextButton.change_texture_to_normal();
		}
	}
}
//call when mouse clicked on something...
void Menu::Mouse_clicked_update(sf::Vector2i &mouseposition)
{
	//in mainmenu
	if (menu_state == mainmenu)
	{
		//if the mosue is on the startButton, change the menu_state to setting1.
		if (startButton.isCursor_on_button(mouseposition))
		{
			menu_state = setting1;
		}
		//if the mouse is on the exitButton, cchange the menu_state to terminated.
		else if (exitButton.isCursor_on_button(mouseposition))
		{
			menu_state = terminated;
		}
	}
	//in setting1
	else if (menu_state == setting1)
	{
		//if the mouse is on the host, change the menu_state to multiplayer_lobby_host
		if (hostButton.isCursor_on_button(mouseposition))
		{
			//starting listening the socket
			ptrNetworkManager->Menu_startListening();
			//change menu state to lobby
			menu_state = multiplayer_lobby_host;
		}
		//if the mouse is on the client, change the menu_state to multiplayer_client
		else if (clientButton.isCursor_on_button(mouseposition))
		{
			menu_state = multiplayer_client;
		}
		//if the mouse is on the back button, change the menu_state to mainmenu
		else if (backButton.isCursor_on_button(mouseposition))
		{
			menu_state = mainmenu;
		}
	}
	//in client
	else if (menu_state == multiplayer_client)
	{
		//if the mouse is on the back, change the menu_state to setting1
		if (clientHostBackButton.isCursor_on_button(mouseposition))
		{
			menu_state = setting1;
		}
		//if the mouse is on the next, try connection.
		else if (clientHostNextButton.isCursor_on_button(mouseposition))
		{
			//try connect...if success, change menu state to multiplayer_lobby_clinet
			if (ptrNetworkManager->Menu_tryConnect(serverIP))
			{
				menu_state = multiplayer_lobby_client;
			}
		}
	}
	//in host
	else if (menu_state == multiplayer_lobby_host)
	{
		//if the mouse is on the back, change the menu_state to setting1
		if (clientHostBackButton.isCursor_on_button(mouseposition))
		{
			//if there are players in the lobby, notify them
			ptrNetworkManager->Servershutdown();
			ptrNetworkManager->Menu_stopListening();
			//clean the player list
			ptrGameData->RebuildPlayer(1);
			//go back to menu setting1
			menu_state = setting1;
		}
		//if the mouse is on the next...!!nothing happen if there is only 1 player
		else if (clientHostNextButton.isCursor_on_button(mouseposition) && ptrGameData->getPlayerNumber() > 1)
		{
			//if players are ready, pass the data to game class and start the game.
            //create game
            //ptrGameData->NewGame();
            
            //send the game context, including map, playerinfo... to each player
            //...
			ptrNetworkManager->Menu_startGame();

            //change the menu_state to end_ingame
            ptrGameData->setGameState(Game_State::game);
		}
	}
	//in client lobby
	else if(menu_state == multiplayer_lobby_client)
	{
		//if the mouse is on the back, change the menu_state to setting1
		if (clientHostBackButton.isCursor_on_button(mouseposition))
		{
			//disconnect...
			ptrNetworkManager->Menu_disconnect();
			
			//go back to menu setting1
			menu_state = setting1;
		}
		//if the mouse is on the next...!!only available when server sent OK signal
		else if (clientHostNextButton.isCursor_on_button(mouseposition))
		{
			//if server sent ok signal
			//...
		}
	}
}
//KeyBoard pressed
void Menu::KeyBoard_Press_update(const char &input)
{
	if (menu_state == multiplayer_client)
	{
		ModifyIP(input);
	}
}

//Modify IP in client phase
void Menu::ModifyIP(const char &key)
{
	if (serverIP.getSize() < 15)
	{
		//if it is 0~9
		if (key >= 48 && key <= 57)
		{
			serverIP += key;
		}

		//if it is period '.'
		if (key == 46)
		{
			serverIP += '.';
		}
	}
	//if it is backspace
	if (key == 8)
	{
		if (!serverIP.isEmpty())
			serverIP.erase(serverIP.getSize() - 1, 1);
	}
	//update the text
	txt_serverIP.setString(serverIP);
}
