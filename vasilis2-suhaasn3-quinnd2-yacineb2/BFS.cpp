#include "graph.h"

/*
 * This file will contain the BFS related functions of the Graph class
 */

vector<Airport*> Graph::BFS()
{
    vector<Airport*> trav;
    unordered_map<Airport*, bool> visited;
    for(Airport* port : V)
    {
        visited[port] = 0;
    }

    vector<Airport*> connected; //single connected component
    for(Airport* port : V)
    {
        if(!visited[port])
        {
            connected = BFS(port, visited);
            trav.insert(trav.end(), connected.begin(), connected.end());
        }
    }
    return trav;
}

vector<Airport*> Graph::BFS(Airport* start, unordered_map<Airport*, bool>& visited)
{
    vector<Airport*> t;
    queue<Airport*> q;
    q.push(start);
    visited[start] = 1;
    Airport* v;
    while(!q.empty())
    {
        v = q.front();
        q.pop();
        t.push_back(v);
        for(Airport* w : getOutNeighbors(v))
        {
            if(!visited[w])
            {
                visited[w] = 1;
                q.push(w);
            }
        }
    }
    return t;
}
