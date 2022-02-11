#include "fileio.h"
#include <unordered_map>
#include <utility>

using std::getline;
using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::unordered_map; 
using std::pair; 

namespace FileIO {
    vector<Airport*> loadAirports(const string& airport_filename) {
        vector<Airport*> airports;
        ifstream my_file(airport_filename);
        string line;
        
        if (my_file.is_open()) {
            while (getline(my_file, line)) {
                
                stringstream s(line);
                string data[8];
                
                for (int i=0; i<8; i++) {
                   getline(s, data[i], ',');
                // std::cout << "  " <<data[i] << "  "; 
                }

                unsigned id = std::stoul(data[0]);
                string name = data[1];
                string city = data[2];
                string country = data[3];
                double latitude = std::stod(data[6]);
                double longitude = std::stod(data[7]);
                
                Airport* a = new Airport(id, name, city, country, latitude, longitude);
                airports.push_back(a);
                // std::cout << "\n"; 
            }
        }

        return airports; 
    }

    vector<Route*> loadRoutes(const std::string& route_filename, const vector<Airport*>& airports) {

        vector<Route*> routes;
        //instead of creating new airport objects we will use same airport objects from loadAirports
        unordered_map <unsigned, Airport*> IdAirportMap; // maps airport ID to its object pointe
        for (Airport* airport: airports)
            IdAirportMap.insert( make_pair ( airport->getAirportID() , airport) ); 

        ifstream my_file(route_filename);
        string line;

        if (my_file.is_open()) {
            while (getline(my_file, line)) {

                stringstream s(line);
                string data[7];
                
                for (int i=0; i<7; i++){
                   getline(s, data[i], ',');
                // std::cout << "  " <<data[i] << "  "; //check cleaniness
                }
                //check that really no route has any stop
                // if(std::stoul(data[6]) != 0){
                //     std::cout << "THERE IS A ROUTE THAT HAS A STOP!!!" ;
                //     exit;
                // }
                unsigned sourceAirportID = std::stoul(data[3]);
                unsigned destinationAirportID = std::stoul(data[5]); 
                
            // if both airports exist in the airports dataset
            if (IdAirportMap.find(sourceAirportID) != IdAirportMap.end() && IdAirportMap.find(destinationAirportID) != IdAirportMap.end() )
            {   
                Route* route = new Route(IdAirportMap[sourceAirportID], IdAirportMap[destinationAirportID] );

                routes.push_back(route);
            }

            // std::cout << "\n"; 
        }
        }

        return routes;
}

}