#pragma once
#include <unordered_map>
#include <ostream>


namespace idk
{
	struct response
	{
		uint32_t status;
		std::unordered_map<std::string, std::string> headers;
		std::string payload;

		response();
		friend std::ostream& operator<<(std::ostream& os, const response& res);
	};
}