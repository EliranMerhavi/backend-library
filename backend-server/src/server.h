#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#pragma comment(lib, "Ws2_32.lib")

#include "request.h"
#include "response.h"
#include "route.h"

/* 
* HTTP/1.1 200 OK
* X-Powered-By: Express
* Content-Type: text/html; charset=utf-8
* Content-Length: 12
* ETag: W/"c-QwzjTQIHJO11oZbfwq1nx3dy0Wk"
* Date: Mon, 29 Aug 2022 13:36:39 GMT
* Connection: keep-alive
* Keep-Alive: timeout=5
*/

/*
* HTTP/1.1 200 OK
* X-Powered-By: Express
* Access-Control-Allow-Origin: *
* Access-Control-Allow-Methods: *
* Access-Control-Allow-Headers: *
* Content-Type: text/html; charset=utf-8
* Accept-Ranges: bytes
* Content-Length: 1711
* ETag: W/"6af-+M4OSPFNZpwKBdFEydrj+1+V5xo"
* Vary: Accept-Encoding
* Date: Mon, 29 Aug 2022 13:14:40 GMT
* Connection: keep-alive
* Keep-Alive: timeout=5 
*/


typedef void (*callback_func) (const idk::request&, idk::response&);

namespace idk
{
	class server
	{
	public:
		server();
		~server();

		void Listen(int port, void (*callback)() = []() {});
		void Close();

		void set_route(const route& r, const callback_func& func);
		void set_default(const callback_func& func);
	private:
		std::unordered_map<route, callback_func> m_routes;
		callback_func m_default_func;

		std::unordered_set<SOCKET> m_clients;
		bool m_listening = false;

		SOCKET Accept();
		void Handle(SOCKET client);

	private:
		WSADATA m_wsaData;
		struct addrinfo* m_result = NULL, * m_ptr = NULL, m_hints;
		SOCKET listen_socket;

		static std::string recive_data(const SOCKET& client, int bufflen);
		static bool send_data(const SOCKET& client, const std::string& data);
	};
}