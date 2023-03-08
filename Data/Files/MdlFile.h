#pragma once
#include <iostream>
#include <fstream>

#include <string.h>
#include "../Parsing/MdlStructs.h"

class MdlFile
{
public:
	MdlFile();
	MdlFile(const char* filePath);
	void Destroy();

	char* Data;

	MdlStructs::ModelFileHeader FileHeader;
	MdlStructs::VertexDeclarationStruct* VertexDeclarations;
	uint16_t StringCount;
	char* Strings;

	MdlStructs::ModelHeader ModelHeader;
	MdlStructs::ElementIdStruct* ElementIds;
	MdlStructs::LodStruct Lods[3];
	MdlStructs::ExtraLodStruct ExtraLods[3];
	MdlStructs::MeshStruct* Meshes;

	uint32_t* AttributeNameOffsets;

	MdlStructs::TerrainShadowMeshStruct* TerrainShadowMeshes;
	MdlStructs::SubmeshStruct* Submeshes;
	MdlStructs::TerrainShadowSubmeshStruct* TerrainShadowSubmeshes;

	uint32_t* MaterialNameOffsets;
	uint32_t* BoneNameOffsets;
	MdlStructs::BoneTableStruct* BoneTables;

	MdlStructs::ShapeStruct* Shapes;
	MdlStructs::ShapeMeshStruct* ShapeMeshes;
	MdlStructs::ShapeValueStruct* ShapeValues;

	uint16_t* SubmeshBoneMap;

	MdlStructs::BoundingBoxStruct BoundingBoxes;
	MdlStructs::BoundingBoxStruct ModelBoundingBoxes;
	MdlStructs::BoundingBoxStruct WaterBoundingBoxes;
	MdlStructs::BoundingBoxStruct VerticalFogBoundingBoxes;
	MdlStructs::BoundingBoxStruct* BoneBoundingBoxes;

	uint32_t StringSize;
	bool ExtraLodEnabled;
};
