
#pragma once

#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace cs225;
using namespace std;
class SquareMaze {
    private:
        //matrix[y][x]
    pair<int,int> result;
    vector<vector<pair<bool,bool>>> matrix;
    int _height;
    int _width;
    DisjointSets dset;
    public:
    //Creates an empty maze
    SquareMaze();

    //Makes a new SquareMaze of given width and height
void makeMaze(int width, int height);

    //Checks if we can travel in a given direction. (is there a wall? etc)
bool canTravel (int x, int y, int dir) const;
    //Sets whether or not a specified wall exists.
void setWall(int x, int y, int dir, bool exists);

    //Solves the maze
vector<int> solveMaze();

    //Draws the maze w/out the soln.
PNG * drawMaze() const;

    //Draws the maze w     the soln.
PNG * drawMazeWithSolution();

};