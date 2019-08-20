#include <iostream> 
#include <thread>
#include <WS2tcpip.h>
#include <string>

#include "Utilities/Helper.h"

#pragma comment (lib, "ws2_32.lib")

SOCKET clientSock;
std::string nick;

void Receive()
{
	Helper help;

	char buffer[4096];

	while (true)
	{
		ZeroMemory(buffer, 4096);

		int bytesReceived = recv(clientSock, buffer, 4096, 0);
		std::string received = std::string(buffer, 0, bytesReceived);

		if (bytesReceived > 0)
		{
			if (help.StringStartsWith(received, "msgfrom"))
			{
				received = help.ShortenStringFromLeft(received, 8);
				std::string name = help.GetStringUntil(received, "###");
				std::string msg = help.ShortenStringFromLeft(received, name.length() + 3);

				//if (name != nick)
					std::cout << name << "> " << msg << std::endl;
			}
			else
			{
				std::cout << "SERVER> " << received << std::endl;
			}
		}
		else
		{
			std::cerr << "SHIT! Server disconnected!" << std::endl;
		}
	}
}

void Send()
{
	std::string userInput;

	do
	{
		std::cout << "> ";
		std::cin >> userInput;

		if (userInput.size() > 0)
		{
			userInput = "msg " + userInput;

			int sendResult = send(clientSock, userInput.c_str(), userInput.size() + 1, 0);

			if (sendResult == SOCKET_ERROR)
			{
				std::cout << "SHIT! Something went wrong when sending shit" << std::endl;
			}
		}
	} while (userInput.size() > 0);
}

void InitializeClient()
{
	std::string serverIp = "127.0.0.1"; //external 89.78.12.9
	int port = 8008;

	//WEENSOCK
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsResult = WSAStartup(version, &data);

	if (wsResult != 0)
	{
		std::cerr << "SHIT! Winstock error with number " << wsResult << std::endl;
	}

	//SOCKET CREATION

	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock == INVALID_SOCKET)
	{
		std::cerr << "SHIT! Invalid socket" << std::endl;
	}

	//HINT SHIT
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, serverIp.c_str(), &hint.sin_addr);

	//CONNECT

	std::cout << "Attempting connection..." << std::endl;

	int connResult = connect(clientSock, (sockaddr*)& hint, sizeof(hint));

	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "SHIT! Can't connect to server" << std::endl;
		closesocket(clientSock);
		WSACleanup();
	}

	std::cout << "Connected to server" << std::endl << std::endl;

	std::cout << "Write your nickname" << std::endl;

	std::cin >> nick;

	std::string userInfo = "userInfo " + nick;
	send(clientSock, userInfo.c_str(), userInfo.size() + 1, 0);

	std::cout << "Set nickname to " << nick << std::endl << std::endl;
}

int main()
{
	InitializeClient();
	std::thread receiveThread (Receive);
	receiveThread.detach();
	Send();

	closesocket(clientSock);
	WSACleanup();
}