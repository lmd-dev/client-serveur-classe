#include "client.h"
#include "socket-factory.h"
#include <iostream>

/**
 * Constructor
 */
Client::Client()
{
	socketClient = NULL;
}

/**
 * Connects the client to the given server
 * @param ip IP address of the server
 * @param port Port of the server
 */
void Client::connect(const std::string& ip, const int& port)
{
	try
	{
		std::cout << "Connection to " << ip << ":" << port << "in progress...";

		socketClient = SocketFactory::createSocket();

		socketClient->connectTo(ip, port);

		std::cout << " Connected." << std::endl;

		std::cout << "Sending data...";

		socketClient->sendData(socketClient, "Hello !", 7);

		std::cout << " Sended." << std::endl;

		char buffer[500];
		int taille = 500;
		memset(buffer, 0, taille);

		std::cout << "Receive data from server...";
		socketClient->receiveData(socketClient, buffer, taille);
		
		std::cout << std::endl << buffer << std::endl;

		socketClient->close();

		std::cout << "End of the connection." << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}