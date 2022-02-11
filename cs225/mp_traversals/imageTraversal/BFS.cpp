#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) : png(png), start(start), tolerance(tolerance)
{  
  /** @todo [Part 1] */
  tapeFeed_.push(start);
  visited_.resize(png.width()*png.height(), false);
  visited_[0] = true;
}
BFS::~BFS() {

}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */ 
  return ImageTraversal::Iterator(*this,start);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

bool BFS::valid(Point point){
  if(point.x >= png.width() || point.y >= png.height()) {return false;}
  if(visited_[(point.y)* png.width() + (point.x)]) {return false;}
  return true;
}
double BFS::getTolerance() {
  return tolerance;
}
HSLAPixel BFS::grabPixel(Point p) {
  
  return png.getPixel(p.x,p.y);
}
  PNG* BFS::getPNG() {
    return &png;
  }

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  tapeFeed_.push(point);

  /** @todo [Part 1] */
}
void BFS::visit(Point point){
   if(point.x >= png.width() || point.y >= png.height()) {return;}
  visited_[(point.y)* png.width() + (point.x)] = true;
  return ;
}
bool BFS::checkon(Point point){
   if(point.x >= png.width() || point.y >= png.height()) {return true;}
  return visited_[(point.y)* png.width() + (point.x)];
}
/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  auto temp = tapeFeed_.front();
  tapeFeed_.pop();
  return temp;
  

}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return tapeFeed_.front();
}
/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return tapeFeed_.empty();
}
