#include "pch.h"
#include "route.h"

namespace idk
{
    bool route::operator==(const route& other) const
    {
        return this->method == other.method and this->path == other.path;
    }
}