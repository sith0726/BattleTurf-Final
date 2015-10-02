#include <SFML/Network.hpp>
#include <vector>
#include "gameData.h"

class NetworkManager
{
private:
	sf::TcpListener listener;
	sf::TcpSocket tcpsocket;
	bool bool_isListening;
    bool bool_isServer;  // true = server, false client.
    sf::Packet packet;  //SFML packet for sending data
public:
	NetworkManager();
    ~NetworkManager();

	//call at each frame
	void EventHandle();
	
	void Menu_startListening();
    void Menu_stopListening();
	void Menu_tryConnect(const sf::String &);

	//is the program listening?
	bool isListening(){ return bool_isListening; }

};