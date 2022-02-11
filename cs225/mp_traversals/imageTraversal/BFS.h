/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"
#include <vector>
#include <queue>
#include <stack>
#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  ~BFS();
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  PNG* getPNG() ;


private:
  std::vector<Point> traversal_; // keeps a list of pixels in the order we want to see them.
	/** @todo [Part 1] */
	/** add private members hes*/
  PNG png;
  Point start;
  Point follower;
  int pos;
  HSLAPixel grabPixel(Point);
  double tolerance;
  bool delta(HSLAPixel, HSLAPixel);
  bool valid(Point);
  void visit(Point);
  bool checkon(Point);
  double getTolerance();
  std::vector<bool> visited_; // keeps a list of pixels that have been visited. position in vector based on pixel x,y
  std::queue<Point> tapeFeed_; // feeds pixels into the tester to decide whether or not to move them into the traversal vector
  Point curr;
  BFS* newMem = NULL;
};
