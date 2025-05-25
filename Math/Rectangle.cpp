#include "Rectangle.h"
namespace sds 
{

Rectangle::Rectangle()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Rectangle::Rectangle(float x_, float y_, float width_, float height_)
{
	x = x_;
	y = y_;
	width = width_;
	height = height_;
}

bool Rectangle::contains(const Point& point)
{
	return 
		point.x >= x		 &&
		point.x <= x + width &&
		point.y >= y		 &&
		point.y <= y + height;
}

bool Rectangle::intersects(const Rectangle& rect)
{
	return
		x < rect.x + rect.width  &&
		x + width > rect.x		 &&
		y < rect.y + rect.height &&
		y + height > rect.y;
}

}