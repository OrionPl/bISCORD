#include "User.h"
#include "Server.h"

User::User(SOCKET* Socket, std::string Name, Server* _server)
{
	socket = Socket;
	name = Name;
	server = _server;

	Receive();
}

void User::Receive()
{
	char buffer[4096];

	while (true)
	{
		ZeroMemory(buffer, 4096);

		int bytesReceived = recv(*socket, buffer, 4096, 0);

		if (bytesReceived > 0)
		{
			std::string received = std::string(buffer, 0, bytesReceived);
			HandleQuery(&received);
		}
		else
		{
			server->OnDisconnect(this);
			break;
		}
	}
}

void User::HandleQuery(std::string* query)
{
	Helper help;

	if (!userInfoDone)
	{
		SetUserInfo(*query);
	}
	else
	{
		std::cout << name << "> " << *query << std::endl;
		Send("Stop this shit");
	}
}

void User::SetUserInfo(std::string msg)
{
	Helper help;

	if (!help.StringStartsWith(msg, "userInfo"))
	{
		closesocket(*socket);
	}
	else if (help.StringStartsWith(msg, "userInfo"))
	{
		for (int i = 9; i < msg.length(); i++)
		{
			msg[i - 9] = msg[i];
			msg[i] = ' ';
		}

		msg.resize(msg.length() - 9);

		std::cout << name << " set nickname to " << msg << std::endl;
		name = msg;

		userInfoDone = true;
	}
}

void User::Send(std::string text)
{
	send(*socket, text.c_str(), text.size() + 1, 0);
}

