#include "server.h"

namespace idk
{
	server::server()
	{
		ZeroMemory(&m_hints, sizeof(m_hints));
		m_hints.ai_family = AF_INET;
		m_hints.ai_socktype = SOCK_STREAM;
		m_hints.ai_protocol = IPPROTO_TCP;
		m_hints.ai_flags = AI_PASSIVE;
	}

	server::~server()
	{
		if (m_listening)
		{
			freeaddrinfo(m_result);
			closesocket(listen_socket);
		}
	}

	//TODO: handle when calling this function more than once
	void server::Listen(int port, void (*callback)())
	{
		if (m_listening)
		{
			throw std::exception("server already listening on other port!");
		}

		int result = getaddrinfo(NULL, std::to_string(port).c_str(), &m_hints, &m_result);

		if (result != 0)
		{
			throw std::exception(("getaddrinfo failed: " + std::to_string(result)).c_str());
		}

		listen_socket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);

		if (listen_socket == INVALID_SOCKET)
		{
			freeaddrinfo(m_result);
			throw std::exception(("Error at socket():" + std::to_string(WSAGetLastError())).c_str());
		}

		if (bind(listen_socket, m_result->ai_addr, (int)m_result->ai_addrlen) == SOCKET_ERROR)
		{
			freeaddrinfo(m_result);
			closesocket(listen_socket);
			throw std::exception(("bind failed with error:" + std::to_string(WSAGetLastError())).c_str());
		}

		if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
		{
			closesocket(listen_socket);
			WSACleanup();
			throw std::exception(("Listen failed with error: " + std::to_string(WSAGetLastError())).c_str());
		}


		m_listening = true;
		std::thread(
			[this, callback]() {
				callback();
				while (m_listening)
				{
					SOCKET client = Accept();
					if (m_clients.find(client) == m_clients.end())
					{
						m_clients.insert(client);
						std::thread(&server::Handle, this, client).detach();
					}
				}
			}
		).detach();

	}

	void server::Close()
	{
		m_listening = false;
	}

	void server::set_route(const route& route, const callback_func& func)
	{
		m_routes[route] = func;
	}

	void server::set_default(const callback_func& func)
	{
		m_default_func = func;
	}

	SOCKET server::Accept()
	{
		SOCKET client = accept(listen_socket, nullptr, nullptr);

		if (client == INVALID_SOCKET)
		{
			closesocket(listen_socket);
			throw std::exception(("accept failed:" + std::to_string(WSAGetLastError())).c_str());
		}

		return client;
	}

	void server::Handle(SOCKET client)
	{
		std::string raw;

		response res;

		raw = recive_data(client, 512);

		while (raw.find("\r\n\r\n") == raw.npos)
		{
			raw += recive_data(client, 1);
		}

		request req(raw);
		route route = { req.method, req.path };

		if (m_routes.find(route) != m_routes.end())
		{
			m_routes[route](req, res);
		}
		else if (m_default_func)
		{
			m_default_func(req, res);
		}
		else
		{
			res.status = 404;
			res.payload = "invalid route!";
		}

		std::stringstream ss;
		ss << res;

		if (!send_data(client, ss.str()))
		{
			throw std::exception(("error! when sending:\n" + ss.str()).c_str());
		}

		closesocket(client);
		m_clients.erase(client);
	}

	std::string server::recive_data(const SOCKET& client, int bufflen)
	{
		std::string data;
		char* buffer = (char*)alloca(bufflen * sizeof(char));
		int recv_len;

		recv_len = recv(client, buffer, bufflen, 0);

		if (recv_len == 1)
		{
			data += buffer[0];
		}
		else if (recv_len == bufflen)
		{
			data += buffer;
		}
		else if (recv_len > 0)
		{
			for (int i = 0; i < recv_len; i++)
			{
				data += buffer[i];
			}
		}
		else
		{
			throw std::exception("read 0 or negative bytes");
		}

		return data;
	}

	bool server::send_data(const SOCKET& client, const std::string& data)
	{
		int iSendResult = send(client, data.c_str(), data.size(), 0);

		return iSendResult != SOCKET_ERROR;
	}
}