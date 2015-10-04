#ifndef _NETWORKMANAGER_
#define _NETWORKMANAGER_

#include <SFML/Network.hpp>
#include <vector>
#include "gameData.h"

class NetworkManager
{
private:
	sf::TcpListener listener;
    //std::list<sf::TcpSocket> tcpsocket;
    sf::TcpSocket tcpsocket;
	bool bool_isAvailable;
    bool bool_isServer;  // true = server, false client.
    sf::Packet packet;  //SFML packet for sending data
    
    std::shared_ptr<GameData> ptrData;  //pointer to game data

	void _Menu_InjectLobbyInfo(sf::Packet&);
	void _Menu_DecodeLobbyInfo(sf::Packet&);
public:
	NetworkManager();
    NetworkManager(std::shared_ptr<GameData>&);
    
    ~NetworkManager();

	//call at each frame
	void EventHandle();
	
	void Menu_startListening();
    void Menu_stopListening();
	void Menu_tryConnect(const sf::String &);
	

	//is the program listening?
	bool isAvailable(){ return bool_isAvailable; }

};
#endif