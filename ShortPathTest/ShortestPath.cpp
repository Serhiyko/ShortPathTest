#include "ShortestPath.h"

#include <iostream>

ShortestPath::ShortestPath()
{
	_modelObj = std::make_unique<Model>();

	_modelObj->readData("fullhelmet_repaired.stl");

	_triangles = _modelObj->getTriangles();

	_modelObj->printData();

	_minLength = 0.0f;

	std::cout << "Choose start and finish points.\nSet numer of triangle and number of vertex[0-2]\n";
}

ShortestPath::~ShortestPath()
{
}

float ShortestPath::calculatePath(int triangle1, Points& startPoint, int triangle2, const Points& finishPoint)
{
	Points p = finishPoint;
	if (checkInpurData(triangle1, startPoint, triangle2, p))
	{
		_pathPoints.push_back(startPoint);

		while (startPoint != finishPoint)
		{
			searchTriangles(startPoint);

			searchPath(startPoint, finishPoint);
			_pathPoints.push_back(startPoint);
		}

		std::cout << "\n" << "\n";
		_minLength = 0.0f;
		for(int i = 1; i < _pathPoints.size(); ++i)
		{
			_minLength += getLength(_pathPoints[i - 1], _pathPoints[i]);
			//std::cout << var._x << " " << var._y << " " << var._z << std::endl;
		}
	}
	else
	{
		std::cout << "Error in input data" << std::endl;
	}
	return _minLength;
}

Points ShortestPath::getPoint(int numTriagle, int numVertex)
{
	if (numVertex == 1)
	{
		return _triangles[numTriagle].getV1();
	}
	else if (numVertex == 2)
	{
		return _triangles[numTriagle].getV2();
	}
	else if (numVertex == 3)
	{
		return _triangles[numTriagle].getV3();
	}
	return Points();
}

bool ShortestPath::checkInpurData(int triangle1, Points& startPoint, int triangle2, Points& finishPoint)
{
	if ((triangle1 > _triangles.size()) || (triangle1 < 0))
	{
		return false;
	}
	else if ((triangle1 > _triangles.size()) || (triangle1 < 0))
	{
		return false;
	}
	else if ((startPoint == Points(0, 0, 0)) || (finishPoint == Points(0, 0, 0)))
	{
		return false;
	}

	return true;
}

void ShortestPath::searchTriangles(const Points& vertex)
{
	for (int i = 0; i < _triangles.size(); ++i)
	{
		if ((_triangles[i].getV1() == vertex) || (_triangles[i].getV2() == vertex) || (_triangles[i].getV3() == vertex))
		{
			_triangleNumber.push(i);
		}
	}
}

void ShortestPath::searchPath(Points & startPoint, const Points & finishPoint)
{
	Points newStartPoint;
	bool check;

	while (!_triangleNumber.empty())
	{
		int iter = _triangleNumber.top();
		_triangleNumber.pop();

		check = checkPoint(iter, finishPoint);
		if (check)
		{
			break;
		}
		else
		{
			checkLength(iter, startPoint, finishPoint, newStartPoint);
		}
	}

	startPoint = (check) ? (finishPoint) : (newStartPoint);
}

bool ShortestPath::checkPoint(int iter, const Points & checkPoint)
{
	Points point1 = _triangles[iter].getV1();
	Points point2 = _triangles[iter].getV2();
	Points point3 = _triangles[iter].getV3();

	if ((point1 == checkPoint) || (point2 == checkPoint) || (point3 == checkPoint))
	{
		return true;
	}

	return false;
}

void ShortestPath::checkLength(int iter, const Points & startPoint, const Points & finishPoint, Points & new_start)
{
	std::multimap<float, Points> buffer;

	Points point = _triangles[iter].getV1();
	if (!checkPath(point))
	{
		if (point != startPoint)
		{
			float length = getLength(point, finishPoint);
			buffer.insert(std::make_pair(length, point));
		}
	}

	point = _triangles[iter].getV2();
	if (!checkPath(point))
	{
		if (point != startPoint)
		{
			float length = getLength(point, finishPoint);
			buffer.insert(std::make_pair(length, point));
		}
	}

	point = _triangles[iter].getV3();
	if (!checkPath(point))
	{
		if (point != startPoint)
		{
			float length = getLength(point, finishPoint);
			buffer.insert(std::make_pair(length, point));
		}
	}

	std::multimap<float, Points>::const_iterator i = buffer.cbegin();
	if (_minLength == 0.0f)
	{
		_minLength = i->first;
		new_start = i->second;
		++i;
	}
	while (i != buffer.cend())
	{
		if (_minLength > i->first)
		{
			_minLength = i->first;
			new_start = i->second;
		}
		++i;
	}
}

bool ShortestPath::checkPath(const Points & point)
{
	auto iter = std::find(_pathPoints.begin(), _pathPoints.end(), point);

	if (iter != _pathPoints.end())
	{
		return true;
	}

	return false;
}

float ShortestPath::getLength(const Points & point1, const Points & point2)
{
	return (sqrtf(pow(point2._x - point1._x, 2) + pow(point2._y - point1._y, 2) + pow(point2._z - point1._z, 2)));
}
