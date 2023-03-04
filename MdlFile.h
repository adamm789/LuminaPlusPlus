#pragma once
#include <iostream>
#include <fstream>

#include <string.h>
#include "MdlStructs.h"

class MdlFile
{
public:
	MdlFile();
	MdlFile(std::string filePath);
	~MdlFile();

	char* Data;

	MdlStructs::ModelFileHeader FileHeader;
	MdlStructs::VertexDeclarationStruct* VertexDeclarations;
	unsigned short StringCount;
	char* Strings;

	MdlStructs::ModelHeader ModelHeader;
	MdlStructs::ElementIdStruct* ElementIds;
	MdlStructs::LodStruct Lods[3];
	MdlStructs::ExtraLodStruct ExtraLods[3];
	MdlStructs::MeshStruct* Meshes;

	unsigned int* AttributeNameOffsets;

	MdlStructs::TerrainShadowMeshStruct* TerrainShadowMeshes;
	MdlStructs::SubmeshStruct* Submeshes;
	MdlStructs::TerrainShadowSubmeshStruct* TerrainShadowSubmeshes;

	unsigned int* MaterialNameOffsets;
	unsigned int* BoneNameOffsets;
	MdlStructs::BoneTableStruct* BoneTables;

	MdlStructs::ShapeStruct* Shapes;
	MdlStructs::ShapeMeshStruct* ShapeMeshes;
	MdlStructs::ShapeValueStruct* ShapeValues;

	unsigned short* SubmeshBoneMap;

	MdlStructs::BoundingBoxStruct BoundingBoxes;
	MdlStructs::BoundingBoxStruct ModelBoundingBoxes;
	MdlStructs::BoundingBoxStruct WaterBoundingBoxes;
	MdlStructs::BoundingBoxStruct VerticalFogBoundingBoxes;
	MdlStructs::BoundingBoxStruct* BoneBoundingBoxes;

	unsigned int StringSize;
	bool ExtraLodEnabled;
};
