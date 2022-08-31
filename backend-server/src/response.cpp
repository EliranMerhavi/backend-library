#include "response.h"
#include <iostream>

namespace idk
{
	response::response() : status(200), headers(), payload("null")
	{
	}

	std::ostream& operator<<(std::ostream& os, const idk::response& res)
	{
		os << "HTTP/1.1 ";

		os << res.status;

		if (res.status == 200)
		{
			os << " OK";
		}
		else if (res.status == 404)
		{
			os << " Not Found";
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