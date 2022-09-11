#pragma once

#include "http_method.h"
#include <string>

namespace idk
{
	struct route
	{
		http_method method;
		std::string path;

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
