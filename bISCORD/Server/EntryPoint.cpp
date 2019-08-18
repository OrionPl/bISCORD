#include <iostream>
#include <string>
#include "Networking.h"
#include "Utilities/Helper.h"

int main()
{
	Networking* networking = new Networking(8008);

	Helper help;
	std::string userInput;

	do
	{
		std::cin >> userInput;

		if (help.StringStartsWith(userInput, "/"))
		{

		}
		else
		{
			//server->SendMsgToAll(userInput);
		}

	} while (userInput.length() > 0);

	std::cout << "Press ENTER to exit";
	//system("pause");

	return 0;
}