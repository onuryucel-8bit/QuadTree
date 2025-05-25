#pragma once
namespace sds
{

struct Point
{
	float x, y;
};


class Rectangle
{
public:
	float x, y, width, height;
	
	Rectangle();
	Rectangle(float x_, float y_, float width_, float height_);

	bool contains(const Point& point);
	bool intersects(const Rectangle& rect);
};
}