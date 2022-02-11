#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(PNG* png,int i_){
  png_ = png;
  i = i_;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel = png_->getPixel(x,y);
  if(pixel.h + i > 360) {
    pixel.h = pixel.h - 360 + i;
  }
  else{
    pixel.h = pixel.h + i;
  }
  return pixel;
}
