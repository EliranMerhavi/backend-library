#pragma once

// data structers
#include <string>
#include <unordered_map>
#include <unordered_set>


//streams
#include <fstream>
#include <iostream>
#include <sstream>

//utils
#include <thread>
#include <regex>

#include "json/json.hpp"

using json = nlohmann::json;


// for socket i/o
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

