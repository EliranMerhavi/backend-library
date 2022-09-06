#pragma once

#include <string>
#include <iostream>

namespace idk
{
	enum class http_method
	{
		OPTIONS, GET, HEAD, PUT, POST, _DELETE, PATCH, UNKNOWN
	};

	inline std::string to_string(const http_method& method)
	{
		switch (method)
		{
		case http_method::OPTIONS: return "OPTIONS";
		case http_method::GET:     return "GET";
		case http_method::HEAD:    return "HEAD";
		case http_method::PUT:	   return "PUT";
		case http_method::POST:    return "POST";
		case http_method::_DELETE: return "DELETE";
		case http_method::PATCH:   return "PATCH";
		case http_method::UNKNOWN: return "UNKNOWN";
		}
	}
}

std::istream& operator>>(std::istream& is, idk::http_method& method);