#include <SFML/Network.hpp>
#include <vector>
#include "gameData.h"

class NetworkManager
{
private:
	sf::TcpListener listener;
	sf::TcpSocket tcpsocket;
	bool bool_isListening;
public:
	NetworkManager();

	//call at each frame
	void EventHandle();
	
	void Menu_startListening();
	void Menu_tryConnect(const sf::String &);

	//is the program listening?
	bool isListening(){ return bool_isListening; }

};