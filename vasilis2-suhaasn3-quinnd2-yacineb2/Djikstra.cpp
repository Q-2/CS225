#include "graph.h"

using std::priority_queue;
using std::map;

/*
 * This includes the Dijkstra functions for the graph
 */

vector<Airport*> Graph::Dijkstra(Airport* start, Airport* dest)
{
    vector<Airport*> path; // to return
    priority_queue<Route, vector<Route>, std::greater<Route>> pq;
    
    map<unsigned, double> dist;
    map<unsigned, unsigned> prev; // mapping two IDs together
    
    for (Airport* a : V) {
        dist[a->getAirportID()] = std::numeric_limits<double>::infinity();
    }
    dist[start->getAirportID()] = 0;
    
    // get list of outgoing routes from airport (start) and push every route to pq
    list<Route*> outGoingRoutes = this->getOutRoutes(start);
    for (Route* route : outGoingRoutes) {
        pq.push(*route);
    }
    
    vector<Airport*> labeled;
    
    while (!pq.empty()) {
        Route r = pq.top();
        pq.pop();
        
        labeled.push_back(r.getRouteAirports().first);
        
        if (r.getRouteDistance() < dist[r.getRouteAirports().second->getAirportID()]) {
            dist[r.getRouteAirports().second->getAirportID()] = dist[r.getRouteAirports().first->getAirportID()]
                    + r.getRouteDistance();
            prev[r.getRouteAirports().second->getAirportID()] = r.getRouteAirports().first->getAirportID();
            
            for (Airport* a : getOutNeighbors(r.getRouteAirports().second)) {
                if (labeled.find(r.getRouteAirports().second) == labeled.end()) {
                    pq.push(Route(r.getRouteAirports().second, a));
                }
            }
        }
    }
    
    if (dist[dest->getAirportID()] == std::numeric_limits<double>::infinity()) {
        path.push_back(NULL);
    }
    
    while (dist[dest->getAirportID()] != 0) {
        path.push_back(dest);
        dest = getAirportWithID(prev[dest->getAirportID()]);
    }
    path.push_back(dest);
    return path;
}
