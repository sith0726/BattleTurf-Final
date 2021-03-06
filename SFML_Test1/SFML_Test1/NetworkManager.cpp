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
	if (isServer())
	{
		Servershutdown();
	}
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
                            
                    case PacketInfo::Game_start :
                            break;

					case PacketInfo::Game_update:
					{
						//send the same packet to all players
						sf::Vector2i mouseposition;
						newPacket >> mouseposition.x >> mouseposition.y;
						Game_sendUpdate(mouseposition);
						//put the data back to packet...?
						newPacket << mouseposition.x << mouseposition.y;
						ptrData->decodeUpdate_Packet(newPacket);
						break;
					}
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
                    //decode the packet
					_Menu_DecodeLobbyInfo(packet);
				}
                else if(info == PacketInfo::Game_start)
                {
                    //decode the packet
                    _Menu_DecodeGameInfo(packet);
                    ptrData->setGameState(Game_State::game);
                }
				else if (info == PacketInfo::Game_update)
				{
					//decode the packet
					ptrData->decodeUpdate_Packet(packet);
				}
				else if (info == PacketInfo::ShutDown_warning)
				{
					//show server shut down message
					std::cout << "disconnected from server." << std::endl;
					tcpsocket.disconnect();
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
    ptrData->NewGame();
    
    //send game data
    sf::Packet packet;
    packet << PacketInfo::Game_start;
    
    packet << ptrData->getGameMap();

    //send the score list of all players
    ptrData->fillScore_Packet(packet);
    
	//send signal to all player
	for (std::unique_ptr<sf::TcpSocket> &socket : tcpsocketlist)
	{
		socket->send(packet);
	}
}

void NetworkManager::Menu_clientReady()
{
    //send OK packet to server
}

void NetworkManager::_Menu_DecodeGameInfo(sf::Packet &packet)
{
    //get the gameMap reference
    packet >> ptrData->getGameMap();
    
    //get the scorelist for all players
    ptrData->decodeScore_Packet(packet);
}


void NetworkManager::Game_sendUpdate(sf::Vector2i mouseposition)
{
	sf::Packet packet;
	packet << PacketInfo::Game_update;

	packet << mouseposition.x << mouseposition.y;
	
	if (isServer())
	{
		for (std::unique_ptr<sf::TcpSocket> &socket : tcpsocketlist)
		{
			socket->send(packet);
		}
	}
	else
	{
		tcpsocket.send(packet);
	}
}

void NetworkManager::Servershutdown()
{
	sf::Packet packet;
	packet << PacketInfo::ShutDown_warning;
	
	for (std::unique_ptr<sf::TcpSocket> &socket : tcpsocketlist)
	{
		socket->send(packet);
	}
	
}