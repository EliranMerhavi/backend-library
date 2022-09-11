#include "init.h"
#include <iostream>
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
			res.status(idk::status_code::NOT_FOUND)
				.send("cannot " + idk::to_string(req.method) + ' ' + req.path + "!");
			
		}
	);

	server.set_route({ idk::http_method::GET, "/" },
		[](const idk::request& req, idk::response& res) {
			res.send_file("res/index.html");
		}
	);

	server.set_route({ idk::http_method::GET, "/hello" },
		[](const idk::request& req, idk::response& res) {
			json obj;

			if (req.query.find("test") != req.query.end())
			{
				obj["test"] = req.query.at("test");
			}
			else
			{
				obj["error"] = "'test' query is required";
			}

			res.send(obj.dump(1));
		}
	);

	server.set_route({ idk::http_method::GET, "/test" },
		[](const idk::request& req, idk::response& res) {
			res.send("<h1>test</h1>");
		}
	);

	server.Listen(3000, 
		[]() {
			std::cout << "ready! press enter to quit\n";
		}
	);

	std::cin.get();
}