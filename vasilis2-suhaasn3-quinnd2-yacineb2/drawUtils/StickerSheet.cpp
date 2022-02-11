#include "StickerSheet.h"
#include "Image.h"
#include <vector>
#include <cmath>
 
using std::vector; 
 
 /*************************************************************************************/
 StickerSheet::StickerSheet (const Image &picture, unsigned max){

     basePicture = new Image(picture); 
     maxStickers = max; 
 }

/*************************************************************************************/  
 StickerSheet::~StickerSheet (){
     clear(); 
 };

/*************************************************************************************/ 
 StickerSheet::StickerSheet (const StickerSheet &other){
  copy(other); 
 }

/*************************************************************************************/ 
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
if (this != &other){
clear(); 
copy(other); 
}
return *this; 
}

 /*************************************************************************************/
void StickerSheet::changeMaxStickers (unsigned max){

unsigned int currentSize= stickerLayers.size(); 

if (max < currentSize){
  
for (unsigned i= max ; i < currentSize; i++) {
// delete extra stickers from vector and MEMORY!
    delete stickerLayers[i]; 
    stickerLayers[i]= NULL; 
    stickerLayers.pop_back(); 

    delete stickersVector[i]; 
    stickersVector[i]= NULL; 
    stickersVector.pop_back();
}
}

maxStickers = max; 
}

/*************************************************************************************/
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){

unsigned latestStickerIndex = stickerLayers.size() -1; 

if ( (latestStickerIndex +1 )< maxStickers) {

Image* newSticker = new Image(sticker);
stickersVector.push_back(newSticker); 

Image* layer = drawSticker(latestStickerIndex +1 ,x,y); 

if (layer != NULL) {
stickerLayers.push_back(layer); 
return stickerLayers.size() - 1; 
}

delete stickersVector[stickersVector.size() - 1];
stickersVector.pop_back(); 
return -1; 
}
return -1; 
}


 /*************************************************************************************/   
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){

if (index > stickerLayers.size()) return false; 

Image * newLayer = drawSticker(index, x,y); 

if (newLayer != NULL){
stickerLayers[index] = newLayer; 

return  true;
}
return false; 

}

/*************************************************************************************/
void StickerSheet::removeSticker (unsigned index){

delete stickerLayers[index]; 
stickerLayers[index]= NULL; 
stickerLayers.erase(stickerLayers.begin() + index); 

delete stickersVector[index]; 
stickersVector[index]= NULL; 
stickersVector.erase(stickersVector.begin() + index); 

}

/*************************************************************************************/
Image * StickerSheet::getSticker (unsigned index){

if ( stickersVector[index] == NULL || index > (stickersVector.size() -1)) return NULL; 

return stickersVector[index]; 
}

/*************************************************************************************/
Image StickerSheet::render () const{

Image renderedPic(*basePicture); 

//resize basePicture to correct size to fit all stickers
unsigned maxWidth = basePicture->width(); 
unsigned maxHeight = basePicture->height(); 

for (unsigned k=0; k<  stickerLayers.size(); k++ ){
if (stickerLayers[k]->width() > maxWidth) maxWidth = stickerLayers[k]->width(); 

if (stickerLayers[k]->height() > maxHeight) maxHeight = stickerLayers[k]->height(); 
}

if(renderedPic.width() != maxWidth || renderedPic.height() != maxHeight)

renderedPic.scalexy(maxWidth, maxHeight); //scaling without keeping original ratio

for (unsigned k=0; k< stickerLayers.size(); k++ ){

  for (unsigned i= 0; i < stickerLayers[k]->width() ; i++){
  for (unsigned j= 0; j < stickerLayers[k]->height(); j++) {

if (stickerLayers[k]->getPixel(i,j).a !=0 )

renderedPic.getPixel(i,j) = stickerLayers[k]->getPixel(i,j); 

} } }

return renderedPic; 
 }

/*************************************************************************************/
void StickerSheet::clear(){
if (basePicture != NULL)
delete basePicture; 

for (int i=0; i< (int) stickerLayers.size() ; i++) {
if (stickerLayers[i] != NULL)
delete stickerLayers[i]; 
}

for (int i=0; i< (int) stickersVector.size() ; i++) {
if (stickersVector[i] != NULL) 
delete stickersVector[i]; 
}
}

/*************************************************************************************/
void StickerSheet::copy (const StickerSheet & other){
     // make a deep copy 

     basePicture = new Image (*(other.basePicture)); 
     maxStickers = other.maxStickers; 
     
     for (int i=0; i< (int) other.stickerLayers.size(); i++)
        stickerLayers.push_back(new Image(*((other.stickerLayers)[i])));

    for (int i=0; i< (int) other.stickersVector.size(); i++)
       stickersVector.push_back(new Image(*((other.stickersVector)[i])));
}

/*************************************************************************************/
Image* StickerSheet::drawSticker (unsigned stickerIndex, unsigned x, unsigned y) {

Image* sticker = stickersVector[stickerIndex]; 

unsigned int widthBaseImage = basePicture->width();            
unsigned int heightBaseImage = basePicture->height() ;   

unsigned int stickerWidth = sticker->width(); 
unsigned int stickerHeight = sticker->height();

// calculate size of layer depending if sticker overflows
unsigned int newWidthBaseImage = ( (x+ stickerWidth) > widthBaseImage )? x+stickerWidth : widthBaseImage; 

unsigned int newHeightBaseImage = ( (y+ stickerHeight) > heightBaseImage )? y+stickerHeight : heightBaseImage; 

if ( stickerLayers.size() > stickerIndex ) delete stickerLayers[stickerIndex]; // specifically for translate() function: get rid of original sticker to draw new sticker

Image* layer= new Image(newWidthBaseImage, newHeightBaseImage);  // layer image

// draw sticker on layer
for (unsigned i= 0; i < newWidthBaseImage ; i++){
  for (unsigned j= 0; j < newHeightBaseImage; j++) {

if ( (i>=x && i< (x+ stickerWidth)) && (j>=y && j < (y+ stickerHeight)) )

layer ->getPixel(i,j) = sticker->getPixel(i-x, j-y); // assign sticker pixel to corresponding layer pixel

else layer ->getPixel(i,j).a =0;  // make other pixel transparent
}
}

return layer; 
}