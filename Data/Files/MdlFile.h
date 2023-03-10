#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include <string>
#include "../Parsing/MdlStructs.h"

class MdlFile
{
public:
	static MdlFile* LoadFromFile2(std::string filePath);
	~MdlFile();
	void LoadFromFile(std::string filePath);

	char* Data;

	MdlStructs::ModelFileHeader FileHeader;
	std::vector<MdlStructs::VertexDeclarationStruct> VertexDeclarations;
	uint16_t StringCount;
	char* Strings;

	MdlStructs::ModelHeader ModelHeader;
	std::vector<MdlStructs::ElementIdStruct> ElementIds;
	MdlStructs::LodStruct Lods[3];
	MdlStructs::ExtraLodStruct ExtraLods[3];
	std::vector<MdlStructs::MeshStruct> Meshes;

	std::vector<uint32_t> AttributeNameOffsets;

	std::vector<MdlStructs::TerrainShadowMeshStruct> TerrainShadowMeshes;
	std::vector<MdlStructs::SubmeshStruct> Submeshes;
	std::vector<MdlStructs::TerrainShadowSubmeshStruct> TerrainShadowSubmeshes;

	std::vector<uint32_t> MaterialNameOffsets;
	std::vector<uint32_t> BoneNameOffsets;
	std::vector<MdlStructs::BoneTableStruct> BoneTables;

	std::vector<MdlStructs::ShapeStruct> Shapes;
	std::vector<MdlStructs::ShapeMeshStruct> ShapeMeshes;
	std::vector<MdlStructs::ShapeValueStruct> ShapeValues;

	std::vector<uint16_t> SubmeshBoneMap;

	MdlStructs::BoundingBoxStruct BoundingBoxes;
	MdlStructs::BoundingBoxStruct ModelBoundingBoxes;
	MdlStructs::BoundingBoxStruct WaterBoundingBoxes;
	MdlStructs::BoundingBoxStruct VerticalFogBoundingBoxes;
	std::vector<MdlStructs::BoundingBoxStruct> BoneBoundingBoxes;

	uint32_t StringSize;
	bool ExtraLodEnabled;
	bool HasLoaded = false;
};
