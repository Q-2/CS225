#include "graph.h"
#include "fileio.h"

#include <utility>



// custom constuctor: build the whole graph based on airports and routes datasets
Graph::Graph(const string& airportsDatasetName , const string& routesDatasetName){

    //load airports 
    vector<Airport*> airportsVector = FileIO::loadAirports (airportsDatasetName); 

    unsigned index = 0; 
    for (Airport* airport: airportsVector){
         V.push_back(airport); 
         airportMap.insert( make_pair ( airport->getAirportID() , make_pair(airport, index)) ); 
         index ++; 
    }

    //set the length of adjacency list equal to number of vertices (airports)
    Adj = new list<Route*>[V.size()]; 

    // construct edges
    connectVertices (routesDatasetName); 

}

// custom destructor
Graph::~Graph(){

    // deallocate edges
    for (unsigned i=0; i< V.size(); i++){

       for (Route* route: Adj[i]){
          delete route; 
       }

       Adj[i].clear(); // clear all content and set size of list to 0
       std::list<Route*>().swap(Adj[i]); // set list capacity to 0 
    }

    delete[]  Adj;

    //deallocate vertices
    for (Airport* airport: V){
        delete airport; 
    }
    V.clear(); 
    V.shrink_to_fit(); // shrink vector to capacity 0

    //deallocate map
    // TO DO
}

// This helper function connects all airports (vertices) that have a connecting route (edge) 
void Graph::connectVertices (const string& routesDatasetName) {

    vector<Route*> routes = FileIO::loadRoutes (routesDatasetName, V);

    for (Route* route: routes)
       addEdge (route->getRouteAirports().first , route); 

}

// This helper function connects two airports with and edge (a route)
void Graph::addEdge (Airport* sourceAirport, Route* outGoingRoute){
    //use airportMap to retrieve adjacency list index corresponding to source airport
    Adj[airportMap[sourceAirport->getAirportID()].second].push_back (outGoingRoute);
}

// FUNCTIONS HERE
Airport* Graph::getAirportWithID (unsigned airportID){

    if (airportMap.find(airportID) == airportMap.end())  return nullptr; 

    return airportMap[airportID].first;
}



vector<Airport*> Graph::getOutNeighbors( Airport* sourceAirport){

    vector<Airport*> outNeighbors; 

    // if airport is not found in graph, return an empty vector 
    if (airportMap.find(sourceAirport->getAirportID()) == airportMap.end())  return outNeighbors; 

    //else
    unsigned adjListIndex = airportMap[sourceAirport->getAirportID()].second; 
    for (Route* route: Adj[adjListIndex])
         outNeighbors.push_back(route->getRouteAirports().second);

    return outNeighbors;
}

// this method return a (linked)-list of outgoing routes corresponding to an airport
list<Route*> Graph::getOutRoutes (Airport* airport){

return Adj[airportMap[airport->getAirportID()].second]; 

}
