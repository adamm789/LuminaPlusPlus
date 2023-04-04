#pragma once
#include "Shape.h"
#include <string>
#include <vector>

class Model;
class Submesh
{
public:
	__declspec(dllexport) Submesh();
	__declspec(dllexport) Submesh(Model* model, int meshIndex, int subMeshIndex);

	uint32_t IndexOffset = 0;
	uint32_t IndexNum = 0;
	std::vector<std::string> Attributes;
	std::vector<std::string> Bones;

	std::vector<Shape*> Shapes;
};
