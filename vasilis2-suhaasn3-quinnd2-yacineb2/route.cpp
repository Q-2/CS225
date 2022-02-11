#include "route.h"
#include "airport.h"
#include <math.h>
#include <cmath> 
#define earthRadiusMiles 3956.0


// custom constructor
Route:: Route(Airport* sourceAirport, Airport* destinationAirport){

    _sourceAirport = sourceAirport; 
    _destinationAirport = destinationAirport; 
    _routeDistance = calculateRouteDistance ( sourceAirport, destinationAirport);
}

//copy constructor (no need to delete original airport objects (vertices))
Route::Route(const Route& other){
  _sourceAirport = other.getRouteAirports().first; 
  _destinationAirport = other.getRouteAirports().second; 
}

// custom destructor
Route:: ~Route() {
  delete _sourceAirport; 
  delete _destinationAirport; 
} 

// check if two routes are same
bool Route::operator==(const Route& other) const {

return ( _sourceAirport == other.getRouteAirports().first && _destinationAirport == other.getRouteAirports().second ) ;

}

bool Route::operator>(const Route& other) const {
    return _routeDistance > other._routeDistance;
}

// Using "Haversine" formula to calculate the distance between two airports based on their longitude and latitude 
double Route::calculateRouteDistance  (Airport* sourceAirport , Airport* destinationAirport){

  double latiSourRad = sourceAirport-> getAirportLatitude() * M_PI / 180; 
  double longSourRad = sourceAirport-> getAirportLongitude()* M_PI / 180; 
  double latiDistRad = destinationAirport-> getAirportLatitude() * M_PI / 180; 
  double longDistRad = destinationAirport-> getAirportLongitude() * M_PI / 180; 

  double u = sin((latiDistRad - latiSourRad)/2);
  double v = sin((longDistRad - longSourRad )/2);
  return 2.0 * earthRadiusMiles * asin(sqrt(u * u + cos(latiSourRad) * cos(latiDistRad) * v * v));
}

// get pair.first ==> source airport*   pair.second ==> destination airport*
pair <Airport*, Airport*> Route::getRouteAirports () const{

    return make_pair(_sourceAirport, _destinationAirport);
}

double Route::getRouteDistance(){

    return _routeDistance;
}