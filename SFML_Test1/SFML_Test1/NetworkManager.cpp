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
			std::unique_ptr<sf::TcpSocket> tcphold(new sf::TcpSocket);
			tcphold->setBlocking(false); 

			if (listener.accept(*tcphold) == sf::Socket::Done)
			{
				std::cout << "New connection from " << tcphold->getRemoteAddress() << "." << std::endl;

				tcpsocketlist.push_back(std::move(tcphold));

				ptrData->AddPlayer();

				//update menu info
				int tempIndex = 1;
				for (std::unique_ptr<sf::TcpSocket> &socket : tcpsocketlist)
				{
					_Menu_SendLobbyInfo(socket, tempIndex);
					tempIndex++;
				}
			}

			//check if a packet is received
			for (std::list<std::unique_ptr<sf::TcpSocket>>::iterator it = tcpsocketlist.begin(); it != tcpsocketlist.end(); )
			{
				sf::Packet newPacket;
				if ((*it)->receive(newPacket) == sf::Socket::Done)
				{
					PacketInfo info;
					newPacket >> info;
					switch (info)
					{
                    case PacketInfo::Lobby_info:
                            break;
                            
					case PacketInfo::Disconnect_request:
						int playerindex;
						newPacket >> playerindex;
						ptrData->RemovePlayer(playerindex);
						it = tcpsocketlist.erase(it);

						//send update menu info to all players
						int tempIndex = 1;
						for (std::unique_ptr<sf::TcpSocket> &socket : tcpsocketlist)
						{
							_Menu_SendLobbyInfo(socket, tempIndex);
							tempIndex++;
						}
						break;
					}
				}

				if (it != tcpsocketlist.end())
				{
					it++;
				}
			}
        }
        //else, it is a client
        else
        {
			sf::Packet packet;
			if (tcpsocket.receive(packet) == sf::Socket::Done)
			{
				PacketInfo info;
				packet >> info;
				if (info == PacketInfo::Lobby_info)
				{
					_Menu_DecodeLobbyInfo(packet);
				}
			}
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
    
	for (std::unique_ptr<sf::TcpSocket> &socket : tcpsocketlist)
	{
		socket->disconnect();
	}
	tcpsocketlist.clear();
    
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
		//sf::Packet packet;
		//tcpsocket.receive(packet);
		//_Menu_DecodeLobbyInfo(packet);

        bool_isAvailable = true;
		return true;
	}
	else
	{
		std::cout << "cannot connect to the server." << std::endl;
		return false;
	}
}

void NetworkManager::_Menu_SendLobbyInfo(std::unique_ptr<sf::TcpSocket>& socket, const int& playerindex)
{
	sf::Packet packet;
    int playercount = ptrData->getPlayerNumber();  //get the player number
	packet << PacketInfo::Lobby_info << playercount << playerindex;
	socket->send(packet);
}

void NetworkManager::_Menu_DecodeLobbyInfo(sf::Packet& packet)
{
	int playercount;
	packet >> playercount;
	std::cout << "Update : There are " << playercount << "Players." << std::endl;
	int playerindex;
	packet >> playerindex;
	std::cout << "Your index is " << playerindex << std::endl;
	ptrData->setPlayerindex(playerindex);
	//rebuild the player list
	ptrData->RebuildPlayer(playercount);
}

void NetworkManager::Menu_disconnect()
{
	sf::Packet packet;
	int playerindex = ptrData->getPlayerindex();
	packet << PacketInfo::Disconnect_request << playerindex;
	tcpsocket.send(packet);
	tcpsocket.disconnect();
}

void NetworkManager::server_Checksocket(sf::TcpSocket& socket)
{

}

void NetworkManager::Menu_startGame()
{
    //call game creation
    //...
    
    //change the state to game
    //...
}

void NetworkManager::Menu_clientReady()
{
    //send OK packet to server
}

