#include "Helper.h"

bool Helper::StringStartsWith(std::string str, std::string startsWith)
{
	if (str.length() < startsWith.length())
	{
		return false;
	}

	for (int i = 0; i < startsWith.length(); i++)
	{
		if (str[i] != startsWith[i])
		{
			return false;
		}
	}

	return true;
}
