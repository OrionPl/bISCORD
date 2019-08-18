#include <iostream> 
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

int main()
{
	std::string serverIp = "127.0.0.1";
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

	SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);
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
		return 0;
	}

	char buffer[4096];
	std::string userInput;

	std::string userInfo = "userInfo OriginalOrion";
	send(clientSock, userInfo.c_str(), userInfo.size() + 1, 0);

	do 
	{
		std::cout << "> ";
		getline(std::cin, userInput);

		if (userInput.size() > 0)
		{
			int sendResult = send(clientSock, userInput.c_str(), userInput.size() + 1, 0);

			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buffer, 4096);
				
				int bytesReceived = recv(clientSock, buffer, 4096, 0);

				if (bytesReceived > 0)
				{
					std::cout << "SERVER> " << std::string(buffer, 0, bytesReceived) << std::endl;
				}
				else
				{
					std::cerr << "SHIT! Server disconnected!" << std::endl;
				}
			}
		}
	} while (userInput.size() > 0);

	closesocket(clientSock);
	WSACleanup();
}