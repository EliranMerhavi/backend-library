#pragma once

#include <string>
#include <iostream>

namespace idk
{
	enum class http_method
	{
		OPTIONS, GET, HEAD, PUT, POST, _DELETE, PATCH
	};

	inline std::string to_string(const http_method& method)
	{
		std::string data;
		switch (method)
		{
		case http_method::OPTIONS:
			data = "OPTIONS";
			break;
		case http_method::GET:
			data = "GET";
			break;
		case http_method::HEAD:
			data = "HEAD";
			break;
		case http_method::PUT:
			data = "PUT";
			break;
		case http_method::POST:
			data = "POST";
			break;
		case http_method::_DELETE:
			data = "_DELETE";
			break;
		case http_method::PATCH:
			data = "PATCH";
			break;
		}

		return data;
	}
}

std::istream& operator>>(std::istream& is, idk::http_method& method);