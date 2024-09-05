#include <iostream>
#include <cmath>
#include <vector>

#include "bmplib.h"
#include "drawing.h"

//implement your classes in this file
//Point is given for the line drawing algorithm
// struct Point {
// 	double x, y;
// };

const ColorPixel BLACK = { 0, 0, 0};

ColorImage::ColorImage(uint32_t xdim, uint32_t ydim) {
	// set empty 2d vec
  data = vector< vector<ColorPixel> >(xdim, vector<ColorPixel>(ydim, BLACK));
}

void ColorImage::setPixel(ColorPixel s, uint32_t x, uint32_t y) {
	// set pixel x,y to given color s
	if (x < data.size() && y < data[0].size()) {
			data[x][y] = s;
	}
}

ColorPixel ColorImage::getPixel(uint32_t x, uint32_t y) {
	// return pixel x,y
	if (x < data.size() && y < data[0].size()) {
		return data[x][y];
	}
	return BLACK;
}

void ColorImage::render(string filename) {
	// Get the dimensions of the image
	uint32_t height = data.size();
	uint32_t width = (height > 0) ? data[0].size() : 0;

	// store blob in memory for bmplib
	unsigned char ***outputBlob = new unsigned char**[height];
	for (uint32_t i = 0; i < height; i++) {
			outputBlob[i] = new unsigned char*[width];
			for (uint32_t j = 0; j < width; j++) {
					outputBlob[i][j] = new unsigned char[3];
					outputBlob[i][j][0] = data[i][j].red;
					outputBlob[i][j][1] = data[i][j].green;
					outputBlob[i][j][2] = data[i][j].blue;
			}
	}

	// call bmplib func with blob
	writeRGBBMP(filename.c_str(), outputBlob, height, width);

	// freee
	for (uint32_t i = 0; i < height; i++) {
			for (uint32_t j = 0; j < width; j++) {
					delete[] outputBlob[i][j];
			}
			delete[] outputBlob[i];
	}
	delete[] outputBlob;
}

Drawing::Drawing() : image(256, 256) {};

void Drawing::parse(string filename) {
	freopen(filename.c_str(), "r", stdin);

	int xdim, ydim;

	// first line dims
	if (!(cin >> xdim >> ydim)) {
		cerr << "Error reading image dimensions from file: " << filename << endl;
		return;
	}

	image = ColorImage(xdim, ydim);

	// valid line: x1, y1, x2, y2, r, g, b
	while (true) {
		Line l;
		int r, g, b;

		// read components
		if (!(cin >> l.start.x >> l.start.y >> l.end.x >> l.end.y >> r >> g >> b)) {
			break;
		}

		// cast channels
		l.c.red = static_cast<uint8_t>(r);
		l.c.green = static_cast<uint8_t>(g);
		l.c.blue = static_cast<uint8_t>(b);

		lines.push_back(l);
	}

	fclose(stdin);
};

void Drawing::draw() {
	for (size_t i = 0; i < lines.size(); ++i) {
    const Line& line = lines[i];
		std::vector<Point> points = plotLine(line.start, line.end);

		for (size_t j = 0; j < points.size(); ++j) {
    	const Point& point = points[j];
			image.setPixel(line.c, point.x, point.y);
		}
	}
}

void Drawing::write(string filename) {
	image.render(filename);
}

//adapted from https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
std::vector<Point> plotLine(Point start, Point end)
{
	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;
	
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
	
	std::vector<Point> line;
	
	while(true)
	{
		Point p = {x0, y0};
		line.push_back(p);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * error;
		if(e2 >= dy) {
			error = error + dy;
			x0 = x0 + sx;
		}
		if(e2 <= dx) {
			error = error + dx;
			y0 = y0 + sy;
		}
	}
	return line;
}
