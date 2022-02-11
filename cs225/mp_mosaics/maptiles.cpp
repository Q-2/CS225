/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    auto result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> p;
    map<Point<3>, TileImage*> map;
    
    for(vector<TileImage>::iterator i = theTiles.begin() ; i!= theTiles.end(); i++){
        LUVAPixel pix = i->getAverageColor();
        Point<3> point = convertToXYZ(pix);
        p.push_back(point);
        map[point] = &*i;
    }

    KDTree<3> pogger(p);

    for(int x = 0; x < result->getRows(); x++){
        for(int y = 0; y < result->getColumns(); y++){
            LUVAPixel pix2 = theSource.getRegionColor(x,y);
            Point<3> temp = convertToXYZ(pix2);
            Point<3> nearest = pogger.findNearestNeighbor(temp);
            TileImage* best = map[nearest];
            result->setTile(x,y,best);
        }
    }
    return result;
}

