#include "Shape.h"

Shape::Shape(std::string shapeName, uint16_t startIndex[3], uint16_t meshCount[3]) {
	ShapeName = shapeName;
	for (int i = 0; i < 3; i++) {
		ShapeMeshStartIndex[i] = startIndex[i];
		ShapeMeshCount[i] = meshCount[i];
	}
}