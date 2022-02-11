/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
	class HSLAPixel {
	public:
		double h, s, l, a;


		HSLAPixel() {
			h = 0;
			s = 0;
			l  = 1;
			a  = 1;
		}
		HSLAPixel(double hue_, double saturation_, double luminance_, double alpha_) {
			h  = hue_;
			s = saturation_;
			l = luminance_;
			a = alpha_;
		}
		HSLAPixel(double hue_, double saturation_, double luminance_) {
			h = hue_;
			s = saturation_;
			l = luminance_;
			a = 1;
		}
		
			};
}
