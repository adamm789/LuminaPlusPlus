#pragma once
#include "../../Data/Parsing/MdlStructs.h"
#include <string>
#include <vector>
#include <map>
#include "Vertex.h"
class Shape
{
	// https://github.com/xivdev/Penumbra/blob/master/Penumbra.GameData/Files/MdlFile.cs
public:
	std::string ShapeName;
	uint16_t ShapeMeshStartIndex[3];
	uint16_t ShapeMeshCount[3];

	std::vector<MdlStructs::ShapeValueStruct> ShapeValueStructs;

	uint16_t ShapeValuesStartIndex = 0;

	__declspec(dllexport) Shape(std::string shapeName, uint16_t startIndex[3], uint16_t meshCount[3]);
};

