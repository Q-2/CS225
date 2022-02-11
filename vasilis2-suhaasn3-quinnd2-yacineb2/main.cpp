
#include "graph.h"
#include "airport.h"
#include "route.h"
#include "fileio.h"
#include "shortestPathVisualizer.h"

#include <iostream>
#include <vector>
#include <utility> 

using std::cout; 

int main(){
    
    Airport* ORD = new Airport (3830, "O'hare Airport", "Chicago", "USA", 41.9786, -87.9048 ); 

    Airport* CDG = new Airport (1381, "Charles Degaulle", "Paris", "France", 49.012798, 2.55 ); 

    Route* ORDtoCDG = new Route (ORD, CDG); 

    cout << "Distance from ORD to CDG is " << ORDtoCDG->getRouteDistance() << " miles.\n\n";  
   
   
   std::vector<Airport*> airports = FileIO::loadAirports("airports_clean.csv");

   cout << "\nAirport 1: " << airports[0]->getAirportID() << "  " <<  airports[0]->getAirportLatitude() << 
   "  " << airports[0]->getAirportLongitude() << " \n";

   std::vector<Route*> routes = FileIO::loadRoutes("routes_clean.csv", airports);

   //check route number 7 for example 
   Airport* source = routes[6]->getRouteAirports().first;
   Airport* distination = routes[6]->getRouteAirports().second; 

   cout << "\nRoute 7: " << source->getAirportID() << " --> " <<  distination->getAirportID() << " \n";


   Graph* graph = new Graph( "airports_clean.csv" , "routes_clean.csv");
   
    // as a simple test we will output the outgoing airport neighbors of a certain airport and check that with dataset

   Airport* airport79 = graph->getAirportWithID(79); // airport with ID 79


   vector<Airport*> outNeighbors = graph->getOutNeighbors(airport79); 
   cout << "\nOutgoing Neighbor Airports for Airport with ID: " << airport79->getAirportID() << " are airports with IDs:  ";
   for (Airport* airport: outNeighbors)
       cout<< airport->getAirportID() << " ";    

   cout << " \n ==> It has direct flight to " << outNeighbors.size() << "  airports \n";
   
    //////// test map 
  vector<Airport*> mapAirports; 
  mapAirports.push_back(graph->getAirportWithID(3361)) ; // must show in Sydney
  mapAirports.push_back(graph->getAirportWithID(210)) ; // must show in algier
  mapAirports.push_back(graph->getAirportWithID(3364)) ; // must show in Beijing
  mapAirports.push_back(graph->getAirportWithID(820)) ; // must show in Johannesburg
  mapAirports.push_back(graph->getAirportWithID(1382)) ; // must show in Paris
  mapAirports.push_back(graph->getAirportWithID(3830)) ; // must show in chicago
  

   Image map = drawShortestPath(mapAirports); 

   map.writeToFile("map.png");
   return 0;
}