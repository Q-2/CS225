#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "airport.h"
#include "route.h"

using std::vector;

namespace FileIO {
    std::vector<Airport*> loadAirports(const std::string& airport_filename);
    
    std::vector<Route*> loadRoutes(const std::string& route_filename, const vector<Airport*>& airports);
}