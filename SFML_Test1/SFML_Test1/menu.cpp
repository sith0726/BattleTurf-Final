#include "menu.h"
#include <iostream>

Menu::Menu()
{
	//initialization
	//the menu state starts at mainmenu.
	menu_state = mainmenu;
	//background
	background.setSize(sf::Vector2f(600, 600));
	background.setFillColor(sf::Color::White);
	background.setPosition(sf::Vector2f(0, 0));
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

	
	//Text...font...
	font.loadFromFile("arial.ttf");
	//EnterIP String
	EnterIP.setCharacterSize(40);
	EnterIP.setPosition(sf::Vector2f(200, 300));
	EnterIP.setString("Enter IP:");
	EnterIP.setColor(sf::Color::Black);
	EnterIP.setFont(font);

	//IP input box in client
	IPinputbox.setPosition(sf::Vector2f(200, 400));
	IPinputbox.setSize(sf::Vector2f(200, 50));
	IPinputbox.setFillColor(sf::Color::White);
	IPinputbox.setOutlineThickness(2);
	IPinputbox.setOutlineColor(sf::Color::Black);
}

void Menu::Graphic_update(sf::RenderWindow *window)
{
	//in main menu, show the background, gameTitle, start and exit button.
	if (menu_state == mainmenu)
	{
		window->draw(background);
		window->draw(gameTitle);
		window->draw(startButton);
		window->draw(exitButton);
	}
	//in setting1, show the background, gameTitle, client or host button.
	else if (menu_state == setting1)
	{
		window->draw(background);
		window->draw(gameTitle);
		window->draw(clientButton);
		window->draw(hostButton);
		window->draw(backButton);
	}
	//in client
	else if (menu_state == multiplayer_client)
	{
		window->draw(background);
		window->draw(gameTitle);
		window->draw(clientHostBackButton);
		window->draw(clientHostNextButton);
		window->draw(EnterIP);
		window->draw(IPinputbox);
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
			//try connent...
		}
	}
}