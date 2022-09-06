#include "request.h"


std::istream& operator>>(std::istream& is, idk::request& req)
{
	std::string line;
	size_t sep;

	is >> req.method;
	is >> req.path;

	if ((sep = req.path.find('?')) != req.path.npos)
	{
		line = req.path.substr(sep + 1);
		std::regex regex("(\\w+)=?(\\w+)?&?");
		std::smatch res;

		while (std::regex_search(line, res, regex))
		{
			req.query[res[1]] = (res.size() == 3) ? res[2] : std::string();
			line = res.suffix();
		}

		req.path = req.path.substr(0, sep);
	}

	
	is.ignore(11); // ignores " HTTP/1.1\r\n"

	std::getline(is, line);

	while (line != "\r")
	{
		sep = line.find_first_of(':');
		req.headers[line.substr(0, sep)] = line.substr(sep + 2);

		std::getline(is, line);
	}

	while (std::getline(is, line))
	{
		req.payload += line;
	}

	// std::cout << "payload:\n" << req.payload << '\n';

	return is;
}

