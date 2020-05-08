#pragma once
#include "socket-windows.h"

/**
 * Test server
  */
class Server
{
private:
	/**
	 * Socket of the server
	 */
	ISocket* socketServer;

	/**
	 * Listening port of the server
	 */
	int port;

	/**
	 * Thread Function - Waits for new connections to accept
	 */
	static void waitForConnections(ISocket* socketServer);

	/**
	 * Thread function - Process a client request
	 */
	static void processConnection(ISocket* socketServer, ISocket* socketClient);

public:
	/**
	 * Constructor
	 * @param listeningPort Listening port of the server
	 */
	Server(const int& listeningPort);

	/**
	 * Destructor
	 */
	~Server();

	/**
	 * Starts listening on the given port
	 */
	void start();
};

