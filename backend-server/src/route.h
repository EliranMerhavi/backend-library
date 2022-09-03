#pragma once
#include "http_method.h"

namespace idk
{
	struct route
	{
		const http_method method;
		const std::string path;

		bool operator==(const route& other) const;
	};
}

template<>
struct std::hash<idk::route>
{
	size_t operator()(const idk::route& route) const
	{
		return std::hash<std::string>()(route.path) + (size_t)route.method;
	}
};
