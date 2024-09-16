#include <iostream>
#include <sstream>
#include <string>
#include "bmplib.h"
#include "shapes.h"

using namespace std;

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

void getPointInput(Point& p) {
	string input;
	int value;
	
	cout << "Enter x: ";
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (ss >> value && value >= 0 && value <= UINT32_MAX && ss.eof()) {
			p.x = static_cast<uint32_t>(value);
			break;
		}
		cout << "Invalid input. Enter x: ";
	}

	cout << "Enter y: ";
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (ss >> value && value >= 0 && value <= UINT32_MAX && ss.eof()) {
			p.y = static_cast<uint32_t>(value);
			break;
		}
		cout << "Invalid input. Enter y: ";
	}
}


void getColorInput(Color& c) {
	string input;
	int value;

	cout << "Please choose the color of your shape (rgb)..." << endl;

	cout << "Enter r: ";
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (ss >> value && value >= 0 && value <= 255 && ss.eof()) {
			c.r = static_cast<uint8_t>(value);
			break;
		}
		cout << "Invalid input. Enter r: ";
	}

	cout << "Enter g: ";
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (ss >> value && value >= 0 && value <= 255 && ss.eof()) {
				c.g = static_cast<uint8_t>(value);
				break;
		}
		cout << "Invalid input. Enter g: ";
	}

	cout << "Enter b: ";
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (ss >> value && value >= 0 && value <= 255 && ss.eof()) {
				c.b = static_cast<uint8_t>(value);
				break;
		}
		cout << "Invalid input. Enter b: ";
	}
}

int main(int argc, char* argv[])
{
    uint32_t h = 1024;
    uint32_t w = 1024;

    uint8_t bg[] = { 255, 255, 255 };
    uint8_t*** image = newImage(bg, h, w);

    string shape;

    while (true) {
        cout << "What shape would you like to draw? (rectangle/triangle/circle) or 'quit' to stop: ";
        cin >> shape;
        cin.ignore();

        if (shape == "quit") {
            break;
        }

        if (shape == "rectangle") {
					Color c;
					getColorInput(c);

					Point p1, p2;
					cout << "Enter the upper-left corner of the rectangle (x, y):\n";
					getPointInput(p1);
					cout << "Enter the bottom-right corner of the rectangle (x, y):\n";
					getPointInput(p2);

					Rectangle r = Rectangle(c, p1, p2);
					r.draw(image, h, w);

        } else if (shape == "triangle") {
					Color c;
					getColorInput(c);

					Point p1, p2, p3;
					cout << "Enter the first point of the triangle (x, y):\n";
					getPointInput(p1);
					cout << "Enter the second point of the triangle (x, y):\n";
					getPointInput(p2);
					cout << "Enter the third point of the triangle (x, y):\n";
					getPointInput(p3);

					Point p_set[3] = { p1, p2, p3 };

					Triangle t = Triangle(c, p_set);
					t.draw(image, h, w);

        } else if (shape == "circle") {
					Color c;
					getColorInput(c);

					Point center;
					int radius;
					cout << "Enter the center of the circle (x, y):\n";
					getPointInput(center);
					cout << "Enter the radius of the circle: ";
					cin >> radius;

					Circle ci = Circle(c, center, radius);
					ci.draw(image, h, w);
        } else {
					cout << "Invalid shape. Please enter rectangle, triangle, or circle.\n";
        }

        writeRGBBMP("output.bmp", image, 1024, 1024);
    }

    return 0;
}
