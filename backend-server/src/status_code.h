#pragma once

#include <string>

namespace idk
{
	enum status_code
	{
		CONTINUE = 100,
		SWITCHING_PROTOCOLS = 101,
		OK = 200,
		CREATED = 201,
		ACCEPTED = 202,
		NON_AUTHORITATIVE_INFORMATION = 203,
		NO_CONTENT = 204,
		RESET_CONTENT = 205,
		PARTIAL_CONTENT = 206,
		MULTIPLE_CHOICES = 300,
		MOVED_PERMANENTLY = 301,
		FOUND = 302,
		SEE_OTHER = 303,
		NOT_MODIFIED = 304,
		USE_PROXY = 305,
		TEMPORARY_REDIRECT = 307,
		BAD_REQUEST = 400,
		UNAUTHORIZED = 401,
		PAYMENT_REQUIRED = 402,
		FORBIDDEN = 403,
		NOT_FOUND = 404,
		METHOD_NOT_ALLOWED = 405,
		NOT_ACCEPTABLE = 406,
		PROXY_AUTHENTICATION_REQUIRED = 407,
		REQUEST_TIMEOUT = 408,
		CONFLICT = 409,
		GONE = 410,
		LENGTH_REQUIRED = 411,
		PRECONDITION_FAILED = 412,
		PAYLOAD_TOO_LARGE = 413,
		URI_TOO_LONG = 414,
		UNSUPPORTED_MEDIA_TYPE = 415,
		RANGE_NOT_SATISFIABLE = 416,
		EXPECTATION_FAILED = 417,
		UPGRADE_REQUIRED = 426,
		INTERNAL_SERVER_ERROR = 500,
		NOT_IMPLEMENTED = 501,
		BAD_GATEWAY = 502,
		SERVICE_UNAVAILABLE = 503,
		GATEWAY_TIMEOUT = 504,
		HTTP_VERSION_NOT_SUPPORTED = 505,
	};
}

inline std::string to_string(uint32_t status)
{
	switch (status)
	{
	case idk::status_code::CONTINUE:						return "Continue";
	case idk::status_code::SWITCHING_PROTOCOLS:				return "Switching Protocols";
	case idk::status_code::OK:								return "OK";
	case idk::status_code::CREATED:							return "Created";
	case idk::status_code::ACCEPTED:						return "Accepted";
	case idk::status_code::NON_AUTHORITATIVE_INFORMATION:	return "Non-Authoritative Information";
	case idk::status_code::NO_CONTENT:						return "No Content";
	case idk::status_code::RESET_CONTENT:					return "Reset Content";
	case idk::status_code::PARTIAL_CONTENT:					return "Partial Content";
	case idk::status_code::MULTIPLE_CHOICES:				return "Multiple Choices";
	case idk::status_code::MOVED_PERMANENTLY:				return "Moved Permanently";
	case idk::status_code::FOUND:							return "Found";
	case idk::status_code::SEE_OTHER:						return "See Other";
	case idk::status_code::NOT_MODIFIED:					return "Not Modified";
	case idk::status_code::USE_PROXY:						return "Use Proxy";
	case idk::status_code::TEMPORARY_REDIRECT:				return "Temporary Redirect";
	case idk::status_code::BAD_REQUEST:						return "Bad Request";
	case idk::status_code::UNAUTHORIZED:					return "Unauthorized";
	case idk::status_code::PAYMENT_REQUIRED:				return "Payment Required";
	case idk::status_code::FORBIDDEN:						return "Forbidden";
	case idk::status_code::NOT_FOUND:						return "Not Found";
	case idk::status_code::METHOD_NOT_ALLOWED:				return "Method Not Allowed";
	case idk::status_code::NOT_ACCEPTABLE:					return "Not Acceptable";
	case idk::status_code::PROXY_AUTHENTICATION_REQUIRED:	return "Proxy Authentication Required";
	case idk::status_code::REQUEST_TIMEOUT:					return "Request Timeout";
	case idk::status_code::CONFLICT:						return "Conflict";
	case idk::status_code::GONE:							return "Gone";
	case idk::status_code::LENGTH_REQUIRED:					return "Length Required";
	case idk::status_code::PRECONDITION_FAILED:				return "Precondition Failed";
	case idk::status_code::PAYLOAD_TOO_LARGE:				return "Payload Too Large";
	case idk::status_code::URI_TOO_LONG:					return "Uri Too Long";
	case idk::status_code::UNSUPPORTED_MEDIA_TYPE:			return "Unsupported Media Type";
	case idk::status_code::RANGE_NOT_SATISFIABLE:			return "Range Not Satisfiable";
	case idk::status_code::EXPECTATION_FAILED:				return "Expectation Failed";
	case idk::status_code::UPGRADE_REQUIRED:				return "Upgrade Required";
	case idk::status_code::INTERNAL_SERVER_ERROR:			return "Internal Server Error";
	case idk::status_code::NOT_IMPLEMENTED:					return "Not Implemented";
	case idk::status_code::BAD_GATEWAY:						return "Bad Gateway";
	case idk::status_code::SERVICE_UNAVAILABLE:				return "Service Unavailable";
	case idk::status_code::GATEWAY_TIMEOUT:					return "Gateway Timeout";
	case idk::status_code::HTTP_VERSION_NOT_SUPPORTED:		return "Http Version Not Supported";
	default:												return "Unknown";
	}
}