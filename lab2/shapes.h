#ifndef __SHAPES_H__
#define __SHAPES_H__
#include <vector>
#include <cstring>

//define our (virtual) base class
using namespace std;

struct Color {
	uint8_t r, g, b;

	void deserialize(uint8_t* s) {
		s[0] = r;
		s[1] = g;
		s[2] = b;
	}
};

struct Point {
	uint32_t x, y;
};

struct BoundingBox {
	Point ul, br;

	BoundingBox(Point up_left, Point bot_right) : ul(up_left), br(bot_right) {};
};

class Shape {
public:
	Shape(Color c);
	void draw(uint8_t*** image, uint32_t h, uint32_t w);
	virtual bool inside(uint32_t x, uint32_t y) = 0;
	virtual BoundingBox getBoundingBox() = 0;
private:
	Color m_color;
};

//define a derived class for Triangle, Rectagle, and Circle
class Triangle : public Shape {
public:
    Triangle(Color c, Point points[3]);
    bool inside(uint32_t x, uint32_t y);
    BoundingBox getBoundingBox();
private:
    Point m_points[3];
};

class Circle : public Shape {
public:
	Circle(Color c, Point center, int radius);
	bool inside(uint32_t x, uint32_t y);
	BoundingBox getBoundingBox();
private:
	Point m_center;
	int m_radius;
};

class Rectangle : public Shape {
public:
	Rectangle(Color c, Point ul, Point br);
	bool inside(uint32_t x, uint32_t y);
	BoundingBox getBoundingBox();
private:
	Point m_ul;
	Point m_br;
};

#endif