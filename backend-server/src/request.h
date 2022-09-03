#pragma once

#include <string>
#include <unordered_map>
#include <sstream>
#include <regex>

#include "http_method.h"
#include "route.h"
namespace idk
{
	struct request
	{
		idk::http_method method;
		std::string path;
		std::unordered_map<std::string, std::string> query;
		std::unordered_map<std::string, std::string> headers;
		std::string payload;
	};
}
std::istream& operator>>(std::istream& is, idk::request& req);
