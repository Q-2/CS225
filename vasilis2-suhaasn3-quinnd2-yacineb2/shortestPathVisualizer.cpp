#include "shortestPathVisualizer.h"
#include <string>
#include <math.h>
#include <cmath> 
#include <utility>

using std::string; 
using std::vector; 
using std::pair;

Image drawShortestPath(vector<Airport*> dijkstraOut){
unsigned nbrAirports = dijkstraOut.size(); 
vector<pair<int,int>> dimensions;   

Image worldMap, letter[26], dots[3], finalMap; 
worldMap.readFromFile("drawUtils/mercatorProjection.png");
unsigned mapWidth = worldMap.width(); 
unsigned mapHeight = worldMap.height(); 

string s="drawUtils/letters/";

for (int i=0; i<26; i++){
    letter[i].readFromFile (s+char(97+i)+".png");
    letter[i].scale(10,10);
}

dots[0].readFromFile(s+"greendot.png");
dots[0].scale(10,10);
dots[1].readFromFile(s+"yellowdot.png"); 
dots[1].scale(10,10);
dots[2].readFromFile(s+"reddot.png"); 
dots[2].scale(10,10);


for (unsigned j=0; j<nbrAirports; j++){
//Mercato Projection
 int x= (int)( (mapWidth/360.0)*(180+ dijkstraOut[j]->getAirportLongitude())) -10; 
 int y= (mapHeight / 2) - (mapWidth * log(tan((M_PI / 4) + (dijkstraOut[j]->getAirportLatitude() * M_PI) /360))) / (2 * M_PI);
 
 dimensions.push_back(std::make_pair(x,y));
}

//draw lines first
cs225::HSLAPixel orange(32,0.97,0.46,1);

for (int a=0; a< (int)(nbrAirports -1); a++){

int x1 = dimensions[a].first; 
int y1 = dimensions[a].second; 
int x2 = dimensions[a+1].first; 
int y2 = dimensions[a+1].second; 
int minx = (x1>x2)? x2: x1;
int maxx = (minx == x1)? x2: x1;
int miny = (y1>y2)? y2: y1;
int maxy = (miny == y1)? y2: y1;
double slope = (double)(y2 -y1)/(x2- x1) ; 
if ((maxx - minx)<3){

for (int j=miny; j<maxy; j++){

    for (int k= 3; k <7; k++){
    if ((x2 + k) < (int)mapWidth){
        worldMap.getPixel(x2+k,j+5) = orange;    
    }
}
}
} else{
for (int i = minx; i< maxx; i++){
    
    int j =0; 
    if (slope < 0) j = (int)( slope * ( i - minx)) + maxy; 
    else j = (int)( slope * ( i - minx)) + miny;
    
    for (int k= 3; k <7; k++){
    if ((j + k) < (int)mapHeight){
        worldMap.getPixel(i+4,j+k) = orange; 
    }
    }
}
}
}

StickerSheet flightMap(worldMap, nbrAirports* 100);

for (unsigned j=0; j<nbrAirports; j++){
 //draw points
 int x= dimensions[j].first;
 int y= dimensions[j].second;
 
 if ( j == 0) flightMap.addSticker(dots[0], x, y);
 else if (j == (nbrAirports -1)) flightMap.addSticker(dots[2], x, y);
 else flightMap.addSticker(dots[1], x, y);

//draw city name
string city = dijkstraOut[j]->getAirportCity(); 
int xCity = x; 

for (char c: city){
    int ascii = std::tolower(int(c)); 
    if ( ascii >= 97 && ascii <=122) 
    flightMap.addSticker(letter[ascii-97], xCity, y+10); 
    
    xCity+=5;
    if (c== 'i' || c == 'l' || c == 'j') xCity -=3; 
}
}

finalMap = flightMap.render(); 

// (optional) crop image to remove parts of the map 
finalMap.crop(0,150);
return finalMap;

}
