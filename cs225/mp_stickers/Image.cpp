#include "Image.h"
#include "cs225/PNG.h"
using cs225::HSLAPixel;
		void Image::lighten() {
			for (unsigned int w = 0; w < width(); w++) {
				for (unsigned int h = 0; h < height(); h++) {
					HSLAPixel& pixel = this->getPixel(w, h);
					double lum = pixel.l;
					if (lum < .9) {
						pixel.l += .1;
					}
					else {
						pixel.l = 1;
					}
				}
			}
		}
		void Image::lighten(double amount) {
			for (unsigned int w = 0; w < width(); w++) {
				for (unsigned int h = 0; h < height(); h++) {
					HSLAPixel& pixel = this->getPixel(w, h);
					double lum = pixel.l;
						if (lum < 1 - amount) {
							pixel.l = lum + amount;
						}
						else {
							pixel.l = 1;
						}
					}
				}
		}
		void Image::darken() {
				for (unsigned int w = 0; w < width(); w++) {
					for (unsigned int h = 0; h < height(); h++) {
						HSLAPixel& pixel = this->getPixel(w, h);
						double lum = pixel.l;
							if (lum > .1) {
								pixel.l = lum - .1;
							}
							else {
								pixel.l = 0;
							}
					}
				}
		}
		void Image::darken(double amount) {
			for (unsigned int w = 0; w < width(); w++) {
				for (unsigned int h = 0; h < height(); h++) {
					HSLAPixel& pixel = this->getPixel(w, h);
					double lum = pixel.l;
						if (lum > amount) {
							pixel.l = lum - amount;
						}
						else {
							pixel.l = 0;
						}
				}
			}
		}
		void Image::saturate() {
				for (unsigned int w = 0; w < width(); w++) {
					for (unsigned int h = 0; h < height(); h++) {
						HSLAPixel& pixel = this->getPixel(w, h);
						double sat = pixel.s;
							if (sat < .9) {
								pixel.s += .1;
							}
							else {
								pixel.s = 1;
							}
					}
				}
		}
		void Image::saturate(double amount) {
				for (unsigned int w = 0; w < width(); w++) {
					for (unsigned int h = 0; h < height(); h++) {
						HSLAPixel& pixel = this->getPixel(w, h);
						double sat = pixel.s;
							if (sat < 1 - amount) {
								pixel.s += amount;
							}
							else {
								pixel.s = 1;
							}
					}
				}
		}
		void Image::desaturate() {
				for (unsigned int w = 0; w < width(); w++) {
					for (unsigned int h = 0; h < height(); h++) {
						HSLAPixel& pixel = this->getPixel(w, h);
						double sat = pixel.s;
							if (sat > .1) {
								pixel.s -=.1;
							}
							else {
								pixel.s = 0;
							}
					}
				}
		}
		void Image::desaturate(double amount) {
				for (unsigned int w = 0; w < width(); w++) {
					for (unsigned int h = 0; h < height(); h++) {
						HSLAPixel& pixel = this->getPixel(w, h);
						double sat = pixel.s;
							if (sat > amount) {
								pixel.s -= amount;
							}
							else {
								pixel.s = 0;
							}
					}
				}
		}
		void Image::grayscale() {
				for (unsigned int w = 0; w < width(); w++) {
					for (unsigned int h = 0; h < height(); h++) {
						HSLAPixel& pixel = this->getPixel(w, h);
						pixel.s = 0;

					}
				}
		}
		void Image::rotateColor(double degrees) {
			for (unsigned int w = 0; w < width(); w++) {
				for (unsigned int h = 0; h < height(); h++) {
					HSLAPixel& pixel = this->getPixel(w, h);
					double sat = pixel.h;
					double rot = sat + degrees;
					if (rot > 360) {
						rot -= 360;
						pixel.h = rot;
					}
					if(rot < 0) {
						rot = rot + 360;
						pixel.h = rot;
					}
					else {
						pixel.h = rot;
					}
				}
			}
		}
		
		void Image::illinify() {
				for (unsigned int w = 0; w < width(); w++) {
					for (unsigned int h = 0; h < height(); h++) {
						HSLAPixel& pixel = this->getPixel(w, h);
						int Hue = (pixel.h);
						int Color1 = 11;
						int Color2 = 216;
						int diff1 = 0;
						int diff2 = 0;
						int finColor = 0;

						if (abs(Hue - Color1) < abs(Hue - abs(Color1 - 360))) {
							diff1 = abs(Hue - Color1);
						}
						else {
							diff1 = abs(Hue - abs(Color1 - 360));
						}
						if (abs(Hue - Color2) < abs(Hue - abs(Color2 - 360))) {
							diff2 = abs(Hue - Color2);
						}
						else {
							diff2 = abs(Hue - abs(Color2 - 360));
						}
						if (diff2 < diff1) {
							finColor = Color2;
						}
						else {
							finColor = Color1;
						}
						pixel.h = finColor;
					}
				}
		}
		void Image::scale(double factor) {			
			int hf = factor * height();
			int wf = factor * width();
			Image img2;
			img2.resize(wf,hf);
			for(int i = 0; i < wf; i++){
				for(int j = 0; j < hf; j++){
					double il = i/factor;
					double jl = j/factor;
					jl = round(jl);
					il = round(il);
					HSLAPixel& pixel = img2.getPixel(i,j);
					if (jl == height()){
						jl = height() - 1;
					}
					if (il == width()){
						il = width() - 1;
					}
					
					HSLAPixel& reppixel = this->getPixel(il,jl);
					pixel = reppixel;
					
				}
			}
			this->resize(wf,hf);
			for(int i = 0; i < wf; i++) {
				for( int j = 0; j < hf; j++ ){
					HSLAPixel& pixel = getPixel(i,j);
					HSLAPixel& reppixel = img2.getPixel(i,j);
					pixel = reppixel;
				}
			}
			
		}
		void Image::scale(unsigned w, unsigned h) {
			int hf = h * height();
			int wf = w * width();
			PNG* Copy = new PNG(wf, hf);
			for (unsigned int x = 0; x < width(); x++) {
				for (unsigned int y = 0; y < height(); y++) {
					HSLAPixel& pixel = this->getPixel(x, y);
					for (unsigned int L = 0; L < w ; L++) {
						for (unsigned int R = 0; R < h; R++) {
							HSLAPixel& copyPixel = Copy->getPixel(wf + L, hf + R);
							copyPixel = pixel;
						}
					}
				}
			
			}
		}
