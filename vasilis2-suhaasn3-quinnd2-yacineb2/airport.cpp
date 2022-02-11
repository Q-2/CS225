#include "airport.h"

//custom constructor
Airport::Airport(unsigned id, string name, string city, string country, 
double latitude, double longitude): _id(id), _name(name), 
_city(city), _country(country), _latitude (latitude), 
_longitude(longitude) 
{ }

//copy constructor
Airport::Airport(const Airport& other) {
    _id = other.getAirportID();
    _name = other.getAirportName();
    _city = other.getAirportCity();
    _country = other.getAirportCountry();
    _latitude = other.getAirportLatitude();
    _longitude = other.getAirportLongitude();
}

// = operator
bool Airport::operator==(const Airport& other) const {

    return ( _id == other.getAirportID() ); 
}
//getters 

unsigned Airport::getAirportID() const{
    return _id;
}
string Airport::getAirportName() const{
    return _name;
}
string Airport::getAirportCity() const{
    return _city;
}
string Airport::getAirportCountry() const{
    return _country;
}
double Airport::getAirportLatitude() const{
    return _latitude;
} 
double Airport::getAirportLongitude() const{
    return _longitude;
} 