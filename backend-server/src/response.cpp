#include "response.h"
#include <iostream>

namespace idk
{
	response::response() : status(idk::status_code::OK), headers(), payload()
	{
	}

	std::ostream& operator<<(std::ostream& os, const idk::response& res)
	{
		os << "HTTP/1.1 ";

		os << (uint32_t) res.status;

		os << ' ' + idk::to_string(res.status);

		os << "\r\n";

		for (const auto& [name, content] : res.headers)
		{
			os << name << ": " << content << "\r\n";
		}

		os << "\r\n";
		os << res.payload;
		os << "\r\n";

		return os;
	}
}