#include "http_method.h"


std::istream& operator>>(std::istream& is, idk::http_method& method)
{
	std::string data;
	is >> data;

	if (data == "OPTIONS")
	{
		method = idk::http_method::OPTIONS;
	}
	else if (data == "GET")
	{
		method = idk::http_method::GET;
	}
	else if (data == "HEAD")
	{
		method = idk::http_method::HEAD;
	}
	else if (data == "PUT")
	{
		method = idk::http_method::PUT;
	}
	else if (data == "POST")
	{
		method = idk::http_method::POST;
	}
	else if (data == "DELETE")
	{
		method = idk::http_method::_DELETE;
	}
	else if (data == "PATCH")
	{
		method = idk::http_method::PATCH;
	}
	else
	{
		method = idk::http_method::UNKNOWN;
	}

	return is;
}
