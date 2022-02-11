#pragma once 

#include <string>
using std::string;

/* This class wraps info about an airport */ 
class Airport {

public:
     // custom constructor 
     Airport(unsigned id, string name, string city, string country, double latitude, double longitude);
     
     //copy constructor
     Airport(const Airport& other); 
     
     // two airports are equal if the share the same ID
     bool operator==(const Airport& other) const ;

     //getters 
     unsigned getAirportID() const; 
     string getAirportName() const;
     string getAirportCity() const;
     string getAirportCountry() const;
     double getAirportLatitude() const; 
     double getAirportLongitude() const;

private:     

  unsigned _id; 
  string _name; 
  string _city; 
  string _country; 
  double _latitude; 
  double _longitude; 


 };