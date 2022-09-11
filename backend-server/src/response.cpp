#include "pch.h"
#include "response.h"



namespace idk
{
	response::response() : m_status(idk::status_code::OK),
		m_headers(), m_payload(), m_ready(false)
	{
	}

	response& response::status(uint32_t status)
	{
		m_status = status;
		return *this;
	}

	response& response::set_headers(const std::unordered_map<std::string, std::string>& headers)
	{
		m_headers = headers;
		return *this;
	}

	std::string response::get_header(const std::string& name)
	{
		return m_headers.at(name);
	}

	void response::send(const char* payload)
	{
		if (m_ready) throw std::exception("response is ready you cant edit it anymore");
		
		m_payload = payload;
		m_headers["Content-Type"] = "text/html; charset=utf-8";
		m_headers["Content-length"] = std::to_string(m_payload.size());
		m_headers["Connection"] = "keep-alive";
		m_ready = true;
	}

	void response::send(const json& payload)
	{
		if (m_ready) throw std::exception("response is ready you cant edit it anymore");

		m_payload = payload.dump();
		m_headers["Content-Type"] = "application/json";
		m_headers["Content-length"] = std::to_string(m_payload.size());
		m_headers["Connection"] = "keep-alive";
		m_ready = true;
	}


	void response::send_file(const std::string& filepath)
	{
		FILE* fp = nullptr;
		size_t size;
		fopen_s(&fp, filepath.c_str(), "r");
	
		if (!fp)
		{
			throw std::exception(("failed loading file: " + filepath).c_str());
		}

		fseek(fp, 0L, SEEK_END);
		size = ftell(fp);
		rewind(fp);
		char* buffer = new char[size] { 0 };
		fread(buffer, sizeof(char), size, fp);
		
		this->send(buffer);

		delete[] buffer;
		fclose(fp);
	}

	void response::close_connection()
	{
		m_headers["Connection"] = "close";
		m_ready = true;
	}

	std::ostream& operator<<(std::ostream& os, const idk::response& res)
	{
		os << "HTTP/1.1 ";

		os << (uint32_t) res.m_status;

		os << ' ' + to_string(res.m_status);

		os << "\r\n";

		for (const auto& [name, content] : res.m_headers)
		{
			os << name << ": " << content << "\r\n";
		}

		os << "\r\n";
		
		if (res.m_payload.size())
		{
			os << res.m_payload;
			os << "\r\n";
		}
		
		return os;
	}
}