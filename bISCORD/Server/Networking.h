#pragma once

#include <iostream>
#include <future>
#include <WS2tcpip.h>

#include "Server.h"

#pragma comment (lib, "ws2_32.lib")

class Networking
{
public:
	Networking(int port);
	void SendMsgToAll(std::string message);

private:
	SOCKET listenSock;
	Server* server;

	void InitializeWinsock();
	void CreateServerSocket();
	void BindSocketToPort(int port);
	void StartListening();
	void AcceptIncomingConnections();
};

