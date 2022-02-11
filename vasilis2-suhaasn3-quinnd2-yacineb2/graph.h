#pragma once
#include "airport.h"
#include "route.h"
#include "fileio.h"

#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <queue>
#include <map>
#include <limits>

using std::vector; 
using std::list; 
using std::string; 
using std::unordered_map; 
using std::pair;
using std::queue;

class Graph {

    public:

    // constuctor of graph from Airports and Routes datasets
    Graph(const string& airportsDatasetName , const string& routesDatasetName); 
    // in our case: airportsDataSetName = "airports_clean.csv" 
    // routesDatasetName = "routes_clean.csv"

    // destructor that deallocates all vertices and edges
    ~Graph(); 

    //ADD FUNCTIONS HERE -----
    
    // this function returns corresponding airport(node) given an Airport ID
    Airport* getAirportWithID (unsigned airportID);

    //This function returns all destination Airports (Adjacent outgoing nodes) for a source Airport
    vector<Airport*> getOutNeighbors( Airport* sourceAirport);
    
    // this function returns a (linked)-list of outgoing routes corresponding to an airport
    list<Route*> getOutRoutes (Airport* airport); 
    
    
    vector<Airport*> BFS(Airport* start, unordered_map<Airport*, bool>& visited);    //helper for the full traversal returns traversal of connected component
    vector<Airport*> BFS(); //this is more of a breadth first traversal than a search
    vector<Airport*> Dijkstra(Airport* start, Airport* dest);
    
    //helper functions
    // This function populates the adjacency list based on Routes dataset
    void connectVertices (const string& routesDatasetName);
    //This function assign a route to an airport
    void addEdge (Airport* sourceAirport, Route* outGoingRoute); 
    
    private:

    vector<Airport*> V; 
    list<Route*>* Adj; 
    
    // This map takes an airport ID as KEY 
    // and returns a pair <Pointer to airport object, index in adjacency list> as VALUE
    unordered_map <unsigned, pair<Airport*, unsigned>> airportMap;
};
