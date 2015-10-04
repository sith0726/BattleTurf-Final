#include "NetworkManager.h"
#include <iostream>	//debug
NetworkManager::NetworkManager()
{
    
}

NetworkManager::NetworkManager(std::shared_ptr<GameData>& ptr)
{
    //set pointer
    ptrData = ptr;
    //set blocking to false
    listener.setBlocking(false);
    //when started, the network is not used
    bool_isAvailable = false;
    //assume it is client
    bool_isServer = false;
    
}

NetworkManager::~NetworkManager()
{
    //disconnect the socket?
}

void NetworkManager::EventHandle()
{
    //networkManager is avilable only when bool_isAvailable is true
    if(bool_isAvailable == true )
    {
        //if it is a server
        if(bool_isServer == true)
        {
            //if there is a connection request and the lobby is not full, accept it
            if (listener.accept(tcpsocket) == sf::Socket::Done && ptrData->getPlayerNumber() < 4)
            {
                std::cout << "New connection from" << tcpsocket.getRemoteAddress() << std::endl;
                
                //send the lobby information
				_Menu_InjectLobbyInfo(packet);
				tcpsocket.send(packet);
                //add one player to the data
                Player newPlayer;
                ptrData->InsertPlayer(newPlayer);
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
    //start listening, bind the port 8310
    listener.listen(8310);
    bool_isAvailable = true;
    bool_isServer = true;
}

void NetworkManager::Menu_stopListening()
{
    //no longer a server
    bool_isServer = false;
    //close all client socket
    listener.close();
    
    //...tcpsocket.disconnect();
    
    bool_isAvailable = false;
}

void NetworkManager::Menu_tryConnect(const sf::String &ip)
{
    //if ip string is empty, nothing happen
    if (ip.isEmpty())
    {
        return;
    }
    
    //declare an ip address
	sf::IpAddress ipAdress(ip);
	
    //try to connect the server, allow 4 seconds to wait
	if (tcpsocket.connect(ipAdress, 8310, sf::seconds(4)) == sf::Socket::Done)
	{
		std::cout << "connect success." << std::endl;
		//receive lobby's information.
		tcpsocket.receive(packet);
		_Menu_DecodeLobbyInfo(packet);

        bool_isAvailable = true;
	}
	else
	{
		std::cout << "cannot connect to the server." << std::endl;
	}
}

void NetworkManager::_Menu_InjectLobbyInfo(sf::Packet& packet)
{
	sf::String test("hello! Welcome to our Battle Turf server!");
    sf::Int8 playercount = ptrData->getPlayerNumber();  //get the player number
	packet << test << playercount;
}

void NetworkManager::_Menu_DecodeLobbyInfo(sf::Packet& packet)
{
	sf::String test;
    sf::Int8 playercount;
	packet >> test >> playercount;
	std::cout << test.toAnsiString() << playercount << std::endl;
}

