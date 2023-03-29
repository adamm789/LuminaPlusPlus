#include "Shape.h"

Shape::Shape(std::string shapeName, uint16_t startIndex[3], uint16_t meshCount[3]) {
	ShapeName = shapeName;
	//ShapeMeshStartIndex = *startIndex;
	memcpy(&ShapeMeshStartIndex, &startIndex, 3);
	//ShapeMeshCount = meshCount;
	memcpy(&ShapeMeshCount, &meshCount, 3);
}