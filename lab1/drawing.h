#include "bmplib.h"
#include "vector"

using namespace std;

//Define your structs/classes in this file
struct ColorPixel {
	uint8_t red, green, blue;
};

class ColorImage {
	public:
		ColorImage(uint32_t xdim, uint32_t ydim);
		void setPixel(ColorPixel p, uint32_t x, uint32_t y);
		ColorPixel getPixel(uint32_t x, uint32_t y);
		void render(string filename);
			
	private:
		vector< vector<ColorPixel> > data;
}; 

struct Point {
	double x, y;
};

struct Line {
	Point start, end;
	ColorPixel c;
};

class Drawing {
	public:
		Drawing();
		void parse(string filename);
		void draw();
		void write(string filename);
	private:
		ColorImage image;
		vector<Line> lines;
};

// write full-color image to the file specified by filename, from outputImage
int writeRGBBMP(const char filename[], uint8_t outputImage[][SIZE][RGB]);
std::vector<Point> plotLine(Point start, Point end);