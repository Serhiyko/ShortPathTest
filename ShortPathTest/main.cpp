#include <iostream>

#include "ShortestPath.h"

int main(int argc, char** argv)
{
	std::unique_ptr<ShortestPath> obj(new ShortestPath());

	Points p1 = obj->getPoint(0, 2);
	Points p2 = obj->getPoint(10, 1);

	float length = obj->calculatePath(0, p1, 34, p2);
	std::cout << "length = " << length << std::endl;

	system("pause");
	return 0;
}