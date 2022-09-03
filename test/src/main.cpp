#include "init.h"
#include <Windows.h>
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
			res.payload = "cannot " + idk::to_string(req.method) + ' ' + req.path + "!";
		}
	);

	server.set_route({ idk::http_method::GET, "/" },
		[](const idk::request& req, idk::response& res) {
			res.payload = "home page";
		}
	);

	server.set_route({ idk::http_method::GET, "/hello" },
		[](const idk::request& req, idk::response& res) {
			json obj = {};

			if (req.query.find("test") != req.query.end())
			{
				obj["test"] = req.query.at("test");
			}
			else
			{
				obj["error"] = "'test' query is required";
			}

			res.payload = obj.dump(1);
			res.headers["Content-length"] = std::to_string(res.payload.size());
		}
	);

	server.set_route({ idk::http_method::GET, "/test" },
		[](const idk::request& req, idk::response& res) {
			res.payload = "<h1>test</h1>";
		}
	);

	server.Listen(3000, 
		[]() {
			std::cout << "ready! pres enter to quit\n";
		}
	);

	std::cin.get();
}