#pragma once

#ifndef SERVER_H_
#define SERVER_H_

class User;

#include <WS2tcpip.h>
#include <vector>
#include <string>

#include "User.h"

class Server
{
public:
	Server(SOCKET* serverSock);
	void OnConnect(SOCKET* clientSock, sockaddr_in* client);
	void OnDisconnect(User* user);
	void AddUser(User* user);

	std::vector<User*>* GetUsers() { return &users; };

private:
	SOCKET* serverSocket;
	std::vector<User*> users;

	void SendToAllUsers(std::string message);
};
#endif