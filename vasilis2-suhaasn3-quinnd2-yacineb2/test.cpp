#include "graph.h"
#include "route.h"
#include "airport.h"
#include "fileio.h"
#include "drawUtils/cs225/catch/catch.hpp"
#include <iostream>
#include "shortestPathVisualizer.h"
#include "drawUtils/cs225/PNG.h"
#include <algorithm>

using namespace std;

TEST_CASE("Simple Distance Check","[weight=1]"){
    Airport* ORD = new Airport (3830, "O'hare Airport", "Chicago", "USA", 41.9786, -87.9048 ); 

    Airport* CDG = new Airport (1381, "Charles Degaulle", "Paris", "France", 49.012798, 2.55 ); 

    Route* ORDtoCDG = new Route (ORD, CDG); 

    int dist = ORDtoCDG->getRouteDistance();
    REQUIRE((4138 == dist));
}

TEST_CASE("Route Class Works","[weight=1]"){
    std::vector<Airport*> airports = FileIO::loadAirports("airports_clean.csv");

    std::vector<Route*> routes = FileIO::loadRoutes("routes_clean.csv", airports);
    Airport* source = routes[6]->getRouteAirports().first;
    Airport* destination = routes[6]->getRouteAirports().second; 
    REQUIRE(source->getAirportID() == 4029);
    REQUIRE(destination->getAirportID() == 6969);
}

TEST_CASE("Graph node neighbor works","[weight=1]"){
    Graph* graph = new Graph( "airports_clean.csv" , "routes_clean.csv");
    Airport* airport79 = graph->getAirportWithID(79); // airport with ID 79
    vector<Airport*> outNeighbors = graph->getOutNeighbors(airport79); 
    REQUIRE(outNeighbors.size() == 3);
    REQUIRE(outNeighbors[0]->getAirportID() == 3830);
}
TEST_CASE("Visualization works","[weight=1]"){
    vector<Airport*> mapAirports; 
    Graph* graph = new Graph( "airports_clean.csv" , "routes_clean.csv");

    mapAirports.push_back(graph->getAirportWithID(3361)) ; // must show in Sydney
    mapAirports.push_back(graph->getAirportWithID(210)) ; // must show in algier
    mapAirports.push_back(graph->getAirportWithID(3364)) ; // must show in Beijing
    mapAirports.push_back(graph->getAirportWithID(820)) ; // must show in Johannesburg
    mapAirports.push_back(graph->getAirportWithID(1382)) ; // must show in Paris
    mapAirports.push_back(graph->getAirportWithID(3830)) ; // must show in chicago
  

    Image map = drawShortestPath(mapAirports); 

    map.writeToFile("map.png");
}
TEST_CASE("BFS Test","[weight=1]"){
    Graph* graph = new Graph( "airports_clean.csv" , "routes_clean.csv");
    auto BFS = graph->BFS();
    REQUIRE(6033 == BFS.size());
    sort(BFS.begin(),BFS.end());
    auto adj = adjacent_find(BFS.begin(),BFS.end());
    REQUIRE(adj == BFS.end());
     
    //There are 6033 airports, so if BFS works it should have 6033 airports.
}