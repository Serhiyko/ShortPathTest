#pragma once

/************************/
//This class calculate the shortest path between two vetexes.
/************************/

#include <memory>
#include <stack>
#include <map>
#include <math.h>

#include "Model.h"

class ShortestPath
{
public:
	ShortestPath();
	~ShortestPath();

	//calculate the shortest path between vertex.
	float calculatePath(int triangle1, Points& startPoint, int triangle2, const Points& finishPoint);

	Points getPoint(int numTriagle, int numVertex);

private:
	bool checkInpurData(int triangle1, Points& startPoint, int triangle2, Points& finishPoint);

	//search all triangles that contain certain vertex and puch them index in the stack.
	void searchTriangles(const Points& vertex);

	//search shirtest path and checkpoints to the vector.
	void searchPath(Points& startPoint, const Points& finishPoint);

	//check if certain triangle has checkPoint.
	bool checkPoint(int iter, const Points& checkPoint);

	//choose the shortest path from some amount of paths.
	void checkLength(int iter, const Points &startPoint, const Points &finishPoint, Points &new_start);

	//check the point had been already checkable.
	bool checkPath(const Points& point);

	//get distance between two points.
	float getLength(const Points& point1, const Points& point2);

private:
	std::unique_ptr<Model> _modelObj;

	std::vector<Triangle> _triangles;
	std::vector<Points> _pathPoints;
	std::stack<int> _triangleNumber;

	float _minLength;
};

