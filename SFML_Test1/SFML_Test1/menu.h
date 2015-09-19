#include <SFML/Graphics.hpp>
#include "Button.h"
#include "gameData.h"

enum Menu_state{
	mainmenu = 1,
	setting1 = 2,
	multiplayer_client = 3,
	multiplayer_lobby_host = 4,
	multiplayer_lobby_client = 5,
	end_ingame = 6,
	terminated = 7
};
class Menu
{
private:
	Menu_state menu_state;
	//Graphics
	sf::RectangleShape background;

	sf::Texture gameTitle_Texture;
	sf::RectangleShape gameTitle;
	//main menu
	Button startButton;
	Button exitButton;
	//setting1
	Button clientButton;
	Button hostButton;
	Button backButton;
	//client/host back button
	Button clientHostBackButton;
	//client/host next button
	Button clientHostNextButton;
	//client text:enter IP
	sf::Font font;
	sf::Text EnterIP;
	
	//IP input box in client
	sf::RectangleShape IPinputbox;
public:
	//
	Menu();
	//get the menu state
	Menu_state getState(){ return menu_state; }
	//call in graphic update
	void Graphic_update(sf::RenderWindow*);
	//call in mouse-moved event
	void Mouse_moved_update(sf::Vector2i &mouseposition);
	//call in mouse-clicked event
	void Mouse_clicked_update(sf::Vector2i &mouseposition);
};