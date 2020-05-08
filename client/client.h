#pragma once
#include "socket-windows.h"

/**
 * Test client
  */
class Client
{
private:
	/**
	 * Socket of the client
	 */
	ISocket* socketClient;

public:
	/**
	 * Constructor
	 */
	Client();

	/**
	 * Connects the client to the given server
	 * @param ip IP address of the server
	 * @param port Port of the server
	 */
	void connect(const std::string& ip, const int& port);
};

