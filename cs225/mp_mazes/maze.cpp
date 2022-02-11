/* Your code here! */
#include "maze.h"
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>       //lol
#include <queue>
#include <map>
#include <stack>
SquareMaze::SquareMaze(){

}

void SquareMaze::makeMaze(int width, int height){
    //me thinking up a matrix system of keeping track of all of this only to find that they wanted a system where you keep 2 bits per item. oops.


    //now we just: 
    //remove walls at random
    //and if a wall is of a distinct set, join it and remove the wall.
    //if it's not a distinct set, we don't remove the wall.
    //false means we haven't destroyed that wall. aka it exists.
    _height = height;
    _width = width;
    matrix.resize(width, std::vector<pair<bool,bool>>(height, pair<bool,bool>(false,false)));

    int i = 0;
    //vector of all walls. when removed from the list, the wall has been destroyed or ignored.
    vector<vector<pair<pair<bool,bool>*,pair<int,int>>>> allWalls; //vector<vector> -> 2d vector, pair<pair,pair>.first = walls of the corresponding coordinate. second = coordinate.
    

    allWalls.resize(width, 
    std::vector<pair<pair<bool,bool>*,pair<int,int>>>
                    (height,
                pair<pair<bool,bool>*,pair<int,int>>
                    (nullptr, pair<int,int>(0,0))));


    for(unsigned i = 0; i < matrix.size(); i++){
        for (unsigned j = 0; j < matrix[0].size(); j++){
            allWalls[i][j].first = &matrix[i][j];  
            allWalls[i][j].second = pair<int,int>(i,j);
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    dset.addelements(width*height);
    for (unsigned i = 0; i < allWalls[0].size(); i++){
        std::shuffle(allWalls[i].begin(),allWalls[i].end(),g);
    }
    std::shuffle(allWalls.begin(),allWalls.end(),g);
    
    for(auto currVec : allWalls){        
        for(auto currPair : currVec){
            auto x = currPair.second.first;
            auto y = currPair.second.second;
            auto currWalls = currPair.first;
            auto coordinate = (x + y*width); 

            if(x == width-1){continue;}
            if(dset.find(coordinate) != dset.find(coordinate+1)){
                currWalls->first = true;
                auto a = dset.find(coordinate);
                auto b = dset.find(coordinate+1);
                dset.setunion(a,b);
            }
            if(y == height-1){continue;}
            if(dset.find(coordinate) != dset.find(coordinate+width)){
                currWalls->second = true;
                auto a = dset.find(coordinate);
                auto b = dset.find(coordinate+width);
                dset.setunion(a,b);
            }
        }
    }
    std::cout << dset.size(0) << std::endl;
    
    std::cout << width*height << std::endl;
}
bool SquareMaze::canTravel (int x, int y, int dir) const {
    //0,1,2,3 right,down,left,up
    unsigned int xtest = x;
    unsigned int ytest = y;
    

    if(dir == 0){
        if(matrix.size() == xtest+1){return false;}
        return matrix[x][y].first; // first = right, second = down
    }
    if(dir == 1){
        if(matrix[0].size() == ytest+1){return false;}
        return matrix[x][y].second;
    }
    if(dir == 2){
        if(x<1) return false;
        return matrix[x-1][y].first;
    }
    if(dir == 3){
        if(y<1) return false;
        return matrix[x][y-1].second;
    }
    return false;
}
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    exists = !exists;
    unsigned xtemp = x;
    unsigned ytemp = y;
    if(xtemp < matrix.size()-1 && dir == 0){
        matrix[x][y].first = exists;
    }
    if(ytemp < matrix.size()-1 && dir == 1){
        matrix[x][y].second = exists;
    }
    

}

vector<int> SquareMaze::solveMaze(){
    //mark all nodes in the matrix as unvisited
    vector<int> path;
    vector<int> lowest;
    vector<int> visited;
    int curr;
    visited.resize(_width*_height,-1);
    visited[0]=0;
    lowest.resize(_width*_height, 0);
    queue<int> traversal;
    traversal.push(0);

    while(!traversal.empty()){
      curr = traversal.front();
      traversal.pop();
      unsigned int x = curr%_width;
      unsigned int y = curr/_width;

      if(canTravel(x,y,0) && visited[x+1+y*_width] == -1){
        visited[x+1+y*_width] = curr;
        traversal.push(x+1+y*_width);
        lowest[curr +1] = lowest[curr] +1;
      }
      if(canTravel(x,y,1) && visited[x+y*_width+_width] == -1){
        visited[x+y*_width+_width] = curr;
        traversal.push(x+y*_width+_width);
        lowest[curr + _width] = lowest[curr] +1;
        
      }
      if(canTravel(x,y,2) && visited[x+y*_width-1] == -1){
        visited[x+y*_width-1] = curr;
        traversal.push(x+y*_width-1);
        lowest[curr -1] = lowest[curr] +1;
      }
      if(canTravel(x,y,3) && visited[x+y*_width-_width] == -1){
        visited[x+y*_width-_width] = curr;
        traversal.push(x+y*_width-_width);
        lowest[curr -_width] = lowest[curr] +1;
      }
      
    }
    int longest = _width*(_height-1);
    for(int i = 0; i < _width; i++){
      if(lowest[_width *(_height-1)+i] > lowest[longest]){
        longest = _width*(_height -1) +i;
      }
    }
    int finx = longest % _width;
    int finy = longest / _width;
    result = pair<int,int>(finx,finy);
    vector<int> soln;
    int i = curr;
    while(i != 0){
      if(visited[i] == i - 1){
        soln.push_back(0);
      }
      if(visited[i] == i - _width){
        soln.push_back(1);
      }
      if(visited[i] == i + 1){
        soln.push_back(2);
      }
      if(visited[i] == i + _width){
        soln.push_back(3);
      }
      i = visited[i];
    }
    reverse(soln.begin(),soln.end());
    
  return soln;

}

    //Draws the maze w/out the soln.
PNG * SquareMaze::drawMaze() const{
  PNG* image = new PNG(_width*10+1,_height*10+1);
  for(int i = 0; i<_width; i++){
    for(int j = 0; j<_height; j++){
      if(j==0) {
        for(unsigned k=0; k<10; k++){
          if((i*10+k<1)||(i*10+k>9)){
            HSLAPixel & cur_pixel = image->getPixel(i*10+k, 0);
            cur_pixel.l = 0;
          }
        }
      }
      if(i==0) {
        for(unsigned k=0; k<10;k++){
          HSLAPixel & cur_pixel = image->getPixel(0, j*10+k);
          cur_pixel.l = 0;
        }
      }
      if(!canTravel(i,j,0)) {
        for(unsigned k=0; k<=10;k++){
          HSLAPixel & cur_pixel = image->getPixel((i+1)*10, j*10+k);
          cur_pixel.l = 0;
        }
      }
      if(!canTravel(i,j,1)) {
        for(unsigned k=0; k<=10;k++){
          HSLAPixel & cur_pixel = image->getPixel(i*10+k, (j+1)*10);
          cur_pixel.l = 0;
        }
      }
    }
  }
  return image;


}

    //Draws the maze w the soln.
PNG * SquareMaze::drawMazeWithSolution(){
    return drawMaze();
}
