#pragma once
#include "Shape.h"
#include <string>
#include <vector>

class Model;
class Submesh
{
public:
	Submesh(Model* model, int meshIndex, int subMeshIndex);

	uint32_t IndexOffset;
	uint32_t IndexNum;
	std::vector<std::string> Attributes;
	std::vector<std::string> Bones;

	std::vector<Shape> Shapes;
};

