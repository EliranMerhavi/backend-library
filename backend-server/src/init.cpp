#include "pch.h"
#include "init.h"

namespace idk
{
	bool init()
	{
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

		return iResult == 0;
	}
}