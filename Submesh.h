#pragma once
#include <string>
#include <vector>

class Model;
class Submesh
{
public:
	unsigned int IndexOffset;
	unsigned int IndexNum;
	std::vector<std::string> Attributes;
	std::vector<std::string> Bones;

	Submesh(Model* model, int meshIndex, int subMeshIndex);
};

