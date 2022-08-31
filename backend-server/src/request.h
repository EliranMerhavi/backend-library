#pragma once

#include <string>
#include <unordered_map>
#include <sstream>

#include "http_method.h"

namespace idk
{
	struct request
	{
		idk::http_method method;
		std::unordered_map<std::string, std::string> params;
		std::string path;
		std::unordered_map<std::string, std::string> headers;
		std::string payload;

		request(const std::string& raw);
	};
}
