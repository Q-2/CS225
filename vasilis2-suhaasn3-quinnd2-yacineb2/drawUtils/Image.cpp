/**
 * @file Image.cpp
 * Implementation of the Image class: A subclass of PNG with more member functions for modifying the image
 *
 * @author Yacine Boulaioune 
 */

#include "Image.h"
#include <cmath>
#include "cs225/PNG.h"
#include <iostream>

// added by me
Image::Image(): PNG(){

}

Image::Image(unsigned int width, unsigned int height): PNG (width,height){
}

void Image::lighten(){

for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & lumImg = this->getPixel(x,y).l ; 
      lumImg = ((lumImg+ 0.1)< 1)? lumImg+= 0.1 : lumImg =1.0; 
    }   
}
}
//increase luminance of every pixel by "amount"
void Image::lighten(double amount){

for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & lumImg = this->getPixel(x,y).l ; 
      lumImg = ((lumImg+ amount)< 1)? lumImg+= amount : lumImg =1.0; 
    }   
}

}
//decrease luminance of every pixel by 0.1
void Image::darken(){
for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & lumImg = this->getPixel(x,y).l ; 
      lumImg = ((lumImg- 0.1)> 0)? lumImg-= 0.1 : lumImg =0.0; 
    }   
}

}
//decrease luminance of every pixel by "amount"
void Image::darken(double amount){
for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & lumImg = this->getPixel(x,y).l ; 
      lumImg = ((lumImg- amount)> 0)? lumImg-= amount : lumImg =0.0; 
    }   
}

}
//increase saturation of every pixel by 0.1
void Image::saturate(){
for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & satImg = this->getPixel(x,y).s ; 
      satImg = ((satImg+ 0.1)< 1)? satImg+= 0.1 : satImg =1.0; 
    }   
}

}
//increase saturation of every pixel by "amount"
void Image::saturate(double amount){
  for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & satImg = this->getPixel(x,y).s ; 
      satImg = ((satImg+ amount)< 1)? satImg+= amount : satImg =1.0; 
    }   
}

}
//decrease saturation of every pixel by 0.1
void Image::desaturate(){
  for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & satImg = this->getPixel(x,y).s ; 
      satImg = ((satImg- 0.1)> 0)? satImg-= 0.1 : satImg =0.0; 
    }   
}

} 
//decrease saturation of every pixel by "amount"
void Image::desaturate(double amount){

for (unsigned x = 0; x < this->width(); x++)
  {
    for (unsigned y = 0; y < this->height(); y++)
    {
      double & satImg = this->getPixel(x,y).s ; 
      satImg = ((satImg- amount)> 0)? satImg-= amount : satImg =0.0; 
    }   
}
}; 
//turns the image grayscale
void Image::grayscale(){
for (unsigned x = 0; x < this-> width(); x++) {
    for (unsigned y = 0; y < this-> height(); y++) {
      double & pixelSat = this-> getPixel(x, y).s;
      pixelSat = 0;
    }
  }
}

//rotate the color wheel for every pixel by "degrees"
void Image::rotateColor(double degrees){

for (unsigned x = 0; x < this-> width(); x++) {
    for (unsigned y = 0; y < this-> height(); y++) {
      double & pixelHue = this-> getPixel(x, y).h;

      if ((pixelHue + degrees)> 360) pixelHue = pixelHue + degrees - 360; 
      
      else if ((pixelHue + degrees)< 0) pixelHue = pixelHue + degrees + 360; 

      else pixelHue += degrees; 
    }
  }
}

//illinify the image
void Image::illinify(){
 for (unsigned x = 0; x < this-> width(); x++)
  {
    for (unsigned y = 0; y < this-> height(); y++)
    {
      double & pixelHue = this-> getPixel(x, y).h;

      pixelHue = (abs(pixelHue - 216) < abs (pixelHue - 11) && abs(pixelHue - 216) < (371 - pixelHue)) ? 216: 11; 
    }
  }
}
//scale the image by a given "factor"
void Image::scale(double factor){

//SCALE ONLY IF FACTOR IS DIFFERENT THAN ONE
if (factor!= 1.0){
// make a copy of original image
cs225::PNG originalImg(*this); 

//resize original image
this->resize (this->width() * factor, this ->height() * factor); 

//scale the content of original image based on its copy
for (unsigned x = 0; x < this-> width() ; x++) {
    for (unsigned y = 0; y < this-> height() ; y++) {
    
    this->getPixel(x,y) = originalImg.getPixel(floor(x* 1/factor), floor(y* 1/factor));   
    }
  }

}
}

// scale the image to fit within the size "w" * "h"
void Image::scale(unsigned w, unsigned h){

double newFactor = (((double)w/ this->width()) > ((double)h/ this->height()))? ((double)h/ this->height()) : ((double)w/ this->width());

this->scale(newFactor);
}

/**********************************************************************/
// ADDED BY ME: scale image without preserving ratio
void Image::scalexy (unsigned newWid, unsigned newHei){
  //SCALE ONLY IF FACTOR IS DIFFERENT THAN ONE
double factorX = (double)newWid/(this->width()); 

double factorY = (double)newHei/(this->height()); 

if ((int)factorX != (int)this->width() || (int)factorY != (int)this->height() ){
// make a copy of original image
cs225::PNG originalImg(*this); 

//resize original image
this->resize (this->width() * factorX, this ->height() * factorY); 

//scale the content of original image based on its copy
for (unsigned x = 0; x < this-> width() ; x++) {
    for (unsigned y = 0; y < this-> height() ; y++) {
    
    this->getPixel(x,y) = originalImg.getPixel(floor(x* 1/factorX), floor(y* 1/factorY));   
    }
  }

}


}