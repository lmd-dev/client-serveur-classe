#pragma once
#include "isocket.h";

/**
 * Socket Factory
 */
class SocketFactory
{
public:
	/**
	 * Returns a socket function of the OS
	 */
	static ISocket* createSocket();
};

