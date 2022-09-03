#include "response.h"
#include <iostream>

namespace idk
{
	response::response() : status(200), headers(), payload()
	{
	}

	std::ostream& operator<<(std::ostream& os, const idk::response& res)
	{
		os << "HTTP/1.1 ";

		os << res.status;

		switch (res.status)
		{
		case 200:
			os << " OK";
			break;
		case 400:
			os << " Bad Request";
			break;
		case 404:
			os << " Not Found";
			break;
		default:
			os << " OK";
			break;
		}

		os << "\r\n";

		for (const auto& [name, content] : res.headers)
		{
			os << name << ": " << content << "\r\n";
		}

		os << "\r\n";
		os << res.payload;
		os << "\r\n\r\n";

		return os;
	}
}