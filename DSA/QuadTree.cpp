#include "QuadTree.h"
namespace sds 
{


QuadTree::QuadTree()
{
	treeId = 0;
	zone_a = nullptr;
	zone_b = nullptr;
	zone_c = nullptr;
	zone_d = nullptr;
	divided = false;
	m_capacity = 50;
}

QuadTree::QuadTree(Rectangle& rect, size_t capacity)
{
	treeId = 0;
	zone_a = nullptr;
	zone_b = nullptr;
	zone_c = nullptr;
	zone_d = nullptr;

	m_rect = rect; 
	divided = false;
	m_capacity = capacity;
}

QuadTree::~QuadTree()
{
	delete zone_a;
	delete zone_b;
	delete zone_c;
	delete zone_d;
}

void QuadTree::add(Point& point)
{
	//is point belongs to this node
	if (!m_rect.contains(point))
	{
		//if not return
		return;
	}

	//if size < cap and area not divided add point to this node
	if (m_points.size() < m_capacity && !divided)
	{
		m_points.push_back(point);
	}
	else
	{
		//if node not divided
		if (!divided)
		{
			subDivide();

			// Re-distribute existing points to child nodes
			for (auto& p : m_points)
			{
				if (zone_a->m_rect.contains(p)) zone_a->add(p);
				else if (zone_b->m_rect.contains(p)) zone_b->add(p);
				else if (zone_c->m_rect.contains(p)) zone_c->add(p);
				else if (zone_d->m_rect.contains(p)) zone_d->add(p);
			}
			m_points.clear(); // Clear root’s points
		}

		// if node is divided push to points to child node
		// 
		// Add the new point to the correct child
		if (zone_a->m_rect.contains(point)) zone_a->add(point);
		else if (zone_b->m_rect.contains(point)) zone_b->add(point);
		else if (zone_c->m_rect.contains(point)) zone_c->add(point);
		else if (zone_d->m_rect.contains(point)) zone_d->add(point);
	}
}

void QuadTree::remove()
{

}

bool QuadTree::isEmpty()
{
	return	
		m_points.empty()  &&
		zone_a == nullptr &&
		zone_b == nullptr &&
		zone_c == nullptr &&
		zone_d == nullptr;	
}

std::vector<Point*> QuadTree::getData(sds::Rectangle area)
{
	std::vector<Point*> pointList;

	std::queue<QuadTree*> que;
	que.push(this);

	while (!que.empty())
	{
		//move to next node
		QuadTree* currentNode = que.front();
		que.pop();

		//std::cout << "DEBUG:: getData() id " << currentNode->treeId << "\n";
		if (currentNode->m_rect.intersects(area))
		{
			if(!currentNode->m_points.empty())
			{
				for (size_t i = 0; i < currentNode->m_points.size(); i++)
				{
					pointList.push_back(&currentNode->m_points[i]);
				}
			}
			else
			{
				if (currentNode->zone_a != nullptr)
				{
					que.push(currentNode->zone_a);
					que.push(currentNode->zone_b);
					que.push(currentNode->zone_c);
					que.push(currentNode->zone_d);
				}
				
			}
		}
	}

	return pointList;
}

std::vector<Rectangle*> QuadTree::getAllAreas()
{
	std::vector<Rectangle*> rectangleList;
	rectangleList.reserve(100);

	std::queue<QuadTree*> que;
	que.push(this);

	while (!que.empty())
	{
		//move to next node
		QuadTree* currentNode = que.front();
		que.pop();

		rectangleList.push_back(&currentNode->m_rect);

		//put next nodes in que
		if (currentNode->zone_a != nullptr)
		{
			que.push(currentNode->zone_a);
			que.push(currentNode->zone_b);
			que.push(currentNode->zone_c);
			que.push(currentNode->zone_d);
		}
	}

	rectangleList.resize(rectangleList.size());
	return rectangleList;
}

#ifdef DEBUG_PRINT_POINTS
void QuadTree::DEBUG_printPoints()
{

	std::queue<QuadTree*> que;
	que.push(this);
	while (!que.empty())
	{
		QuadTree* currentNode = que.front();
		que.pop();

		std::cout << "TreeId : " << currentNode->treeId << "\n";
		for (auto& point : currentNode->m_points)
		{
			std::cout << "x : " << point.x << " y: " << point.y << "\n";
		}
		std::cout << "---------------------\n";

		if (currentNode->zone_a != nullptr)
		{
			que.push(currentNode->zone_a);
			que.push(currentNode->zone_b);
			que.push(currentNode->zone_c);
			que.push(currentNode->zone_d);
		}
	}
}

void QuadTree::DEBUG_treeId()
{
	std::queue<QuadTree*> que;
	que.push(this);

	size_t counter = 0;

	while (!que.empty())
	{
		QuadTree* currentNode = que.front();
		que.pop();

		currentNode->treeId = counter;
		counter++;

		if (currentNode->zone_a != nullptr)
		{
			que.push(currentNode->zone_a);
			que.push(currentNode->zone_b);
			que.push(currentNode->zone_c);
			que.push(currentNode->zone_d);
		}
	}
}

bool QuadTree::isInside(const sds::Point& point)
{
	if (!m_rect.contains(point))
	{
		return false;
	}
	else
	{
		if (!m_points.empty())
		{
			for (size_t i = 0; i < m_points.size(); i++)
			{
				if (m_points[i].x == point.x && m_points[i].y == point.y)
				{
					return true;
				}
			}
		}
		else
		{
			if (zone_a->isInside(point)) { return true; }
			if (zone_b->isInside(point)) { return true; }
			if (zone_c->isInside(point)) { return true; }
			if (zone_d->isInside(point)) { return true; }
		}
	}


	return false;
}

#endif // DEBUG_PRINT_POINTS

void QuadTree::subDivide()
{
	//						x						y							 width			     height
	Rectangle subRect_a(m_rect.x                   , m_rect.y                    , m_rect.width / 2  , m_rect.height / 2);
	Rectangle subRect_b(m_rect.x + m_rect.width / 2, m_rect.y                    , m_rect.width / 2  , m_rect.height / 2);
	Rectangle subRect_c(m_rect.x + m_rect.width / 2, m_rect.y + m_rect.height / 2, m_rect.width / 2  , m_rect.height / 2);
	Rectangle subRect_d(m_rect.x                   , m_rect.y + m_rect.height / 2, m_rect.width / 2  , m_rect.height / 2);

	zone_a = new QuadTree(subRect_a, m_capacity);
	zone_b = new QuadTree(subRect_b, m_capacity);
	zone_c = new QuadTree(subRect_c, m_capacity);
	zone_d = new QuadTree(subRect_d, m_capacity);

	zone_a->treeId = treeId + 1;
	zone_b->treeId = treeId + 2;
	zone_c->treeId = treeId + 3;
	zone_d->treeId = treeId + 4;

	divided = true;
}

}