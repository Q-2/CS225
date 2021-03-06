/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    ~Iterator();

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);
    bool valid(Point);
    Iterator(ImageTraversal& traversal, Point start);
    Iterator(ImageTraversal& traversal);
    /** @todo [Part 1] */
    /** add member functions if neccesary*/

  private:
    /** @todo [Part 1] */
    ImageTraversal * traversal;
    Point current;
    Point start;
    bool extinguished;
    /** add private members here if neccesary*/

  };
  virtual ~ImageTraversal();

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;
  virtual void visit(Point) = 0;
  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;
  virtual double getTolerance() = 0;
  virtual HSLAPixel grabPixel(Point) = 0;
  virtual PNG* getPNG() = 0;
  virtual bool checkon(Point) =0;
private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
};
