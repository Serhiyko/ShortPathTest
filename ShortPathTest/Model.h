#pragma once

/******************************/
//This class performs read vertexes from the file in binary mode.
//The vertexes save in vector<Triangle>
/******************************/

#include <vector>
#include <fstream>
#include <string>

#include "Triangle.h"

class Model
{
public:
	Model();
	~Model();

	void readData(const std::string& filename);
	void printData();

	std::vector<Triangle> getTriangles() const { return _triangles; }

private:
	float parse_float(std::ifstream& file);

	Points parse_point(std::ifstream& file);

private:
	std::vector<Triangle> _triangles;
};