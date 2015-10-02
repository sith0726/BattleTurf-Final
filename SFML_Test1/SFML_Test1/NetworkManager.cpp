#include "NetworkManager.h"
#include <iostream>	//debug
NetworkManager::NetworkManager()
{
	//set blocking to false
	listener.setBlocking(false);
	tcpsocket.setBlocking(false);
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
                //send the lobby data to user
                //...
                
            }
        }
        //else, it is a client
        else
        {
            //if the socket receive something...
            switch (tcpsocket.receive(packet))
            {
                //in case of success, call decoder.
                case sf::Socket::Done : //decode...
                                        break;
                //in case of broken data, request the server to send again.
                case sf::Socket::Partial : //send again...
                                        break;
                //if the server shut down or something...
                case sf::Socket::Disconnected : //disconnected...
                                        break;
                //in case of error,
                case sf::Socket::Error : //error...
                                        break;
                //in case of notready, do nothing
                case sf::Socket::NotReady : ;
            }
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
	
	if (tcpsocket.connect(ipAdress, 8310) == sf::Socket::Done)
	{
		std::cout << "connect success." << std::endl;
        //start listening...only accept the server ip
        bool_isListening = true;
	}
	else
	{
		std::cout << "cannot connect to the server." << std::endl;
	}
}