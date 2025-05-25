#pragma once 

#define DEBUG_PRINT_POINTS

#ifdef DEBUG_PRINT_POINTS

#include <iostream>
#include <queue>

#endif // DEBUG_PRINT_POINTS

#include "../Math/Rectangle.h"

#include <vector>
namespace sds 
{


class QuadTree
{
public:
	QuadTree();
	QuadTree(Rectangle& rect, size_t capacity);
	~QuadTree();

	//Recursive :: adds points to tree
	void add(Point& point);
	void remove();

	//if root doesnt have any points and all subRegions are nullptr return: true
	bool isEmpty();

	//returns data in specific area EX:getData({0,0,50,50}) returns datas from that area or empty array
	std::vector<Point*> getData(sds::Rectangle area);

	//returns quadtree areas/rectangles
	std::vector<Rectangle*> getAllAreas();

#ifdef DEBUG_PRINT_POINTS

	void DEBUG_printPoints();
	void DEBUG_treeId();

	//Recursive :: checks point in tree if not inside returns false
	bool isInside(const sds::Point& point);
	size_t treeId;
#endif // DEBUG_PRINT_POINTS

private:

	void subDivide();

	Rectangle m_rect;
	size_t m_capacity;
	std::vector<Point> m_points;


	QuadTree* zone_a;
	QuadTree* zone_b;
	QuadTree* zone_c;
	QuadTree* zone_d;

	bool divided;
};

}