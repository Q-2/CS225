/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"

#include <vector>
using std::vector;

class StickerSheet {

public: 

// declare instance variables
Image* basePicture = NULL;  // stores base picture on which to apply stickers

unsigned int maxStickers;  // max number of stickers that can be stored

vector<Image*> stickerLayers; // stores layers made out of stickers

vector<Image*> stickersVector; //stores raw stickers 


// custom constructor
 StickerSheet (const Image &picture, unsigned max);
 	
// destructor
 ~StickerSheet ();
 	
// copy constructor 
 StickerSheet (const StickerSheet &other);
 
// = operator
const StickerSheet & operator= (const StickerSheet &other);
 
void changeMaxStickers (unsigned max);

int addSticker (Image &sticker, unsigned x, unsigned y);
 	
bool translate (unsigned index, unsigned x, unsigned y);

void removeSticker (unsigned index);

Image * getSticker (unsigned index);
 
Image render () const;

// ADDED BY ME FOR A GOOD DESIGN
// clear helper function
void clear(); 

// copy helper function 
void copy(const StickerSheet & other); 

// draw sticker helper function
Image* drawSticker(unsigned stickerIndex, unsigned x, unsigned y);

}; 