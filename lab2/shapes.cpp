#include "shapes.h"
#include "iostream"
#include "string"

//Implement your shapes here

using namespace std;

Shape::Shape(Color c) : m_color(c) {};

void Shape::draw(uint8_t ***image, uint32_t h, uint32_t w)
{

  BoundingBox b = getBoundingBox();

  // cout << "Bounding Box: x: " << b.ul.x << ", y: " << b.ul.y << endl;
  // cout << "Bounding Box: x: " << b.br.x << ", y: " << b.br.y << endl;

  for (int i = b.ul.y; i < b.br.y; ++i) {
    for (int j = b.ul.x; j < b.br.x; ++j) {

      if (i < h && j < w) {
        if (inside(j, i)) {

          uint8_t s[3];
          m_color.deserialize(s);

          image[j][i] = s;
        }
      }
    }
  }
};

Triangle::Triangle(Color c, Point points[3]) : Shape(c) {
  for (int i = 0; i < 3; ++i) {
    m_points[i] = points[i];
    // cout << "Initializing point " << i << ": " << m_points[i].x << ", " << m_points[i].y << endl;
  }
}

BoundingBox Triangle::getBoundingBox() {
  int max_y, max_x, min_y, min_x;

  max_y = m_points[0].y;
  min_y = m_points[0].y;
  max_x = m_points[0].x;
  min_x = m_points[0].x;

  for (int i = 0; i < 3; ++i) {
    Point curr_point;


    curr_point.x = m_points[i].x;
    curr_point.y = m_points[i].y;

    cout << "Point " << i << ": " << curr_point.x << ", " << curr_point.y << endl;

    if (curr_point.x > max_x) {
      max_x = curr_point.x;
    }
    if (curr_point.x < min_x) {
      min_x = curr_point.x;
    }
    if (curr_point.y > max_y) {
      max_y = curr_point.y;
    } 
    if (curr_point.y < min_y) {
      min_y = curr_point.y;
    } 
  }

  Point br;
  br.x = max_x;
  br.y = max_y;

  Point ul;
  ul.x = min_x;
  ul.y = min_y;

  BoundingBox b = BoundingBox(ul, br);

  return b;
};

bool PointInTriangle(Point p, Point tri[3])
{
	int s = (tri[0].x - tri[2].x) * (p.y - tri[2].y) - (tri[0].y - tri[2].y) * (p.x - tri[2].x);
	int t = (tri[1].x - tri[0].x) * (p.y - tri[0].y) - (tri[1].y - tri[0].y) * (p.x - tri[0].x);

	if ((s < 0) != (t < 0) && s != 0 && t != 0)
		return false;

	int d = (tri[2].x - tri[1].x) * (p.y - tri[1].y) - (tri[2].y - tri[1].y) * (p.x - tri[1].x);
	return d == 0 || (d < 0) == (s + t <= 0);
}

bool Triangle::inside(uint32_t x, uint32_t y) {
  Point p;
  p.x = x;
  p.y = y;

  bool is_inside = PointInTriangle(p, m_points);

  return is_inside;
}

// Circle::Circle(Color c, Point center, int radius) : Shape(c) {
//   m_center = center;
//   m_radius = radius;
// }

// BoundingBox Circle::getBoundingBox() {
//   BoundingBox b;

//   b.br = ;
//   b.ul = ;
// }

// bool Circle::inside(uint32_t x, uint32_t y) {
// }

// Rectangle::Rectangle(Color c, Point ul, Point br) : Shape(c) {
//   m_ul = ul;
//   m_br = br;
// }

// BoundingBox Rectangle::getBoundingBox() {
//   BoundingBox b;

//   b.br = ;
//   b.ul = ;
// }

// bool Rectangle::inside(uint32_t x, uint32_t y) {
// }