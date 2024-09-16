#include "shapes.h"
#include "iostream"
#include "string"

//Implement your shapes here

using namespace std;

Shape::Shape(Color c) : m_color(c) {};

void Shape::draw(uint8_t ***image, uint32_t h, uint32_t w) {

  BoundingBox b = getBoundingBox();

  for (int i = b.ul.x; i < b.br.x; ++i) {
    for (int j = b.ul.y; j < b.br.y; ++j) {
      if (i < h && j < w) {
        if (inside(i, j)) {
          image[j][i][0] = m_color.r;
          image[j][i][1] = m_color.g;
          image[j][i][2] = m_color.b;
        }
      }
    }
  }
};

Triangle::Triangle(Color c, Point points[3]) : Shape(c) {
  for (int i = 0; i < 3; ++i) {
    m_points[i] = points[i];
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

Circle::Circle(Color c, Point center, int radius) : Shape(c) {
  m_center = center;
  m_radius = radius;
}

BoundingBox Circle::getBoundingBox() {
  Point br;
  br.x = m_center.x + m_radius;
  br.y = m_center.y + m_radius;

  Point ul;
  ul.x = m_center.x - m_radius;
  ul.y = m_center.y - m_radius;

  BoundingBox b = BoundingBox(ul, br);

  return b;
}

bool Circle::inside(uint32_t x, uint32_t y) {
  uint32_t dx = x - m_center.x;
  uint32_t dy = y - m_center.y;
  uint32_t d_squared = dx * dx + dy * dy;

  return d_squared <= (m_radius * m_radius);
}

Rectangle::Rectangle(Color c, Point ul, Point br) : Shape(c) {
  m_ul = ul;
  m_br = br;
}

BoundingBox Rectangle::getBoundingBox() {
  BoundingBox b = BoundingBox(m_ul, m_br);
  return b;
}

bool Rectangle::inside(uint32_t x, uint32_t y) {
  if (x > m_ul.x && x < m_br.x) {
    if (y > m_ul.y && y < m_br.y) {
      return true;
    }
  }
  return false;
}