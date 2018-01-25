#include "Triangle.h"


Triangle::Triangle(const Points& v1, const Points& v2, const Points& v3)
{
	_vertex1 = v1;
	_vertex2 = v2;
	_vertex3 = v3;
}

Triangle::~Triangle()
{
}
