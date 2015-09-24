#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <thread>

#include <iostream>		//debug message
#include "gameData.h"	//game data class
#include "menu.h"		//menu class

//declare the game state
enum Game_State{intro, menu, game};
Game_State game_state;

/*Functions*/
void PlayIntro(sf::RenderWindow*);	//play introduction animation
void renderingThread(sf::RenderWindow*, Menu*);
/*~~~~~~~~~*/

int main()
{
	// create the window (remember: it's safer to create it in the main thread due to OS limitations)
	sf::RenderWindow window(sf::VideoMode(600, 600), "Test", sf::Style::Close);

	//set frame limit
	window.setFramerateLimit(60);

	// deactivate its OpenGL context
	window.setActive(false);

	//declare game state, starting with introduction.
	game_state = Game_State::intro;

	//declare game data
	GameData gameData;

	//pointer to the menu and the game
	Menu game_menu;
	//TheGame *game_thegame;

	// launch the rendering thread
	std::thread thread(&renderingThread, &window, &game_menu);

	// the event loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.waitEvent(event))
		{
			//if window close...
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//if mouse moved...
			if (event.type == sf::Event::MouseMoved)
			{
				//get the position of the mouse (in the window)
				sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
				//if the game state is intro
				if (game_state == intro)
				{
					//nothing...
				}
				//if the game state is menu
				else if (game_state == menu)
				{
					//call menu's mouse update function
					game_menu.Mouse_moved_update(mouseposition);
				}
				//if the game state is game
				else if (game_state == game)
				{
					//call game's mouse update function
				}
			}

			//if mosue clicked...
			if (event.type == sf::Event::MouseButtonPressed)
			{
				//get the position of the mouse (in the window)
				sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
				//if the game state is intro
				if (game_state == intro)
				{
					//nothing...
				}
				//if the game state is menu
				else if (game_state == menu)
				{
					//call menu's mouse clicked update function
					game_menu.Mouse_clicked_update(mouseposition);

					//if menu is terminated, close the window
					if (game_menu.getState() == terminated)
					{
						window.close();
					}
				}
				//if the game state is game
				else if (game_state == game)
				{
					//call game's mouse clicked update function
				}
			}	

			//if keyboard pressed
			if (event.type == sf::Event::KeyPressed)
			{
				if (game_state == intro)
				{
					//nothing...
				}
				else if (game_state == menu)
				{
					//game_menu.KeyBoard_Press_update();
				}
				else if (game_state == game)
				{
					//nothing...
				}
			}
		}
	}
	thread.join();
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
void renderingThread(sf::RenderWindow* window, Menu *ptrmenu)
{
	// the rendering loop
	while (window->isOpen())
	{
		//clear...
		window->clear(sf::Color::White);

		//if the game state is "intro", play the introduction animation.
		if (game_state == Game_State::intro)
		{
			//PlayIntro(window);
			//when done, swith to menu phase.
			game_state = menu;
		}
		//if the game state is "menu", render menu graphics.
		else if (game_state == Game_State::menu)
		{
			// make sure menu exist...
			if (ptrmenu)
			{
				//draw...
				ptrmenu->Graphic_update(window);
			}		
		}
		//if the game state is "game", render the game graphics.
		else if (game_state == Game_State::game)
		{
			// draw...


		}
		// end the current frame
		window->display();
	}
}
