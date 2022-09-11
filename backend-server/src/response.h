#pragma once
#include <unordered_map>
#include <ostream>
#include <fstream>

#include "status_code.h"
#include "json/json.hpp"

using json = nlohmann::json;

namespace idk
{
	class response
	{
	public:
		response();

		response& status(uint32_t status);
		response& set_headers(const std::unordered_map<std::string, std::string>& headers);
		std::string get_header(const std::string& name);
		
		inline bool has_header(const std::string& name) const
		{
			return m_headers.find(name) != m_headers.end();
		}

		void send(const char* data);
		void send(const json& payload);
		void send_file(const std::string& filepath);
		void close_connection();

		friend std::ostream& operator<<(std::ostream& os, const response& res);
	private: // HTTP fields
		uint32_t m_status;
		std::unordered_map<std::string, std::string> m_headers;
		std::string m_payload;
	private: // utils fields
		bool m_ready;
	};
}