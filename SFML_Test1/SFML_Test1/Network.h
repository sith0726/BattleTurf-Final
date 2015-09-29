#include <SFML/Network.hpp>
#include <list>

class NetworkManager
{
private:
	sf::TcpListener listener;
	std::list<sf::TcpSocket> socketList;
public:
	NetworkManager();

	//call at each frame
	void EventHandle();
	
	void startListening();
	void tryConnect();

};