#include "socket-factory.h"
#include "socket-windows.h"

/**
 * Returns a socket function of the OS
 */
ISocket* SocketFactory::createSocket()
{
#ifdef _WIN32
	return new SocketWindows();
#endif
}