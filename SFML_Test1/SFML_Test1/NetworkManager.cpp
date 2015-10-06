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
                std::cout << "New connection from" << tcpsocket.getRemoteAddress() << " " << std::endl;
                
				//insert the socket into the list
				tcpsocketlist.push_back(&tcpsocket);
				
				//add one player to the data
				Player newPlayer;
				ptrData->InsertPlayer(newPlayer);

                //send the lobby information
				int playerindex_forPacket = 1;
				for (sf::TcpSocket* socket : tcpsocketlist)
				{
					_Menu_SendLobbyInfo(socket, playerindex_forPacket);
					playerindex_forPacket++;
				}
				
            }

			int toberemoved;
			bool needremoved = false;
			//for each socket in the list, check the status
			for (sf::TcpSocket* socket : tcpsocketlist)
			{
				//server_Checksocket(*socket);
				/*
				The reason of server_Checksocket is disabled is that after the last element of tcpsocketlist is deleted, the iterator of
				this for loop points to a non-exist socket, causing the program crash.
				I make up a post-delete method to temporary solve this problem. Problem: if two people disconnect at the same 
				time, the program may delete one player only. I need a better solution.
				*/
				sf::Packet packet;
				if (socket->receive(packet) == sf::Socket::Done)
				{
					PacketInfo info;
					packet >> info;
					//if the player disconnect, remove it
					if (info == PacketInfo::Disconnect_request)
					{
						int playerindex;
						packet >> playerindex;
						ptrData->RemovePlayer(playerindex);
						toberemoved = playerindex - 1;
						needremoved = true;

						std::cout << "a player has disconnected." << std::endl;
						ptrData->RebuildPlayer(ptrData->getPlayerNumber());
					}
				}
			}
			if (needremoved)
			{
				//remove the socket in the tcpsocketlist
				tcpsocketlist[toberemoved]->disconnect();
				tcpsocketlist.erase(tcpsocketlist.begin() + toberemoved);
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

void NetworkManager::_Menu_SendLobbyInfo(sf::TcpSocket* socket, const int& playerindex)
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

