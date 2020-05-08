#include "client.h"
#include <iostream>

int main()
{
	std::cout << "Client application" << std::endl;

	Client client;
	client.connect("127.0.0.1", 5000);

	return 0;
}