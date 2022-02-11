#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>
#define PI 3.14159265



using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
	//initial setup for images
	
	PNG* inputPic = new PNG;
	PNG* outputPic = new PNG;
	inputPic->readFromFile(inputFile);
	outputPic->readFromFile(inputFile);

	for (unsigned y = 0; y < inputPic->height(); y++) {
		for (unsigned x = 0; x < inputPic->width(); x++) {
			HSLAPixel& source = inputPic->getPixel(x, y);
			HSLAPixel& sink = outputPic->getPixel(outputPic->width() - x - 1, outputPic->height() - y - 1);
				sink = source;
		
		
		}
	}


	outputPic->writeToFile(outputFile);
	delete inputPic;
	delete outputPic;

}


cs225::PNG myArt(unsigned int width, unsigned int height) {
	cs225::PNG png(width, height);
	// TODO: Part 3
	srand(314139387476189); //seed
	PNG art = PNG(width, height);

	//appropriated spotlight tech
	for (int j = 0; j < 60; j++) {
		srand(rand() % 100000);
	for (int i = 0; i < 3; i++) {
		//makeCircle(randHue, randSat, art);
		int randHue = (rand() % 361);
		double randSat = ((rand() % 30) / 100.0) + 6;
		int radius = rand() % 101;
		int centX = rand() % 801;
		int centY = rand() % 801;
		int randchance = rand() % 10;
		//std::cout << randSat << std::endl;
		HSLAPixel satPix(randHue, randSat, .5);
		for (unsigned int x = 0; x < art.width(); x++) {
			int diffx = x - centX;
			int sqrtdiffx = diffx * diffx;

			for (unsigned int y = 0; y < art.height(); y++) {

				int diffy = y - centY;
				int sqrtdiffy = diffy * diffy;
				int totdiffyx = sqrt(sqrtdiffy + sqrtdiffx);
				if (randchance < 5 && totdiffyx < radius) {
					HSLAPixel& pixel = art.getPixel(x, y);
					pixel = satPix;
				}
				if (totdiffyx == radius|| totdiffyx == radius + 1 || totdiffyx == radius - 1) {
					HSLAPixel& pixel = art.getPixel(x, y);
					pixel = satPix;
				}
				

			}
		}
		for (int w = 0; w < 20; w++) {

			//diffuser(art);
			double cosSum;
			double sinSum;
			double satSum;
			double lumSum;
			for (unsigned int x = 1; x < 799; x++) {

				for (unsigned int y = 1; y < 799; y++) {


					sinSum = 0.0;
					cosSum = 0.0;
					satSum = 0.0;
					lumSum = 0.0;
					for (int i = -1; i < 2; i++) {
						for (int j = -1; j < 2; j++) {
							//circular mean alg
						//	std::cout << "DIFFUSER " << __LINE__ << ": x = " << y << std::endl;

							HSLAPixel& curPix = art.getPixel(x + i, y + j);
							int pixAng = ((curPix.h) * PI) / 180.0;
							cosSum += cos(pixAng);
							sinSum += sin(pixAng);
							satSum += curPix.s;
							lumSum += curPix.l;
						}
					}
					HSLAPixel& actPix = art.getPixel(x, y);
					actPix.h = atan2(-sinSum, cosSum) * 180.0 / PI;
					actPix.s = satSum / 9.0;
					actPix.l = lumSum / 9.0;

				}
			}
		}

	}
	}

	return art;
}

