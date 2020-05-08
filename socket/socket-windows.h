#pragma once
#include "isocket.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

/**
 * Windows Socket
 */
class SocketWindows: public ISocket
{
private:
	/**
	 * Contains the number of SocketWindows created instances
	 */
	static int instances;

	/**
	 * Initializes the WinSock2 library before using Windows sockets
	 */
	void initialize();

	/**
	 * uninitializes the WinSock2 library when no more instances use Windows sockets
	 */
	void uninitialize();

public:
	/**
	 * Opened Windows socket
	 */
	SOCKET _socket;

public:
	/**
	 * Constructor
	 */
	SocketWindows();

	/**
	 * Constructor with always opened socket 
	 */
	SocketWindows(const SOCKET& sock);

	/**
	 * Desctructor
	 */
	~SocketWindows();
		
	/**
	 * Starts listening on given port
	 */
	void listenOn(const int& port);

	/**
	 * Accepts new client connection
	 */
	ISocket* acceptConnection();

	/**
	 * Connects to the server with given address and port
	 */
	void connectTo(const std::string& address, const int& port);

	/**
	 * Sends data
	 * @param to Pointer to the socket to use to send data
	 * @buffer Bytes array containing data to send
	 * @bufferLength size of the data to send
	 */
	void sendData(ISocket* to, const char* buffer, const int& bufferLength);

	/**
	 * Receives data
	 * @param from Pointer to the socket to use to get data
	 */
	int receiveData(ISocket* from, char* buffer, const int& bufferLength);

	/**
	 * Closes the socket
	 */
	void close();
};

