#ifndef _NETWORKMANAGER_
#define _NETWORKMANAGER_

#include <SFML/Network.hpp>
#include <algorithm>
#include <vector>
#include <deque>
#include "gameData.h"

/*define the content of the packet
Lobby_info = update the lobby's information
client_OK  = client is ready for the game
Game_start = the game starts, send the map settings, player's order...
Game_update = update the currnet map, player's order...
Game_currentbox = update other players location
Disconnect_request = a client tries to desconnect from server
ShutDown_warning = the server is shutting down.
*/
enum PacketInfo{Lobby_info,Disconnect_request};

//overlad the operator <<
template <typename Enum>
typename std::enable_if<std::is_enum<Enum>::value, sf::Packet&>::type
operator<< (sf::Packet& packet, Enum t)
{
	return packet << static_cast<typename std::underlying_type<Enum>::type>(t);
}

//overload the operator >>
template <typename Enum>
typename std::enable_if<std::is_enum<Enum>::value, sf::Packet&>::type
operator>> (sf::Packet& packet, Enum& t)
{
	typename std::underlying_type<Enum>::type i;
	packet >> i;
	t = static_cast<Enum>(i);
	return packet;
}

class NetworkManager
{
private:
	sf::TcpListener listener;
	std::list<std::unique_ptr<sf::TcpSocket>> tcpsocketlist;
    sf::TcpSocket tcpsocket;
	bool bool_isAvailable;
    bool bool_isServer;  // true = server, false = client.
    //sf::Packet packet;  //SFML packet for sending data
    
    std::shared_ptr<GameData> ptrData;  //pointer to game data

	void _Menu_SendLobbyInfo(std::unique_ptr<sf::TcpSocket>&, const int&);
	void _Menu_DecodeLobbyInfo(sf::Packet&);

	void server_Checksocket(sf::TcpSocket&);
public:
	NetworkManager();
    NetworkManager(std::shared_ptr<GameData>&);
    
    ~NetworkManager();

	//call at each frame
	void EventHandle();
	
    //Menu functions
	void Menu_startListening();
    void Menu_stopListening();
	bool Menu_tryConnect(const sf::String &);
	void Menu_disconnect();
    void Menu_clientReady();        //the client is ready for the game
    void Menu_startGame();          //the menu send the content of map and other stuff...

	//is the program listening?
	bool isAvailable(){ return bool_isAvailable; }

};
#endif