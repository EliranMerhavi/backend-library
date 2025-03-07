#pragma once
#include <unordered_map>


#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include "request.h"
#include "response.h"
#include "route.h"


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

		bool m_listening = false;

		SOCKET Accept();
		void Handle(const SOCKET& client);

	private:
		WSADATA m_wsaData;
		struct addrinfo* m_result = NULL, * m_ptr = NULL, m_hints;
		SOCKET listen_socket;

		static std::string recive_data(const SOCKET& client, int bufflen);
		static bool send_data(const SOCKET& client, const std::string& data);
	};
}