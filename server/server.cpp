#include "server.h"
#include "socket-factory.h"
#include <iostream>
#include <exception>
#include <thread>

/**
 * Constructor
 * @param listeningPort Listening port of the server
 */
Server::Server(const int& listeningPort)
{
	port = listeningPort;
	socketServer = NULL;
}

/**
 * Destructor
 */
Server::~Server()
{
	if (socketServer)
		delete socketServer;
}

/**
 * Starts listening on the given port
 */
void Server::start()
{
	try {
		socketServer = SocketFactory::createSocket();

		socketServer->listenOn(port);

		std::cout << "Server started. Waiting for connections..." << std::endl;

		std::thread connectionThread(&Server::waitForConnections, socketServer);
		connectionThread.join();
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

/**
 * Thread Function - Waits for new connections to accept
 */
void Server::waitForConnections(ISocket* socketServer)
{
	while (true)
	{
		try
		{
			ISocket* socketClient = socketServer->acceptConnection();
			new std::thread(&Server::processConnection, socketServer, socketClient);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

/**
 * Thread function - Process a client request
 */
void Server::processConnection(ISocket* socketServer, ISocket* socketClient)
{
	try {
		std::cout << "Incoming connection - Process request..." << std::endl;

		char buffer[4096] = "";
		socketServer->receiveData(socketClient, buffer, 4096);;
		std::cout << buffer << std::endl;

		std::string response = "HTTP/1.0 200 OK\r\n";
		response += "Content-Type: text/html\r\n";
		response += "Content-Length: 48\r\n";
		response += "\r\n";
		response += "<html><head></head><body>Page Web !</body></html>";

		socketServer->sendData(socketClient, response.c_str(), response.length());

	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	socketClient->close();
	std::cout << "Connection closed.";

}