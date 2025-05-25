#include <iostream>

#include "DSA/QuadTree.h"
#include "SDL3/SDL.h"


void runSDL(int WIN_WIDTH ,int WIN_HEIGHT ,size_t capacity = 5,size_t pointAmount = 20 ,float rectx = 0,float recty = 0,float rectw = 400,float recth = 400)
{

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return;
	}

	SDL_Window* window;
	int WINDOW_WIDTH = WIN_WIDTH;
	int WINDOW_HEIGHT = WIN_HEIGHT;
	if (window = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", WIN_WIDTH, WIN_HEIGHT, 0); window == nullptr)
	{
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
		return;
	}

	// Create a renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	if (renderer == nullptr)
	{
		SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	SDL_Event event;
	bool running = true;

	

	sds::Rectangle rect{ 0,0,(float)WINDOW_WIDTH,(float)WINDOW_HEIGHT };
	sds::QuadTree tree(rect, 6);

	std::vector<SDL_FRect> rectList;

	std::vector<SDL_FPoint> pointList;
	pointList.reserve(pointAmount);

	std::srand(std::time(0));
	for (size_t i = 0; i < pointAmount; i++)
	{
		sds::Point point;
		point.x = std::rand() % 700;
		point.y = std::rand() % 500;
		tree.add(point);
		pointList.push_back({ point.x,point.y });
	}
	

	std::vector<sds::Rectangle*> rects = tree.getAllAreas();
	for (size_t i = 0; i < rects.size(); i++)
	{
		SDL_FRect temp{ rects[i]->x ,rects[i]->y ,rects[i]->width ,rects[i]->height };
		rectList.push_back(temp);
	}

	tree.DEBUG_treeId();
	tree.DEBUG_printPoints();

	std::cout << "--------------------------\n";
	std::vector<sds::Point*> pointList_ptr = tree.getData(sds::Rectangle(rectx,recty,rectw,recth));
	for (size_t i = 0; i < pointList_ptr.size(); i++)
	{
		std::cout << pointList_ptr[i]->x << ":" << pointList_ptr[i]->y << "\n";
	}
	std::cout << "--------------------------\n";
	
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}

			if (event.type == SDL_EVENT_KEY_DOWN)
			{				
				if (event.key.key == SDLK_ESCAPE)
				{
					running = false;
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			// Set draw color to red and draw the rectangle
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

			for (SDL_FRect& rect : rectList)
			{
				SDL_RenderRect(renderer, &rect);
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderPoints(renderer ,pointList.data(), pointList.size());

			// Present the rendered frame
			SDL_RenderPresent(renderer);
			
		}
	}
	

	SDL_DestroyWindow(window);
	SDL_Quit();
}


int main()
{
	std::cout << "Running...\n";
	size_t capacity ,pointAmount;
	float rectx, recty, rectw, recth;
	int wwidth, wheight;
	std::cout << "rectx recty for QuadTree.getData() it will return sub rect of tree\n";
	std::cout << "WIN_WIDTH | WIN_HEIGHT | capacity | pointAmount | rectx | recty | rectw | recth \n";

	std::cin >> wwidth >> wheight >> capacity >> pointAmount >> rectx >> recty >> rectw >> recth;

	runSDL(wwidth, wheight, capacity, pointAmount ,rectx ,recty ,rectw ,recth);
	
	

}