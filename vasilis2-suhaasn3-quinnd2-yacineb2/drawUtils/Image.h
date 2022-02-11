/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"

class Image: public cs225::PNG{
public: 
//added by me

Image(); 

Image(unsigned int width, unsigned int height);
// // added by me
// Image(Image const & other);

// ~Image();
//     Image const & operator= (Image const & other){

//         return (Image) operator= (Image const & other)
//     };
//     bool operator== (PNG const & other) const;
//     bool operator!= (PNG const & other) const;

//increase luminance of every pixel by 0.1
void lighten(); 
//increase luminance of every pixel by "amount"
void lighten(double amount); 
//decrease luminance of every pixel by 0.1
void darken(); 
//decrease luminance of every pixel by "amount"
void darken(double amount); 
//increase saturation of every pixel by 0.1
void saturate(); 
//increase saturation of every pixel by "amount"
void saturate(double amount); 
//decrease saturation of every pixel by 0.1
void desaturate(); 
//decrease saturation of every pixel by "amount"
void desaturate(double amount); 
//turns the image grayscale
void grayscale(); 
//rotate the color wheel for every pixel by "degrees"
void rotateColor(double degrees); 
//illinify the image
void illinify(); 
//scale the image by a given "factor"
void scale(double factor); 
//scale the image to fit within the size "w" * "h"
void scale(unsigned w, unsigned h); 

//added by me
void scalexy (unsigned newWid, unsigned newHei);
};
