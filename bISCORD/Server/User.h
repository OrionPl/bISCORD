#pragma once

#ifndef USER_H_
#define USER_H_

class Server;

#include <iostream>
#include <string>
#include <WS2tcpip.h>

#include "Utilities/Helper.h"
#include "Server.h"

class User
{
public:
	User(SOCKET* Socket, std::string Name, Server* _server);
	std::string GetName() const { return name; };
	std::string GetIP() const { return ip; };
	SOCKET* GetSocket() const { return socket; };
	void Send(std::string text);

private:
	std::string name;
	std::string ip;
	SOCKET* socket;
	Server* server;

	void Receive();
	void HandleQuery(std::string* query);
	void SetUserInfo(std::string msg);

	bool userInfoDone = false;
};
#endif