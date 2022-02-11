#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    deepCopy_ = new cs225::PNG(picture);
    init_deepX = deepCopy_->width();
    init_deepY = deepCopy_->height();

    for(unsigned int i = 0; i < max; i++){
        sheet.push_back(nullptr);
        x_vec.push_back(0);
        y_vec.push_back(0);
    }
}

StickerSheet::~StickerSheet() {
    
    for(unsigned int i = 0; i < sheet.size() ; i++){

        sheet.pop_back();
        x_vec.pop_back();
        y_vec.pop_back();
    }
}
StickerSheet::StickerSheet( const StickerSheet &other) {
    if (deepCopy_) {
        delete deepCopy_;
        }
    //deepcopy copier:
    deepCopy_ = new cs225::PNG(*other.deepCopy_);
    for(unsigned int i = 0; i < sheet.size() ; i++){
        if(sheet[i] != nullptr){
            delete sheet[i]; 
            }
        sheet.pop_back();
        x_vec.pop_back();
        y_vec.pop_back();
        
    }
    for(unsigned int i = 0; i < other.sheet.size(); i++){
        sheet.push_back(nullptr);
        x_vec.push_back(0);
        y_vec.push_back(0);
    }
    for(unsigned int i = 0; i < other.sheet.size(); i++){
        addSticker(*other.sheet[i],other.x_vec[i],other.y_vec[i]);

    }
}
const StickerSheet & StickerSheet::operator=( const StickerSheet &other){
    if (this != &other) {
        if (deepCopy_) {
        delete deepCopy_;
        }
    //deepcopy copier:
    deepCopy_ = new cs225::PNG(*other.deepCopy_);
    for(unsigned int i = 0; i < sheet.size() ; i++){
        if(sheet[i] != nullptr){
            delete sheet[i]; 
            }
        sheet.pop_back();
        x_vec.pop_back();
        y_vec.pop_back();
        
    }
    for(unsigned int i = 0; i < other.sheet.size(); i++){
        sheet.push_back(nullptr);
        x_vec.push_back(0);
        y_vec.push_back(0);
    }
    for(unsigned int i = 0; i < other.sheet.size(); i++){
        addSticker(*other.sheet[i],other.x_vec[i],other.y_vec[i]);

    }
    }
    return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
    if(max > sheet.size()){
        for (unsigned int i = sheet.size(); i < max; i++){
  
            sheet.push_back(nullptr);
            x_vec.push_back(0);
            y_vec.push_back(0);
            
        }
    }
    else{
        for (unsigned int i = sheet.size(); i > max; i--){


            
            sheet.pop_back();
            x_vec.pop_back();
            y_vec.pop_back();

        }
    }
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    for(unsigned int i = 0; i < sheet.size() ; i++) {
        if (sheet[i] == nullptr) {
            sheet[i] = &sticker;
            x_vec[i] = x;
            y_vec[i] = y;
            return i;
        }

    }
    return -1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (sheet[index] != nullptr) {
        x_vec[index] = x;
        y_vec[index] = y;
        return true;
    }
    else {
        return false;
    }
}
void StickerSheet::removeSticker(unsigned index){
    sheet[index] = nullptr;
    x_vec[index] = 0;
    y_vec[index] = 0;
}
Image* StickerSheet::getSticker(unsigned index){
    if (sheet[index] == nullptr){
        return NULL;
    }
    else{
        return sheet[index];
    }
}
Image StickerSheet::render() const {
     unsigned int width1=deepCopy_->width();
    unsigned int height1=deepCopy_->height();

    Image result;   
    result.resize(width1,height1);
    for(unsigned int w = 0; w < deepCopy_->width(); w++) {
			for (unsigned int h = 0; h < deepCopy_->height(); h++) {
                cs225::HSLAPixel& pixel = result.getPixel(w,h);
                cs225::HSLAPixel& pixelres = deepCopy_->getPixel(w,h);
                pixel = pixelres;
                }
    }

    //image is now a copy of deepcopy
    int resizetest = 0;
    for (unsigned int i = 0 ; i < sheet.size(); i++){
        if (sheet[i] == nullptr){
            continue;
        }
        if (x_vec[i] + sheet[i]->width() >  result.width() ){
            result.resize( x_vec[i] + sheet[i]->width(),result.height());
            resizetest++;   
        }
        if (y_vec[i] + sheet[i]->height() >  - result.height() ){
            result.resize(result.width(), y_vec[i] + sheet[i]->height());
            resizetest++;
        }
        sheet[i]->writeToFile("CurSticker.png");
        for (unsigned int w = 0; w < sheet[i]->width(); w++) {
			for (unsigned int h = 0; h < sheet[i]->height(); h++) {
                    cs225::HSLAPixel& pixel = sheet[i]->getPixel(w,h);
                    if (pixel.a == 0){
                        continue;
                    }
                    cs225::HSLAPixel& replacePixel = result.getPixel(x_vec[i]+w, y_vec[i]+h);

                    replacePixel = pixel;
                }
        }
    }
    
    //result should now have the stickers on it and if it never resized then it should be the initial size

    result.writeToFile("resultresult.png");

    deepCopy_->writeToFile("DeepResult.png");

    return result;
    
}