#pragma once
#include <string>

/**
 * Socket Interface
 */
class ISocket
{
	public:
	//Server socket features -----------------------------------------------------

	/**
	 * Starts listening on given port
	 */
	virtual void listenOn(const int& port) = 0;

	/**
	 * Accepts new client connection 
	 */
	virtual ISocket* acceptConnection() = 0;

	//Client socket features -----------------------------------------------------

	/**
	 * Connects to the server with given address and port
	 */
	virtual void connectTo(const std::string& address, const int& port) = 0;

	//Common features ------------------------------------------------------------

	/**
	 * Sends data
	 * @param to Pointer to the socket to use to send data
	 * @buffer Bytes array containing data to send
	 * @bufferLength size of the data to send
	 */
	virtual void sendData(ISocket* to, const char* buffer, const int& bufferLength) = 0;

	/**
	 * Receives data
	 * @param from Pointer to the socket to use to get data
	 */
	virtual int receiveData(ISocket* from, char* buffer, const int& bufferLength) = 0;

	/**
	 * Closes the socket
	 */
	virtual void close() = 0;
};