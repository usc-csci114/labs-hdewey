#include <iostream>
#include "bmplib.h"
#include "shapes.h"

using namespace std;

const Color BLACK = { 0, 0, 0 };

uint8_t*** newImage(uint8_t bground[3], uint32_t h, uint32_t w)
{
	uint8_t*** img = new uint8_t**[h];
	for(int r=0; r < h; r++) {
		img[r] = new uint8_t*[w];
		for(int c = 0; c < w; c++) {
			img[r][c] = new uint8_t[3];
			img[r][c][0] = bground[0];
			img[r][c][1] = bground[1];
			img[r][c][2] = bground[2];
		}
	}
	return img;
}

int main(int argc, char* argv[])
{
	uint32_t h = 1024;
	uint32_t w = 1024;

	uint8_t bg[] = {255,255,255};
	uint8_t*** image = newImage(bg, h, w);
	
	//add your code here

	Point p1;
	p1.x = 1;
	p1.y = 1;

	Point p2;
	p2.x = 50;
	p2.y = 50;
	

	Point p3;
	p3.x = 50;
	p3.y = 1;

	Point p_set[3] = { p1, p2, p3 };

	Triangle t = Triangle(BLACK, p_set);

	t.draw(image, h, w);
	
	//ask the user what shape the want to draw
	//collect the required information
	//instantiate the shape, draw it into the image
	//loop and ask for another shape, "quit" to stop
	
	writeRGBBMP("output.bmp", image, 1024, 1024);

	return 0;
}
