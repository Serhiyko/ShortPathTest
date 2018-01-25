#include "Model.h"

#include <iostream>

Model::Model()
{
}

Model::~Model()
{
}

void Model::readData(const std::string & filename)
{
	std::ifstream file(filename.c_str(), std::ios::binary);
	if (!file)
	{
		std::cerr << "ERROR: COULD NOT READ FILE" << std::endl;
	}

	char header_info[80] = "";
	char triangles[4];

	file.read(header_info, 80);
	file.read(triangles, 4);

	int* r = (int*)triangles;
	int num_triangles = *r;

	for (int i = 0; i < num_triangles; ++i) {
		auto normal = parse_point(file);
		auto v1 = parse_point(file);
		auto v2 = parse_point(file);
		auto v3 = parse_point(file);

		_triangles.push_back(Triangle(v1, v2, v3));

		char dummy[2];
		file.read(dummy, 2);
	}

	file.close();
}

void Model::printData()
{
	/*for (int i = 0; i < _triangles.size(); ++i)
	{
		std::cout << _triangles[i].getV1()._x << " " << _triangles[i].getV1()._y << " " << _triangles[i].getV1()._z << std::endl;
		std::cout << _triangles[i].getV2()._x << " " << _triangles[i].getV2()._y << " " << _triangles[i].getV2()._z << std::endl;
		std::cout << _triangles[i].getV3()._x << " " << _triangles[i].getV3()._y << " " << _triangles[i].getV3()._z << std::endl;
		std::cout << "************************************************" << std::endl;
	}*/
	std::cout << "Model contains " << _triangles.size() << " triangles!" << std::endl;
}

float Model::parse_float(std::ifstream & file)
{
	char buffer[sizeof(float)];
	file.read(buffer, 4);
	float* d_ptr = (float*)buffer;

	return *d_ptr;
}

Points Model::parse_point(std::ifstream & file)
{
	float x = parse_float(file);
	float y = parse_float(file);
	float z = parse_float(file);

	return Points(x, y, z);
}
