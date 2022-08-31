#include "request.h"

namespace idk
{
	request::request(const std::string& raw)
	{
		std::stringstream ss;
		std::string line;

		ss << raw;
		ss >> this->method;
		ss >> this->path;

		//TODO: parse the path for params
		ss.ignore(11);

		std::getline(ss, line);

		while (line != "\r")
		{
			size_t sep = line.find(':');
			this->headers[line.substr(0, sep)] = line.substr(sep + 2);

			std::getline(ss, line);
		}

		while (std::getline(ss, line))
		{
			this->payload += line;
		}

		std::cout << "payload:\n" << payload << '\n';
	}
}