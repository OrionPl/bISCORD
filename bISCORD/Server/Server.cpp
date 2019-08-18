#include "Server.h"

Server::Server(SOCKET* serverSock)
{
	serverSocket = serverSock;
}

void Server::OnConnect(SOCKET* clientSock, sockaddr_in* client)
{
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	if (getnameinfo((sockaddr*)& client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client->sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected to port " << ntohs(client->sin_port) << std::endl;
	}

	Server::AddUser(clientSock, host);
}

void Server::OnDisconnect(User* user)
{
	std::cout << user->GetName() << " disconnected" << std::endl;
	delete user;

	if (users.empty())
	{
		std::cout << "Noone is connected" << std::endl;
	}
	else
	{
		for (int i = 0; i < users.size(); i++)
		{
			std::cout << users[i]->GetName() << " is connected" << std::endl;
		}
	}
}

void Server::AddUser(SOCKET* socket, std::string name)
{
	users.push_back(new User(socket, name, this));
}


void Server::SendToAllUsers(std::string message)
{
	for (int i = 0; i < users.size(); i++)
	{
		users[i]->Send(message);
	}
}