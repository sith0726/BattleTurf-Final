#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <thread>

#include <iostream>		//debug message
#include "gameData.h"	//game data class
#include "menu.h"		//menu class
#include "Game.h"       //game class


/*Functions*/
void PlayIntro(sf::RenderWindow*);	//play introduction animation
void renderingThread(sf::RenderWindow*, std::shared_ptr<Menu>, std::shared_ptr<TheGame>, std::shared_ptr<GameData>);
void networkThread(sf::RenderWindow*, std::shared_ptr<NetworkManager>);
/*~~~~~~~~~*/

int main()
{
	// create the window (remember: it's safer to create it in the main thread due to OS limitations)
	sf::RenderWindow window(sf::VideoMode(600, 600), "Test", sf::Style::Close);

	//set frame limit
	window.setFramerateLimit(60);

	// deactivate its OpenGL context
	window.setActive(false);

	//declare game data
    std::shared_ptr<GameData> gameData(new GameData);

	//declare networkManager
	std::shared_ptr<NetworkManager> networkmanager(new NetworkManager(gameData));

	//pointer to the menu and the game
	std::shared_ptr<Menu> game_menu(new Menu(networkmanager, gameData));
    std::shared_ptr<TheGame> myGame(new TheGame(networkmanager, gameData));

	// launch the rendering thread
	std::thread thread(&renderingThread, &window, game_menu, myGame, gameData);
	// launch the networking thread
	std::thread thread1(&networkThread, &window, networkmanager);

	// the event loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.waitEvent(event))
		{
            
            //get the position of the mouse (in the window)
            sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
            
            //update the game data for game, if the game has started
            if(gameData->isGameCreated())
            {
                myGame->dataUpdate(mouseposition);
            }
            
			//if window close...
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//if mouse moved...
			if (event.type == sf::Event::MouseMoved)
			{
				//if the game state is intro
				if (gameData->getGameState() == intro)
				{
					//nothing...
				}
				//if the game state is menu
				else if (gameData->getGameState() == menu)
				{
					//call menu's mouse update function
					game_menu->Mouse_moved_update(mouseposition);
				}
				//if the game state is game
				else if (gameData->getGameState() == game)
				{
					//call game's mouse update function
					myGame->Mouse_moved_update(mouseposition);
				}
			}

			//if mosue clicked...
			if (event.type == sf::Event::MouseButtonPressed)
			{
				//get the position of the mouse (in the window)
				sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
				//if the game state is intro
				if (gameData->getGameState() == intro)
				{
					//nothing...
				}
				//if the game state is menu
				else if (gameData->getGameState() == menu)
				{
					//call menu's mouse clicked update function
					game_menu->Mouse_clicked_update(mouseposition);

					//if menu is terminated, close the window
					if (game_menu->getState() == terminated)
					{
						window.close();
					}
				}
				//if the game state is game
				else if (gameData->getGameState() == game)
				{
					//call game's mouse clicked update function
					myGame->Mouse_clicked_update(mouseposition);
				}
			}	

			//if keyboard pressed
			if (event.type == sf::Event::TextEntered)
			{
				if (gameData->getGameState() == intro)
				{
					//nothing...
				}
				else if (gameData->getGameState() == menu)
				{
					game_menu->KeyBoard_Press_update(static_cast<char>(event.text.unicode));
				}
				else if (gameData->getGameState() == game)
				{
                    //nothing...
				}
			}
            
            //if special key pressed
            if(event.type == sf::Event::KeyPressed)
            {
                if(gameData->getGameState() == game)
                    myGame->KeyBoard_Press_update();
            }
            
		}
	}
	thread.join();
	thread1.join();
	return 0;
}
//PlayIntro
void PlayIntro(sf::RenderWindow *window)
{
	sf::RectangleShape introImageRectangle;

	introImageRectangle.setTexture(&AssetManager::GetTexture("Texture/image_bt_2_1.png"));
	introImageRectangle.setPosition(200,250);
	introImageRectangle.setSize(sf::Vector2f(200,100));

	sf::Clock clock;
	sf::Time t1 = sf::milliseconds(6);

	//whiten the screen
	for (int i = 1; i < 255;)
	{
		window->clear(sf::Color::White);

		if (clock.getElapsedTime() > t1)
		{
			clock.restart();
			i++;
			introImageRectangle.setFillColor(sf::Color(i, i, i, i));
		}
		window->draw(introImageRectangle);
		window->display();
	}
	//wait 0.5 sec
	sf::Time t2 = sf::seconds(0.5);
	clock.restart();
	while (clock.getElapsedTime() < t2)
	{

	}
	//blacken the screen
	for (int i = 1; i < 255;)
	{
		window->clear(sf::Color::White);

		if (clock.getElapsedTime() > t1)
		{
			clock.restart();
			i++;
			introImageRectangle.setFillColor(sf::Color(255, 255, 255, 255 - i));
		}

		window->draw(introImageRectangle);

		window->display();
	}
}

//renderingThread
void renderingThread(sf::RenderWindow* window, std::shared_ptr<Menu> ptrmenu, std::shared_ptr<TheGame> myGame, std::shared_ptr<GameData> gameData)
{
	
	// the rendering loop
	while (window->isOpen())
	{
		//clear...
		window->clear(sf::Color::White);

		//if the game state is "intro", play the introduction animation.
		if (gameData->getGameState() == Game_State::intro)
		{
			//PlayIntro(window);
			//when done, swith to menu phase.
            gameData->setGameState(Game_State::menu);
		}
		//if the game state is "menu", render menu graphics.
		else if (gameData->getGameState() == Game_State::menu)
		{
			// make sure menu exist...
			if (ptrmenu)
			{
                ptrmenu->Graphic_update(window);
			}		
		}
		//if the game state is "game", render the game graphics.
		else if (gameData->getGameState() == Game_State::game)
		{
			// draw...
            myGame->Graphic_update(window);
		}
		// end the current frame
		window->display();
	}
	
}

//networking thread
void networkThread(sf::RenderWindow *window, std::shared_ptr<NetworkManager> networkmanager)
{
    //the networkHandler only works when window is open
	while (window->isOpen())
	{
        networkmanager->EventHandle();
	}
}
