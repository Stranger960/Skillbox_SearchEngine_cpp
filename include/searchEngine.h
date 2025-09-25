#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <algorithm> 
#include <chrono>
#include "nlohmann/json.hpp"
using namespace std;

const bool PRINT = !true;                                         //  debug print switch
#define    PAUSE this_thread::sleep_for(chrono::seconds(20));     //  delay before closing
