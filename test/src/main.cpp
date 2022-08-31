#include "init.h"

#include "json/json.hpp"

using json = nlohmann::json;

int main()
{
	if (!idk::init())
	{
		system("pause");
		return -1;
	}

	idk::server server;

	server.set_default(
		[](const idk::request& req, idk::response& res) {
			res.payload = "cannot " + to_string(req.method) + ' ' + req.path + "!";
		}
	);

	server.set_route({ idk::http_method::GET, "/" },
		[](const idk::request& req, idk::response& res) {
			res.payload = "home page";
		}
	);

	server.set_route({ idk::http_method::GET, "/hello" },
		[](const idk::request& req, idk::response& res) {
			res.payload = "<h1>hello world</h1>";
		}
	);

	server.set_route({ idk::http_method::GET, "/test" },
		[](const idk::request& req, idk::response& res) {
			res.payload = "<h1>test</h1>";
		}
	);

	server.Listen(3000, 
		[]() {
			std::cout << "ready! pres any to quit\n";
		}
	);

	std::cin.get();
}