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
			//if a player disconnect, remove it

            //if there is a connection request and the lobby is not full, accept it
            if (listener.accept(tcpsocket) == sf::Socket::Done && ptrData->getPlayerNumber() < 4)
            {
                std::cout << "New connection from" << tcpsocket.getRemoteAddress() << std::endl;
                
				//add one player to the data
				Player newPlayer;
				ptrData->InsertPlayer(newPlayer);

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

bool NetworkManager::Menu_tryConnect(const sf::String &ip)
{
    //if ip string is empty, nothing happen
    if (ip.isEmpty())
    {
		return false;
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
		return true;
	}
	else
	{
		std::cout << "cannot connect to the server." << std::endl;
		return false;
	}
}

void NetworkManager::_Menu_InjectLobbyInfo(sf::Packet& packet)
{
	sf::String test("hello! Welcome to Battle Turf server!");
    int playercount = ptrData->getPlayerNumber();  //get the player number
}

void NetworkManager::_Menu_DecodeLobbyInfo(sf::Packet& packet)
{
	sf::String test;
    int playercount;
	packet >> test;
	std::cout << test.toAnsiString() << std::endl;
	packet >> playercount;
	std::cout << "There are " << playercount << "Players." << std::endl;
	//update players
	//temporary...remove this after test
	Player samplePlayer;
	ptrData->InsertPlayer(samplePlayer);
	//temporary...
}

void NetworkManager::Menu_disconnect()
{
	tcpsocket.disconnect();
}

