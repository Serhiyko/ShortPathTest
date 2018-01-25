#pragma once

/*************************/
//This class describes each tringle of the surface.
//The vertexes of the triangle are described by the struct called Points.
/*************************/

struct Points
{
	float _x;
	float _y;
	float _z;

	Points() : _x(0), _y(0), _z(0) {}
	Points(float x, float y, float z) : _x(x), _y(y), _z(z) {}

	//overloaded operator for check if vertexes are equal.
	bool operator ==(const Points& point)
	{
		return ((this->_x == point._x) && (this->_y == point._y) && (this->_z == point._z));
	}

	//overloaded operator for check if vertexes aren't equal.
	bool operator !=(const Points& point)
	{
		return ((this->_x != point._x) || (this->_y != point._y) || (this->_z != point._z));
	}
};

class Triangle
{
public:
	Triangle (const Points& v1, const Points& v2, const Points& v3);
	~Triangle();

	Points getV1() const { return _vertex1; }
	Points getV2() const { return _vertex2; }
	Points getV3() const { return _vertex3; }

private:
	Points _vertex1;
	Points _vertex2;
	Points _vertex3;
};
