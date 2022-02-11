/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "cs225/PNG.h"
#include <vector>

class StickerSheet {
    public:
    cs225::PNG* deepCopy_ = 0;
    std::vector<Image*> sheet;
    std::vector<int> x_vec;
    std::vector<int> y_vec;
    unsigned int init_deepX;
    unsigned int init_deepY;

    ~StickerSheet();
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate (unsigned index, unsigned x, unsigned y);
    void removeSticker (unsigned index);
    Image* getSticker(unsigned index);
    Image render() const;

};