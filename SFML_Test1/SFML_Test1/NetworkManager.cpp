#include "NetworkManager.h"
#include <iostream>	//debug
NetworkManager::NetworkManager()
{
	//set blocking to false
	listener.setBlocking(false);
	//tcpsocket.setBlocking(false);
	listener.listen(8310);
	
	bool_isListening = false;
    //assume it is client
    bool_isServer = false;
}

NetworkManager::~NetworkManager()
{
    //disconnect the socket?
}

void NetworkManager::EventHandle()
{
    //networkManager is avilable only when bool_isListening is true
    if(bool_isListening == true)
    {
        //if it is a server
        if(bool_isServer == true)
        {
            //if there is a connection request, accept it
            if (listener.accept(tcpsocket) == sf::Socket::Done)
            {
                std::cout << "New connection from" << tcpsocket.getRemoteAddress() << std::endl;
                //send the lobby information
				_Menu_InjectLobbyInfo(packet);
				tcpsocket.send(packet);
            }
        }
        //else, it is a client
        else
        {

        }
    }
}

void NetworkManager::Menu_startListening()
{
	bool_isListening = true;
    bool_isServer = true;
}

void NetworkManager::Menu_stopListening()
{
    bool_isServer = false;
    //close all client socket
    //....
    
}

void NetworkManager::Menu_tryConnect(const sf::String &ip)
{
	sf::IpAddress ipAdress(ip);
	
	if (tcpsocket.connect(ipAdress, 8310, sf::seconds(4)) == sf::Socket::Done)
	{
		std::cout << "connect success." << std::endl;
		//receive lobby's information.
		tcpsocket.receive(packet);
		_Menu_DecodeLobbyInfo(packet);

        bool_isListening = true;
	}
	else
	{
		std::cout << "cannot connect to the server." << std::endl;
	}
}

void NetworkManager::_Menu_InjectLobbyInfo(sf::Packet& packet)
{
	sf::String test("hello! Welcome to our Battle Turf server!");
	packet << test;
}

void NetworkManager::_Menu_DecodeLobbyInfo(sf::Packet& packet)
{
	sf::String test;
	packet >> test;
	std::cout << test.toAnsiString() << std::endl;
}

