#include "socket-windows.h"
#include <WS2tcpip.h>
#include <sstream>

//Set the default value of the static attribut initialized
int SocketWindows::instances = 0;

/**
 * Constructor
 */
SocketWindows::SocketWindows()
{
	_socket = NULL;
	this->initialize();
	SocketWindows::instances++;
}

/**
 * Constructor with always opened socket
 */
SocketWindows::SocketWindows(const SOCKET& sock)
{
	SocketWindows();

	_socket = sock;
}

/**
 * Destructor
  */
SocketWindows::~SocketWindows()
{
	SocketWindows::instances--;
	this->uninitialize();
}

/**
 * Initializes the WinSock2 library before using Windows sockets
 */
void SocketWindows::initialize()
{
	if (SocketWindows::instances == 0)
	{
		WSADATA WSAData;
		WSAStartup(MAKEWORD(2, 0), &WSAData);
	}
}

/**
 * uninitializes the WinSock2 library when no more instances use Windows sockets
 */
void SocketWindows::uninitialize()
{
	if (SocketWindows::instances == 0)
		WSACleanup();
}

/**
 * Starts listening on given port
 */
void SocketWindows::listenOn(const int& port)
{
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(this->_socket, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketWindows::listenOn - An error occured when trying to bind socket - Error #" << WSAGetLastError();
		throw new std::exception(error.str().c_str());
	}

	if (listen(this->_socket, 5) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketWindows::listenOn - An error occured when trying to listen on port " << port << " - Error #" << WSAGetLastError();
		throw new std::exception(error.str().c_str());
	}
}

/**
 * Accepts new client connection
 */
ISocket* SocketWindows::acceptConnection()
{
	SOCKADDR_IN clientsin;
	int clientsinSize = sizeof(clientsin);
	SOCKET clientSocket = accept(this->_socket, (SOCKADDR*)&clientsin, &clientsinSize);

	if (clientSocket == INVALID_SOCKET)
	{
		std::stringstream error;
		error << "SocketWindows::accept - Invalid client socket - Error #" << WSAGetLastError();
		throw new std::exception(error.str().c_str());
	}

	return new SocketWindows(clientSocket);
}

/**
 * Connects to the server with given address and port
 */
void SocketWindows::connectTo(const std::string& address, const int& port)
{
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	inet_pton(AF_INET, address.c_str(), &sin.sin_addr.s_addr);

	this->_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(this->_socket, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketWindows::connectTo - Unable to connect to server " << address << ":" << port << " - Error #" << WSAGetLastError();
		throw new std::exception(error.str().c_str());
	}
}

/**
 * Sends data
 * @param to Pointer to the socket to use to send data
 * @buffer Bytes array containing data to send
 * @bufferLength size of the data to send
 */
void SocketWindows::sendData(ISocket* to, const char* buffer, const int& bufferLength)
{
	SocketWindows* temp = dynamic_cast<SocketWindows*>(to);

	if (send(temp->_socket, buffer, bufferLength, 0) == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketWindows::sendData - An error occured when trying to send data - Error #" << WSAGetLastError();
		throw new std::exception(error.str().c_str());
	}
}

/**
 * Receives data
 * @param from Pointer to the socket to use to get data
 */
int SocketWindows::receiveData(ISocket* from, char* buffer, const int& bufferLength)
{
	int readSize = 0;

	SocketWindows* temp = dynamic_cast<SocketWindows*>(from);

	int res = recv(temp->_socket, buffer, bufferLength, 0);

	if (res == SOCKET_ERROR)
	{
		std::stringstream error;
		error << "SocketWindows::receiveData - An error occured when trying to receive data - Error #" << WSAGetLastError();
		throw new std::exception(error.str().c_str());
	}

	return res;
}

/**
 * Closes the socket
 */
void SocketWindows::close()
{
	closesocket(_socket);
}