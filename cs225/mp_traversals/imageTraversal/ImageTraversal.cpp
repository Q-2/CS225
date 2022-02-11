#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(): traversal(), extinguished(true)
 {   
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal& traversal)
    : traversal(&traversal), extinguished(true)
{
    current = traversal.peek();
}
ImageTraversal::Iterator::Iterator(ImageTraversal& traversal, Point start): traversal(&traversal), start(start), extinguished(false)
{
  traversal.add(start);
  current = traversal.peek();
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
/**  if(!traversal->empty()){
    current = traversal->pop();
    traversal->add(current);
    current = traversal->peek();
  }
  return *this;
  */
  auto topper = traversal->pop();
  traversal->visit(topper);
  auto right = Point(topper.x+1,topper.y);
  auto down  = Point(topper.x,topper.y+1);
  auto left  = Point(topper.x-1,topper.y);
  auto up    = Point(topper.x,topper.y-1);
  if(valid(right)){
    traversal->add(right);
  }
  if(valid(down)){
    traversal->add(down);
  }
  if(valid(left)){
    traversal->add(left);
  }
  if(valid(up)){
    traversal->add(up);
  }
  if(traversal->empty()) {
    *this = Iterator();
    return *this;
  }
  while ( !(traversal->empty()) && (traversal->checkon(traversal->peek()))) {
    traversal->pop();
  }
  if(!traversal->empty()) {current = traversal->peek();}
  if(traversal->empty())  {extinguished = true;}
  return *this;
}
bool ImageTraversal::Iterator::valid(Point p){
  auto tolerance = traversal->getTolerance();  
  if(p.x >= traversal->getPNG()->width() || p.y >= traversal->getPNG()->height()) {return false;}
  if(calculateDelta(traversal->grabPixel(p),traversal->grabPixel(start)) >= tolerance) {return false;}
  return true;
}
ImageTraversal::Iterator::~Iterator() {
	if (traversal != NULL) {}
	traversal = NULL;
}

ImageTraversal::~ImageTraversal() {
	// Nothing
}
/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return current;
}


/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  return !(extinguished && other.extinguished);
}

