#include "NetworkManager.h"
#include <iostream>	//debug
NetworkManager::NetworkManager()
{
	//set blocking to false
	listener.setBlocking(false);
	tcpsocket.setBlocking(false);
	listener.listen(8310);
	
	bool_isListening = false;
}

void NetworkManager::EventHandle()
{
	if (listener.accept(tcpsocket) != sf::Socket::Done)
	{
		
	}
	else
	{
		std::cout << "New connection from" << tcpsocket.getRemoteAddress() << std::endl;
	}
}

void NetworkManager::Menu_startListening()
{
	bool_isListening = true;
}

void NetworkManager::Menu_tryConnect(const sf::String &ip)
{
	sf::TcpSocket socket;
	sf::IpAddress ipAdress(ip);
	
	if (socket.connect(ipAdress, 8310, sf::seconds(5)) == sf::Socket::Done)
	{
		std::cout << "LOL" << std::endl;
	}
	else
	{
		std::cout << "timed out" << std::endl;
	}
	socket.disconnect();
}